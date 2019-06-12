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

namespace dy::math
{

template <typename TType>
DVector2<TType> Abs(const DVector2<TType>& vector) noexcept
{
  return {std::abs(vector.X), std::abs(vector.Y)};
}

template <typename TType>
DVector3<TType> Abs(const DVector3<TType>& vector) noexcept
{
  return {std::abs(vector.X), std::abs(vector.Y), std::abs(vector.Z)};
}

template <typename TType>
DVector4<TType> Abs(const DVector4<TType>& vector) noexcept
{
  return {std::abs(vector.X), std::abs(vector.Y), std::abs(vector.Z), std::abs(vector.W)};
}

} /// ::dy::math namespace