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

#define GXT_TYPE_ARRAY                          \
  (gxt_array_get_type())
#define GXT_ARRAY(obj)                          \
  (G_TYPE_CHECK_INSTANCE_CAST((obj),            \
                              GXT_TYPE_ARRAY,   \
                              GXtArray))
#define GXT_ARRAY_CLASS(klass)                  \
  (G_TYPE_CHECK_CLASS_CAST((klass),             \
                           GXT_TYPE_ARRAY,      \
                           GXtArrayClass))
#define GXT_IS_ARRAY(obj)                       \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj),            \
                              GXT_TYPE_ARRAY))
#define GXT_IS_ARRAY_CLASS(klass)               \
  (G_TYPE_CHECK_CLASS_TYPE((klass),             \
                           GXT_TYPE_ARRAY))
#define GXT_ARRAY_GET_CLASS(obj)                \
  (G_TYPE_INSTANCE_GET_CLASS((obj),             \
                             GXT_TYPE_ARRAY,    \
                             GXtArrayClass))

typedef struct _GXtArray         GXtArray;
typedef struct _GXtArrayClass    GXtArrayClass;

/**
 * GXtArray:
 *
 * It wraps `xt::xarray<double>`.
 */
struct _GXtArray
{
  /*< private >*/
  GObject parent_instance;
};

struct _GXtArrayClass
{
  GObjectClass parent_class;
};

GType gxt_array_get_type(void) G_GNUC_CONST;

GXtArray *gxt_array_new(void);

gchar *gxt_array_to_string(GXtArray *array);

G_END_DECLS
