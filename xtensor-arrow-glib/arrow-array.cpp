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

#include <arrow-glib/array.hpp>

#include <xtensor-arrow-glib/arrow-array.h>

#include <arrow/array.h>

#include <xtensor/xadapt.hpp>
#include <xtensor/xeval.hpp>
#include <xtensor/xio.hpp>

#include <iostream>
#include <sstream>

G_BEGIN_DECLS

/**
 * SECTION: arrow-array
 * @short_description: Array class for Apache Arrow
 * @include: xtensor-arrow-glib/xtensor-arrow-glib.h
 *
 * #GXtArrowArray is a class for array of Apache Arrow Array.
 */

typedef struct GXtArrowArrayPrivate_ {
  GArrowArray *arrow_array;
} GXtArrowArrayPrivate;

enum {
  PROP_0,
  PROP_ARROW_ARRAY
};

G_DEFINE_TYPE_WITH_PRIVATE(GXtArrowArray,
                           gxt_arrow_array,
                           G_TYPE_OBJECT)

#define GXT_ARROW_ARRAY_GET_PRIVATE(obj)                \
  (G_TYPE_INSTANCE_GET_PRIVATE((obj),                   \
                               GXT_ARROW_TYPE_ARRAY,    \
                               GXtArrowArrayPrivate))

static void
gxt_arrow_array_dispose(GObject *object)
{
  auto priv = GXT_ARROW_ARRAY_GET_PRIVATE(object);

  if (priv->arrow_array) {
    g_object_unref(priv->arrow_array);
    priv->arrow_array = nullptr;
  }

  G_OBJECT_CLASS(gxt_arrow_array_parent_class)->dispose(object);
}

