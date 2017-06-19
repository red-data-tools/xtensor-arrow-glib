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

typedef struct GXtArrayPrivate_ {
  xt::xarray<double> *array;
} GXtArrayPrivate;

enum {
  PROP_0,
  PROP_ARRAY
};

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

  delete priv->array;

  G_OBJECT_CLASS(gxt_array_parent_class)->finalize(object);
}

static void
gxt_array_set_property(GObject *object,
                       guint prop_id,
                       const GValue *value,
                       GParamSpec *pspec)
{
  auto priv = GXT_ARRAY_GET_PRIVATE(object);

  switch (prop_id) {
  case PROP_ARRAY:
    priv->array = static_cast<xt::xarray<double> *>(g_value_get_pointer(value));
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
}

static void
gxt_array_get_property(GObject *object,
                       guint prop_id,
                       GValue *value,
                       GParamSpec *pspec)
{
  switch (prop_id) {
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
}

static void
gxt_array_init(GXtArray *object)
{
}

static void
gxt_array_class_init(GXtArrayClass *klass)
{
  GParamSpec *spec;

  auto gobject_class = G_OBJECT_CLASS(klass);

  gobject_class->finalize     = gxt_array_finalize;
  gobject_class->set_property = gxt_array_set_property;
  gobject_class->get_property = gxt_array_get_property;

  spec = g_param_spec_pointer("array",
                              "Array",
                              "The raw xt::xarray<double> *",
                              static_cast<GParamFlags>(G_PARAM_WRITABLE |
                                                       G_PARAM_CONSTRUCT_ONLY));
  g_object_class_install_property(gobject_class, PROP_ARRAY, spec);
}

/**
 * gxt_array_new:
 *
 * Returns: (nullable): A newly created #GXtArray.
 *
 * Since: 1.0.0
 */
GXtArray *
gxt_array_new(void)
{
  auto xt_array = new xt::xarray<double>({
      {1.0, 2.0, 3.0},
      {2.0, 5.0, 7.0},
      {2.0, 5.0, 7.0}
    });
  return gxt_array_new_raw(xt_array);
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
  auto xt_array = gxt_array_get_raw(array);
  std::stringstream sink;
  sink << *xt_array;
  return g_strdup(sink.str().c_str());
}

G_END_DECLS

GXtArray *
gxt_array_new_raw(xt::xarray<double> *xt_array)
{
  auto array = GXT_ARRAY(g_object_new(GXT_TYPE_ARRAY,
                                      "array", xt_array,
                                      NULL));
  return array;
}

xt::xarray<double> *
gxt_array_get_raw(GXtArray *array)
{
  auto priv = GXT_ARRAY_GET_PRIVATE(array);
  return priv->array;
}
