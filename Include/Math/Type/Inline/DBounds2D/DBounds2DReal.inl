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
DBounds2D<TType, std::enable_if_t<kIsRealType<TType>>>
::DBounds2D(const DVector2<TValueType>& point)
  : __mMin{point}, __mMax{point}
{ }

template <typename TType>
DBounds2D<TType, std::enable_if_t<kIsRealType<TType>>>
::DBounds2D(const DVector2<TValueType>& point1, const DVector2<TValueType>& point2)
  : __mMin{std::min(point1.X, point2.X), std::min(point1.Y, point2.Y)},
    __mMax{std::max(point1.X, point2.X), std::max(point1.Y, point2.Y)}
{ }

template <typename TType>
template <typename TAnotherType>
DBounds2D<TType, std::enable_if_t<kIsRealType<TType>>>
::operator DBounds2D<TAnotherType>() const noexcept
{
  return {
    static_cast<DVector2<TAnotherType>>(this->GetMinimumPoint()), 
    static_cast<DVector2<TAnotherType>>(this->GetMaximumPoint())
  };
}

template <typename TType>
TReal DBounds2D<TType, std::enable_if_t<kIsRealType<TType>>>
::GetArea() const noexcept
{
  const auto diagonal = this->GetDiagonal();
  return static_cast<TReal>(diagonal.X * diagonal.Y);
}

template <typename TType>
const DVector2<TType>& DBounds2D<TType, std::enable_if_t<kIsRealType<TType>>>
::GetMinimumPoint() const noexcept
{
  return this->__mMin;
}

template <typename TType>
const DVector2<typename DBounds2D<TType, std::enable_if_t<kIsRealType<TType>>>::TValueType>& 
DBounds2D<TType, std::enable_if_t<kIsRealType<TType>>>
::GetMaximumPoint() const noexcept
{
  return this->__mMax;
}

template <typename TType>
DVector2<typename DBounds2D<TType, std::enable_if_t<kIsRealType<TType>>>::TValueType> 
DBounds2D<TType, std::enable_if_t<kIsRealType<TType>>>
::GetDiagonal() const noexcept
{
  return this->__mMax - this->__mMin;
}

template<typename TType>
bool DBounds2D<TType, std::enable_if_t<kIsRealType<TType>>>::HasNaN() const noexcept
{
  return 
      this->__mMin.HasNan() == true
  ||  this->__mMax.HasNan() == true; 
}

template<typename TType>
bool DBounds2D<TType, std::enable_if_t<kIsRealType<TType>>>::HasInfinity() const noexcept
{
  return 
      this->__mMin.HasInfinity() == true
  ||  this->__mMax.HasInfinity() == true;
}

template<typename TType>
bool DBounds2D<TType, std::enable_if_t<kIsRealType<TType>>>::HasOnlyNormal() const noexcept
{
  return 
      this->__mMin.HasOnlyNormal() == true
  &&  this->__mMax.HasOnlyNormal() == true;
}

} /// ::dy::math namespace