static void
gxt_arrow_array_set_property(GObject *object,
                             guint prop_id,
                             const GValue *value,
                             GParamSpec *pspec)
{
  auto priv = GXT_ARROW_ARRAY_GET_PRIVATE(object);

  switch (prop_id) {
  case PROP_ARROW_ARRAY:
    priv->arrow_array = GARROW_ARRAY(g_value_dup_object(value));
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
}

static void
gxt_arrow_array_get_property(GObject *object,
                             guint prop_id,
                             GValue *value,
                             GParamSpec *pspec)
{
  switch (prop_id) {
  case PROP_ARROW_ARRAY:
    g_value_set_object(value, gxt_arrow_array_get_raw(GXT_ARROW_ARRAY(object)));
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
}

static void
gxt_arrow_array_init(GXtArrowArray *object)
{
}

static void
gxt_arrow_array_class_init(GXtArrowArrayClass *klass)
{
  auto gobject_class = G_OBJECT_CLASS(klass);

  gobject_class->dispose = gxt_arrow_array_dispose;
  gobject_class->set_property = gxt_arrow_array_set_property;
  gobject_class->get_property = gxt_arrow_array_get_property;

  GParamSpec *spec;
  spec = g_param_spec_object("arrow-array",
                             "GArrowArray",
                             "The wrapped Arrow Array",
                             GARROW_TYPE_ARRAY,
                             static_cast<GParamFlags>(G_PARAM_WRITABLE |
                                                      G_PARAM_CONSTRUCT_ONLY));
  g_object_class_install_property(gobject_class, PROP_ARROW_ARRAY, spec);
}

/**
 * gxt_arrow_array_new:
 * @arrow_array: The Arrow array.
 *
 * Returns: A newly created #GXtArrowArray.
 *
 * Since: 1.0.0
 */
GXtArrowArray *
gxt_arrow_array_new(GArrowArray *arrow_array)
{
  auto object = g_object_new(GXT_ARROW_TYPE_ARRAY,
                             "arrow-array", arrow_array,
                             NULL);
  return GXT_ARROW_ARRAY(object);
}

/**
 * gxt_arrow_array_get_raw:
 * @array: A #GXtArrowArray.
 *
 * Returns: (transfer none): The internal #GArrowArray. It's owned by
 *   the array. You don't need to call g_object_unref().
 *
 * Since: 1.0.0
 */
GArrowArray *
gxt_arrow_array_get_raw(GXtArrowArray *array)
{
  auto priv = GXT_ARROW_ARRAY_GET_PRIVATE(array);
  return priv->arrow_array;
}

G_END_DECLS
template <typename TYPE>
xt::xtensor_adaptor<xt::xbuffer_adaptor<typename TYPE::c_type>, 1>
gxt_arrow_array_create_tensor(GXtArrowArray *array)
{
  using ArrayType = typename arrow::TypeTraits<TYPE>::ArrayType;

  auto arrow_array = gxt_arrow_array_get_raw(array);
  auto arrow_array_raw = garrow_array_get_raw(arrow_array);
  auto arrow_specific_array_raw =
    std::static_pointer_cast<ArrayType>(arrow_array_raw);
  auto const_values_raw = arrow_specific_array_raw->raw_values();
  auto values_raw = const_cast<typename TYPE::c_type *>(const_values_raw);
  size_t size = arrow_specific_array_raw->length();
  std::array<size_t, 1> shape = {size};
  return xt::xadapt(values_raw,
                    size,
                    xt::no_ownership(),
                    shape);
}

template <typename TYPE>
GXtArrowArray *
gxt_arrow_array_new_xtensor(xt::xtensor_adaptor<xt::xbuffer_adaptor<typename TYPE::c_type>, 1> &tensor)
{
  auto type = arrow::TypeTraits<TYPE>::type_singleton();
  auto pool = arrow::default_memory_pool();
  typename arrow::TypeTraits<TYPE>::BuilderType builder(type, pool);
  for (auto element : tensor) {
    builder.Append(element);
  }
  std::shared_ptr<arrow::Array> arrow_array_raw;
  builder.Finish(&arrow_array_raw);
  auto arrow_array = garrow_array_new_raw(&arrow_array_raw);
  return gxt_arrow_array_new(arrow_array);
}

template <typename TYPE>
GXtArrowArray *
gxt_arrow_array_new_xtensor(xt::xtensor_container<xt::uvector<typename TYPE::c_type>, 1> &tensor)
{
  auto type = arrow::TypeTraits<TYPE>::type_singleton();
  auto pool = arrow::default_memory_pool();
  typename arrow::TypeTraits<TYPE>::BuilderType builder(type, pool);
  for (auto element : tensor) {
    builder.Append(element);
  }
  std::shared_ptr<arrow::Array> arrow_array_raw;
  builder.Finish(&arrow_array_raw);
  auto arrow_array = garrow_array_new_raw(&arrow_array_raw);
  return gxt_arrow_array_new(arrow_array);
}
G_BEGIN_DECLS

/**
 * gxt_arrow_array_to_string:
 * @array: A #GXtArrowArray.
 *
 * Returns: (nullable): The formatted array content.
 *
 *   The returned string should be freed when with g_free() when no
 *   longer needed.
 *
 * Since: 1.0.0
 */
gchar *
gxt_arrow_array_to_string(GXtArrowArray *array)
{
  std::stringstream sink;
  auto tensor = gxt_arrow_array_create_tensor<arrow::DoubleType>(array);
  sink << tensor;
  return g_strdup(sink.str().c_str());
}

G_END_DECLS
namespace {
  template <typename TYPE, typename OPERATOR>
  GXtArrowArray *apply(GXtArrowArray *array1,
                       GXtArrowArray *array2)
  {
    auto tensor1 = gxt_arrow_array_create_tensor<TYPE>(array1);
    auto tensor2 = gxt_arrow_array_create_tensor<TYPE>(array2);
    auto expression = OPERATOR::apply(tensor1, tensor2);
    auto result = xt::eval(expression);
    return gxt_arrow_array_new_xtensor<TYPE>(result);
  }
}

namespace {
  template<typename TYPE>
  struct plus {
    using Tensor =
      xt::xtensor_adaptor<xt::xbuffer_adaptor<typename TYPE::c_type>, 1>;
    static decltype(auto)
    apply(const Tensor &tensor1, const Tensor &tensor2) {
      return tensor1 + tensor2;
    }
  };
}
G_BEGIN_DECLS

/**
 * gxt_arrow_array_plus:
 * @array1: The addend.
 * @array2: The augend.
 *
 * Returns: (transfer full): The expression to run plus.
 *
 * Since: 1.0.0
 */
GXtArrowArray *
gxt_arrow_array_plus(GXtArrowArray *array1,
                     GXtArrowArray *array2)
{
  return apply<arrow::DoubleType, plus<arrow::DoubleType>>(array1, array2);
}

G_END_DECLS
