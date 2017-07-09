/*
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <xtensor-arrow-glib/double-array.hpp>

#include <xtensor/xio.hpp>

#include <iostream>
#include <sstream>

G_BEGIN_DECLS

/**
 * SECTION: array
 * @short_description: Array class for double
 * @include: xtensor-arrow-glib/xtensor-arrow-glib.h
 *
 * #GXtDoubleArray is a class for array of double.
 */

class GXtDoubleArrayData {
public:
  GXtDoubleArrayData(const gdouble *values, gsize n_values) :
    allocator_(),
    values_(copy_values(values, n_values)),
    buffer_(values_, n_values, allocator_),
    shape_({n_values}),
    array_(std::move(buffer_), shape_) {
  }

  ~GXtDoubleArrayData() {
  }

  gxt::double_array_adaptor &array() {
    return array_;
  }

private:
  gxt::double_buffer_adaptor::allocator_type allocator_;
  gdouble *values_;
  gxt::double_buffer_adaptor buffer_;
  std::vector<size_t> shape_;
  gxt::double_array_adaptor array_;

  gdouble *copy_values(const gdouble *values, gsize n_values) {
    auto new_values = allocator_.allocate(n_values);
    std::copy(values, values + n_values, new_values);
    return new_values;
  }
};

typedef struct GXtDoubleArrayPrivate_ {
  GXtDoubleArrayData *data;
} GXtDoubleArrayPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(GXtDoubleArray,
                           gxt_double_array,
                           G_TYPE_OBJECT)

#define GXT_DOUBLE_ARRAY_GET_PRIVATE(obj)               \
  (G_TYPE_INSTANCE_GET_PRIVATE((obj),                   \
                               GXT_TYPE_DOUBLE_ARRAY,   \
                               GXtDoubleArrayPrivate))

static void
gxt_double_array_finalize(GObject *object)
{
  auto priv = GXT_DOUBLE_ARRAY_GET_PRIVATE(object);

  delete priv->data;

  G_OBJECT_CLASS(gxt_double_array_parent_class)->finalize(object);
}

static void
gxt_double_array_init(GXtDoubleArray *object)
{
}

static void
gxt_double_array_class_init(GXtDoubleArrayClass *klass)
{
  auto gobject_class = G_OBJECT_CLASS(klass);

  gobject_class->finalize = gxt_double_array_finalize;
}

/**
 * gxt_double_array_new:
 * @values: (array length=n_values): The values of the array.
 * @n_values: The number of values.
 *
 * Returns: A newly created #GXtDoubleArray.
 *
 * Since: 1.0.0
 */
GXtDoubleArray *
gxt_double_array_new(const gdouble *values, gsize n_values)
{
  auto array = GXT_DOUBLE_ARRAY(g_object_new(GXT_TYPE_DOUBLE_ARRAY, NULL));
  auto priv = GXT_DOUBLE_ARRAY_GET_PRIVATE(array);
  priv->data = new GXtDoubleArrayData(values, n_values);
  return array;
}

/**
 * gxt_double_array_to_string:
 * @array: A #GXtDoubleArray.
 *
 * Returns: (nullable): The formatted array content.
 *
 *   The returned string should be freed when with g_free() when no
 *   longer needed.
 *
 * Since: 1.0.0
 */
gchar *
gxt_double_array_to_string(GXtDoubleArray *array)
{
  auto priv = GXT_DOUBLE_ARRAY_GET_PRIVATE(array);
  std::stringstream sink;
  sink << priv->data->array();
  return g_strdup(sink.str().c_str());
}

/**
 * gxt_double_array_reshape:
 * @array: A #GXtDoubleArray.
 * @shape: (array length=n_dimensions): The new shape.
 * @n_dimensions: The new number of dimensions.
 *
 * Returns: (transfer none): The array itself.
 *
 * Since: 1.0.0
 */
GXtDoubleArray *
gxt_double_array_reshape(GXtDoubleArray *array,
                  const gsize *shape,
                  gsize n_dimensions)
{
  auto priv = GXT_DOUBLE_ARRAY_GET_PRIVATE(array);
  std::vector<size_t> shape_vector;
  for (gsize i = 0; i < n_dimensions; ++i) {
    shape_vector.push_back(shape[i]);
  }
  priv->data->array().reshape(shape_vector);
  return array;
}

G_END_DECLS
