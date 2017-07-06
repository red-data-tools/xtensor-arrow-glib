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

#include <xtensor-glib/xarray.hpp>

#include <xtensor/xio.hpp>

#include <iostream>
#include <sstream>

G_BEGIN_DECLS

/**
 * SECTION: array
 * @short_description: Arrow class
 * @include: xtensor-glib/xtensor-glib.h
 *
 * #GXtArray is a class for array.
 */

class GXtArrayData {
public:
  GXtArrayData(const gdouble *values, gsize n_values) :
    allocator_(),
    values_(copy_values(values, n_values)),
    buffer_(values_, n_values, allocator_),
    shape_({n_values}),
    array_(std::move(buffer_), shape_) {
  }

  ~GXtArrayData() {
  }

  gxt::xarray_adaptor_double &array() {
    return array_;
  }

private:
  gxt::xbuffer_adaptor_double::allocator_type allocator_;
  gdouble *values_;
  gxt::xbuffer_adaptor_double buffer_;
  std::vector<size_t> shape_;
  gxt::xarray_adaptor_double array_;

  gdouble *copy_values(const gdouble *values, gsize n_values) {
    auto new_values = allocator_.allocate(n_values);
    std::copy(values, values + n_values, new_values);
    return new_values;
  }
};

typedef struct GXtArrayPrivate_ {
  GXtArrayData *data;
} GXtArrayPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(GXtArray,
                           gxt_array,
                           G_TYPE_OBJECT)

#define GXT_ARRAY_GET_PRIVATE(obj)              \
  (G_TYPE_INSTANCE_GET_PRIVATE((obj),           \
                               GXT_TYPE_ARRAY,  \
                               GXtArrayPrivate))

static void
gxt_array_finalize(GObject *object)
{
  auto priv = GXT_ARRAY_GET_PRIVATE(object);

  delete priv->data;

  G_OBJECT_CLASS(gxt_array_parent_class)->finalize(object);
}

static void
gxt_array_init(GXtArray *object)
{
}

static void
gxt_array_class_init(GXtArrayClass *klass)
{
  auto gobject_class = G_OBJECT_CLASS(klass);

  gobject_class->finalize = gxt_array_finalize;
}

/**
 * gxt_array_new:
 * @values: (array length=n_values): The values of the array.
 * @n_values: The number of values.
 *
 * Returns: A newly created #GXtArray.
 *
 * Since: 1.0.0
 */
GXtArray *
gxt_array_new(const gdouble *values, gsize n_values)
{
  auto array = GXT_ARRAY(g_object_new(GXT_TYPE_ARRAY, NULL));
  auto priv = GXT_ARRAY_GET_PRIVATE(array);
  priv->data = new GXtArrayData(values, n_values);
  return array;
}

/**
 * gxt_array_to_string:
 * @array: A #GXtArray.
 *
 * Returns: (nullable): The formatted array content.
 *
 *   The returned string should be freed when with g_free() when no
 *   longer needed.
 *
 * Since: 1.0.0
 */
gchar *
gxt_array_to_string(GXtArray *array)
{
  auto priv = GXT_ARRAY_GET_PRIVATE(array);
  std::stringstream sink;
  sink << priv->data->array();
  return g_strdup(sink.str().c_str());
}

/**
 * gxt_array_reshape:
 * @array: A #GXtArray.
 * @shape: (array length=n_dimensions): The new shape.
 * @n_dimensions: The new number of dimensions.
 *
 * Returns: (transfer none): The array itself.
 *
 * Since: 1.0.0
 */
GXtArray *
gxt_array_reshape(GXtArray *array,
                  const gsize *shape,
                  gsize n_dimensions)
{
  auto priv = GXT_ARRAY_GET_PRIVATE(array);
  std::vector<size_t> shape_vector;
  for (gsize i = 0; i < n_dimensions; ++i) {
    shape_vector.push_back(shape[i]);
  }
  priv->data->array().reshape(shape_vector);
  return array;
}

G_END_DECLS
