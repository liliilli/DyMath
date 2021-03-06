#pragma once
///
/// MIT License
/// Copyright (c) 2018-2019 Jongmin Yun
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
/// SOFTWARE.
///

#include <Math/Common/XRttrEntry.h>

namespace dy::math
{
 
/// @enum ERandomPolicy
/// @brief decides random distribution policy.
enum class ERandomPolicy 
{
  Uniform,  /// Follows uniform distribution.
  Discrete, /// Follows discrete normal distribution.
};

} /// ::dy::math namespace
#ifdef MATH_ENABLE_RTTR
EXPR_BIND_REFLECTION_ENUM(::dy::math::ERandomPolicy);
#endif
