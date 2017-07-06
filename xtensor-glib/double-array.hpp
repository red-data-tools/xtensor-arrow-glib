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

#include <xtensor/xadapt.hpp>

#include <xtensor-glib/double-array.h>

namespace gxt {
  using double_buffer_adaptor =
    xt::xbuffer_adaptor<double, xt::acquire_ownership>;
  using double_array_adaptor =
    xt::xarray_adaptor<double_buffer_adaptor,
                       xt::layout_type::dynamic,
                       std::vector<size_t>>;
}
