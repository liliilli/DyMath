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
DArea2D<TType, std::enable_if_t<kIsIntegerType<TType>>>
::DArea2D(const DVector2<TValueType>& iStartPoint, const DVector2<TValueType>& iLength)
  : __mStartPoint{iStartPoint},
    __mLength{iLength}
{ 
  if constexpr (kCategoryOf<TType> == EValueCategory::Signed)
  {
    this->RelocatePosition();
  }
}

template <typename TType>
DArea2D<TType, std::enable_if_t<kIsIntegerType<TType>>>
::DArea2D(TValueType x, TValueType y, TValueType width, TValueType height)
  : __mStartPoint{x, y},
    __mLength{width, height}
{
  if constexpr (kCategoryOf<TType> == EValueCategory::Signed)
  {
    this->RelocatePosition();
  }
}

template <typename TType>
template <typename TAnotherType>
DArea2D<TType, std::enable_if_t<kIsIntegerType<TType>>>
::operator DArea2D<TAnotherType>() const noexcept
{
  using AnotherType = typename DVector2<
    TAnotherType, 
    std::enable_if_t<kIsIntegerType<TAnotherType> || kIsRealType<TAnotherType>>>::TValueType; 

  using TVectorType = DVector2<AnotherType>;
  return DArea2D
  {
    Cast<TVectorType>(this->__mStartPoint), 
    Cast<TVectorType>(this->__mLength)
  };
}

template <typename TType>
TReal DArea2D<TType, std::enable_if_t<kIsIntegerType<TType>>>
::GetArea() const noexcept
{
  const auto& value = this->__mLength;
  return static_cast<TReal>(value[0] * value[1]);
}

template <typename TType>
void DArea2D<TType, std::enable_if_t<kIsIntegerType<TType>>>
::SetStartPoint(const DVector2<TValueType>& iStartPoint)
{
  this->__mStartPoint = iStartPoint;
}

template <typename TType>
const DVector2<typename DArea2D<TType, std::enable_if_t<kIsIntegerType<TType>>>::TValueType>& 
DArea2D<TType, typename std::enable_if<kIsIntegerType<TType>>::type>
::GetStartPoint() const noexcept
{
  return this->__mStartPoint;
}

template <typename TType>
DVector2<typename DArea2D<TType, std::enable_if_t<kIsIntegerType<TType>>>::TValueType> 
DArea2D<TType, typename std::enable_if<kIsIntegerType<TType>>::type>
::GetEndPoint() const noexcept
{
  return this->__mStartPoint + this->__mLength;
}

template <typename TType>
void DArea2D<TType, std::enable_if_t<kIsIntegerType<TType>>>
::SetWidth(TValueType width) noexcept
{
  this->__mLength.X = width;
  if constexpr (kCategoryOf<TType> == EValueCategory::Signed)
  {
    this->RelocatePosition();
  }
}

template <typename TType>
typename DArea2D<TType, std::enable_if_t<kIsIntegerType<TType>>>::TValueType 
DArea2D<TType, typename std::enable_if<kIsIntegerType<TType>>::type>
::GetWidth() const noexcept
{
  return this->__mLength.X;
}

template <typename TType>
void DArea2D<TType, std::enable_if_t<kIsIntegerType<TType>>>
::SetHeight(TValueType height) noexcept
{
  this->__mLength.Y = height;
  if constexpr (kCategoryOf<TType> == EValueCategory::Signed)
  {
    this->RelocatePosition();
  }
}

template <typename TType>
typename DArea2D<TType, std::enable_if_t<kIsIntegerType<TType>>>::TValueType 
DArea2D<TType, typename std::enable_if<kIsIntegerType<TType>>::type>
::GetHeight() const noexcept
{
  return this->__mLength.Y;
}

template<typename TType>
void DArea2D<TType, std::enable_if_t<kIsIntegerType<TType>>>
::SetWh(const DVector2<TValueType>& wh)
{
  this->__mLength = wh;
  if constexpr (kCategoryOf<TType> == EValueCategory::Signed)
  {
    this->RelocatePosition();
  }
}

template<typename TType>
DVector2<TType> 
DArea2D<TType, std::enable_if_t<kIsIntegerType<TType>>>
::GetWh() const noexcept
{
  return DVector2<TValueType>{this->GetWidth(), this->GetHeight()};
}

template <typename TType>
void DArea2D<TType, std::enable_if_t<kIsIntegerType<TType>>>
::RelocatePosition()
{
  // When width is negative value.
  if (this->__mLength.X < 0) 
  { 
    this->__mStartPoint.X += this->__mLength.X; 
    this->__mLength.X = std::abs(this->__mLength.X); 
  }
  // When height is negative value.
  if (this->__mLength.Y < 0) 
  { 
    this->__mStartPoint.Y += this->__mLength.Y; 
    this->__mLength.Y = std::abs(this->__mLength.Y); 
  }
}

} /// ::dy::math namespace