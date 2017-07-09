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

#pragma once

#include <glib-object.h>

G_BEGIN_DECLS

#define GXT_TYPE_DOUBLE_ARRAY                   \
  (gxt_double_array_get_type())
#define GXT_DOUBLE_ARRAY(obj)                           \
  (G_TYPE_CHECK_INSTANCE_CAST((obj),                    \
                              GXT_TYPE_DOUBLE_ARRAY,    \
                              GXtDoubleArray))
#define GXT_DOUBLE_ARRAY_CLASS(klass)                   \
  (G_TYPE_CHECK_CLASS_CAST((klass),                     \
                           GXT_TYPE_DOUBLE_ARRAY,       \
                           GXtDoubleArrayClass))
#define GXT_IS_DOUBLE_ARRAY(obj)                        \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj),                    \
                              GXT_TYPE_DOUBLE_ARRAY))
#define GXT_IS_DOUBLE_ARRAY_CLASS(klass)                \
  (G_TYPE_CHECK_CLASS_TYPE((klass),                     \
                           GXT_TYPE_DOUBLE_ARRAY))
#define GXT_DOUBLE_ARRAY_GET_CLASS(obj)                 \
  (G_TYPE_INSTANCE_GET_CLASS((obj),                     \
                             GXT_TYPE_DOUBLE_ARRAY,     \
                             GXtDoubleArrayClass))

typedef struct _GXtDoubleArray         GXtDoubleArray;
typedef struct _GXtDoubleArrayClass    GXtDoubleArrayClass;

/**
 * GXtDoubleArray:
 *
 * It wraps `gxt::double_array_adaptor`.
 */
struct _GXtDoubleArray
{
  /*< private >*/
  GObject parent_instance;
};

struct _GXtDoubleArrayClass
{
  GObjectClass parent_class;
};

GType gxt_double_array_get_type(void) G_GNUC_CONST;

GXtDoubleArray *gxt_double_array_new(const gdouble *values,
                                     gsize n_values);

gchar *gxt_double_array_to_string(GXtDoubleArray *array);

GXtDoubleArray *gxt_double_array_reshape(GXtDoubleArray *array,
                                         const gsize *shape,
                                         gsize n_dimensions);

G_END_DECLS
