# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

class TestDoubleArray < Test::Unit::TestCase
  def array(data)
    shape = compute_shape(data)
    values = data.flatten
    XtensorArrow::DoubleArray.new(shape, values)
  end

  def compute_shape(data)
    shape = []
    while data.is_a?(Array)
      shape << data.size
      data = data[0]
    end
    shape
  end

  def setup
    @array = array([
                     [1, 2, 3],
                     [4, 5, 6],
                     [7, 8, 9],
                   ])
  end

  def test_to_s
    assert_equal(<<-ARRAY.chomp, @array.to_s)
{{ 1.,  2.,  3.},
 { 4.,  5.,  6.},
 { 7.,  8.,  9.}}
    ARRAY
  end

  def test_plus
    assert_equal(<<-ARRAY.chomp, @array.plus(array([10.0, 11.0, 12.0])).to_s)
{{ 11.,  13.,  15.},
 { 14.,  16.,  18.},
 { 17.,  19.,  21.}}
    ARRAY
  end

  def test_pow
    assert_equal(<<-ARRAY.chomp, @array.pow(array([2, 3, 4])).to_s)
{{    1.,     8.,    81.},
 {   16.,   125.,  1296.},
 {   49.,   512.,  6561.}}
    ARRAY
  end
end
