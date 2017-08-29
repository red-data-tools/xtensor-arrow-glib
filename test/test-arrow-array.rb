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

class TestArrowArray < Test::Unit::TestCase
  def arrow_array(values)
    builder = Arrow::DoubleArrayBuilder.new
    values.each do |value|
      builder.append(value)
    end
    builder.finish
  end

  def array(values)
    XtensorArrow::Array.new(arrow_array(values))
  end

  def test_to_s
    assert_equal("{ 1.,  2.,  3.}",
                 array([1, 2, 3]).to_s)
  end

  def test_plus
    array1 = array([1, 2, 3])
    array2 = array([10.0, 11.0, 12.0])
    assert_equal("{ 11.,  13.,  15.}",
                 array1.plus(array2).to_s)
  end
end
