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

#include <arrow-glib/array.h>

G_BEGIN_DECLS

#define GXT_ARROW_TYPE_ARRAY                    \
  (gxt_arrow_array_get_type())
#define GXT_ARROW_ARRAY(obj)                            \
  (G_TYPE_CHECK_INSTANCE_CAST((obj),                    \
                              GXT_ARROW_TYPE_ARRAY,     \
                              GXtArrowArray))
#define GXT_ARROW_ARRAY_CLASS(klass)                    \
  (G_TYPE_CHECK_CLASS_CAST((klass),                     \
                           GXT_ARROW_TYPE_ARRAY,        \
                           GXtArrowArrayClass))
#define GXT_ARROW_IS_ARRAY(obj)                         \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj),                    \
                              GXT_ARROW_TYPE_ARRAY))
#define GXT_ARROW_IS_ARRAY_CLASS(klass)                 \
  (G_TYPE_CHECK_CLASS_TYPE((klass),                     \
                           GXT_ARROW_TYPE_ARRAY))
#define GXT_ARROW_ARRAY_GET_CLASS(obj)                  \
  (G_TYPE_INSTANCE_GET_CLASS((obj),                     \
                             GXT_ARROW_TYPE_ARRAY,      \
                             GXtArrowArrayClass))

typedef struct _GXtArrowArray         GXtArrowArray;
typedef struct _GXtArrowArrayClass    GXtArrowArrayClass;

/**
 * GXtArrowArray:
 *
 * It wraps `GArrowArray`.
 */
struct _GXtArrowArray
{
  /*< private >*/
  GObject parent_instance;
};

struct _GXtArrowArrayClass
{
  GObjectClass parent_class;
};

GType gxt_arrow_array_get_type(void) G_GNUC_CONST;

GXtArrowArray *gxt_arrow_array_new(GArrowArray *arrow_array);

GArrowArray *gxt_arrow_array_get_raw(GXtArrowArray *array);

gchar *gxt_arrow_array_to_string(GXtArrowArray *array);

GXtArrowArray *
gxt_arrow_array_plus(GXtArrowArray *array1,
                     GXtArrowArray *array2);

G_END_DECLS
