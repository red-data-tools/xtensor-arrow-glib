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

#define GXT_ARROW_TYPE_DOUBLE_ARRAY             \
  (gxt_arrow_double_array_get_type())
#define GXT_ARROW_DOUBLE_ARRAY(obj)                             \
  (G_TYPE_CHECK_INSTANCE_CAST((obj),                            \
                              GXT_ARROW_TYPE_DOUBLE_ARRAY,      \
                              GXtArrowDoubleArray))
#define GXT_ARROW_DOUBLE_ARRAY_CLASS(klass)             \
  (G_TYPE_CHECK_CLASS_CAST((klass),                     \
                           GXT_ARROW_TYPE_DOUBLE_ARRAY, \
                           GXtArrowDoubleArrayClass))
#define GXT_ARROW_IS_DOUBLE_ARRAY(obj)                          \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj),                            \
                              GXT_ARROW_TYPE_DOUBLE_ARRAY))
#define GXT_ARROW_IS_DOUBLE_ARRAY_CLASS(klass)                  \
  (G_TYPE_CHECK_CLASS_TYPE((klass),                             \
                           GXT_ARROW_TYPE_DOUBLE_ARRAY))
#define GXT_ARROW_DOUBLE_ARRAY_GET_CLASS(obj)                   \
  (G_TYPE_INSTANCE_GET_CLASS((obj),                             \
                             GXT_ARROW_TYPE_DOUBLE_ARRAY,       \
                             GXtArrowDoubleArrayClass))

typedef struct _GXtArrowDoubleArray         GXtArrowDoubleArray;
typedef struct _GXtArrowDoubleArrayClass    GXtArrowDoubleArrayClass;

/**
 * GXtArrowDoubleArray:
 *
 * It wraps `gxt_arrow::double_array_adaptor`.
 */
struct _GXtArrowDoubleArray
{
  /*< private >*/
  GObject parent_instance;
};

struct _GXtArrowDoubleArrayClass
{
  GObjectClass parent_class;
};

GType gxt_arrow_double_array_get_type(void) G_GNUC_CONST;

GXtArrowDoubleArray *gxt_arrow_double_array_new(const gsize *shape,
                                                gsize n_dimensions);
GXtArrowDoubleArray *gxt_arrow_double_array_new_values(const gsize *shape,
                                                       gsize n_dimensions,
                                                       const gdouble *values,
                                                       gsize n_values);

gchar *gxt_arrow_double_array_to_string(GXtArrowDoubleArray *array);

GXtArrowDoubleArray *
gxt_arrow_double_array_reshape(GXtArrowDoubleArray *array,
                               const gsize *shape,
                               gsize n_dimensions);
GXtArrowDoubleArray *
gxt_arrow_double_array_set_values(GXtArrowDoubleArray *array,
                                  const gdouble *values,
                                  gsize n_values);

GXtArrowDoubleArray *
gxt_arrow_double_array_plus(GXtArrowDoubleArray *array1,
                            GXtArrowDoubleArray *array2);
GXtArrowDoubleArray *
gxt_arrow_double_array_pow(GXtArrowDoubleArray *array1,
                           GXtArrowDoubleArray *array2);

G_END_DECLS
