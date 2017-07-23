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
#include <xtensor/xeval.hpp>

#include <iostream>
#include <sstream>

G_BEGIN_DECLS

/**
 * SECTION: array
 * @short_description: Array class for double
 * @include: xtensor-arrow-glib/xtensor-arrow-glib.h
 *
 * #GXtArrowDoubleArray is a class for array of double.
 */

class GXtArrowDoubleArrayData {
public:
  GXtArrowDoubleArrayData(gxt_arrow::double_array array) :
    array_(array) {
  }

  ~GXtArrowDoubleArrayData() {
  }

  auto array() {
    return &array_;
  }

private:
  gxt_arrow::double_array array_;
};

typedef struct GXtArrowDoubleArrayPrivate_ {
  GXtArrowDoubleArrayData *data;
} GXtArrowDoubleArrayPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(GXtArrowDoubleArray,
                           gxt_arrow_double_array,
                           G_TYPE_OBJECT)

#define GXT_ARROW_DOUBLE_ARRAY_GET_PRIVATE(obj)                 \
  (G_TYPE_INSTANCE_GET_PRIVATE((obj),                           \
                               GXT_ARROW_TYPE_DOUBLE_ARRAY,     \
                               GXtArrowDoubleArrayPrivate))

static void
gxt_arrow_double_array_finalize(GObject *object)
{
  auto priv = GXT_ARROW_DOUBLE_ARRAY_GET_PRIVATE(object);

  delete priv->data;

  G_OBJECT_CLASS(gxt_arrow_double_array_parent_class)->finalize(object);
}

static void
gxt_arrow_double_array_init(GXtArrowDoubleArray *object)
{
}

static void
gxt_arrow_double_array_class_init(GXtArrowDoubleArrayClass *klass)
{
  auto gobject_class = G_OBJECT_CLASS(klass);

  gobject_class->finalize = gxt_arrow_double_array_finalize;
}

/**
 * gxt_arrow_double_array_new:
 * @shape: (array length=n_dimensions): The shape of the array.
 * @n_dimensions: The new number of dimensions.
 *
 * Returns: A newly created #GXtArrowDoubleArray.
 *
 * Since: 1.0.0
 */
GXtArrowDoubleArray *
gxt_arrow_double_array_new(const gsize *shape, gsize n_dimensions)
{
  auto object = g_object_new(GXT_ARROW_TYPE_DOUBLE_ARRAY, NULL);
  auto array = GXT_ARROW_DOUBLE_ARRAY(object);
  auto priv = GXT_ARROW_DOUBLE_ARRAY_GET_PRIVATE(array);
  std::vector<size_t> gxt_shape(n_dimensions);
  for (gsize i = 0; i < n_dimensions; ++i) {
    gxt_shape[i] = shape[i];
  }
  gxt_arrow::double_array gxt_array(gxt_shape);
  priv->data = new GXtArrowDoubleArrayData(gxt_array);
  return array;
}

/**
 * gxt_arrow_double_array_new_values:
 * @shape: (array length=n_dimensions): The shape of the array.
 * @n_dimensions: The new number of dimensions.
 * @values: (array length=n_values): The values of the array.
 * @n_values: The number of values.
 *
 * Returns: A newly created #GXtArrowDoubleArray.
 *
 * Since: 1.0.0
 */
GXtArrowDoubleArray *
gxt_arrow_double_array_new_values(const gsize *shape,
                                  gsize n_dimensions,
                                  const gdouble *values,
                                  gsize n_values)
{
  auto array = gxt_arrow_double_array_new(shape, n_dimensions);
  gxt_arrow_double_array_set_values(array, values, n_values);
  return array;
}

/**
 * gxt_arrow_double_array_to_string:
 * @array: A #GXtArrowDoubleArray.
 *
 * Returns: (nullable): The formatted array content.
 *
 *   The returned string should be freed when with g_free() when no
 *   longer needed.
 *
 * Since: 1.0.0
 */
gchar *
gxt_arrow_double_array_to_string(GXtArrowDoubleArray *array)
{
  auto priv = GXT_ARROW_DOUBLE_ARRAY_GET_PRIVATE(array);
  std::stringstream sink;
  sink << *(priv->data->array());
  return g_strdup(sink.str().c_str());
}

/**
 * gxt_arrow_double_array_reshape:
 * @array: A #GXtArrowDoubleArray.
 * @shape: (array length=n_dimensions): The new shape.
 * @n_dimensions: The new number of dimensions.
 *
 * Returns: (transfer none): The array itself.
 *
 * Since: 1.0.0
 */
GXtArrowDoubleArray *
gxt_arrow_double_array_reshape(GXtArrowDoubleArray *array,
                               const gsize *shape,
                               gsize n_dimensions)
{
  auto priv = GXT_ARROW_DOUBLE_ARRAY_GET_PRIVATE(array);
  std::vector<size_t> gxt_shape;
  for (gsize i = 0; i < n_dimensions; ++i) {
    gxt_shape.push_back(shape[i]);
  }
  priv->data->array()->reshape(gxt_shape);
  return array;
}

/**
 * gxt_arrow_double_array_set_values:
 * @array: A #GXtArrowDoubleArray.
 * @values: (array length=n_values): The values of the array.
 * @n_values: The number of values.
 *
 * Returns: (transfer none): The array itself.
 *
 * Since: 1.0.0
 */
GXtArrowDoubleArray *
gxt_arrow_double_array_set_values(GXtArrowDoubleArray *array,
                                  const gdouble *values,
                                  gsize n_values)
{
  auto priv = GXT_ARROW_DOUBLE_ARRAY_GET_PRIVATE(array);
  auto &&gxt_array = *(priv->data->array());
  for (gsize i = 0; i < n_values; ++i) {
    gxt_array(i) = values[i];
  }
  return array;
}

/**
 * gxt_arrow_double_array_plus:
 * @array1: The addend.
 * @array2: The augend.
 *
 * Returns: (transfer full): The expression to run plus.
 *
 * Since: 1.0.0
 */
GXtArrowDoubleArray *
gxt_arrow_double_array_plus(GXtArrowDoubleArray *array1,
                            GXtArrowDoubleArray *array2)
{
  auto priv1 = GXT_ARROW_DOUBLE_ARRAY_GET_PRIVATE(array1);
  auto priv2 = GXT_ARROW_DOUBLE_ARRAY_GET_PRIVATE(array2);
  auto expression = *(priv1->data->array()) + *(priv2->data->array());
  gxt_arrow::double_array &&result = xt::eval(expression);

  auto result_object = g_object_new(GXT_ARROW_TYPE_DOUBLE_ARRAY, NULL);
  auto result_array = GXT_ARROW_DOUBLE_ARRAY(result_object);
  auto result_priv = GXT_ARROW_DOUBLE_ARRAY_GET_PRIVATE(result_array);
  result_priv->data = new GXtArrowDoubleArrayData(result);
  return result_array;
}

G_END_DECLS
