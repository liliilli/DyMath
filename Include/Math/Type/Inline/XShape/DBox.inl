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

#include <Math/Type/Shape/DBox.h>
#include <cassert>
#include <cmath>
#include <algorithm>

namespace dy::math
{

template<typename TType>
inline DBox<TType>::DBox(const DVector3<TValueType>& origin, 
  TValueType right, TValueType left, 
  TValueType up, TValueType down, 
  TValueType front, TValueType back)
  : mOrigin{ origin },
    mLength{ right, left, up, down, front, back }
{
  for (const auto& item : this->mLength) { assert(item > 0.0f); }
}

template<typename TType>
inline DBox<TType>::DBox(const DVector3<TValueType>& origin, const DVector3<TValueType>& length)
  : DBox{ origin, length.X, length.X, length.Y, length.Y, length.Z, length.Z }
{ }

template<typename TType>
inline DBox<TType>::DBox(const DVector3<TValueType>& origin, TValueType right, TValueType up, TValueType down)
  : DBox{ origin, {right, up, down} }
{ }

template<typename TType>
inline DBox<TType>::DBox(const DVector3<TValueType>& origin, TValueType length)
  : DBox{ origin, length, length, length }
{ }

template<typename TType>
inline typename DBox<TType>::TValueType 
DBox<TType>::GetLengthOf(EBoxDir direction) const noexcept
{
  return this->mLength[static_cast<std::underlying_type_t<decltype(direction)>>(direction)];
}

template<typename TType>
inline const DVector3<typename DBox<TType>::TValueType>& 
DBox<TType>::GetOrigin() const noexcept
{
  return this->mOrigin;
}

template <typename TType>
inline DVector3<typename DBox<TType>::TValueType>
DBox<TType>::GetMinPos() const noexcept
{
  return 
      this->GetOrigin() 
    - DVector3<TValueType>{this->GetLengthOf(EBoxDir::Left), this->GetLengthOf(EBoxDir::Down), this->GetLengthOf(EBoxDir::Back)};
}

template <typename TType>
inline DVector3<typename DBox<TType>::TValueType>
DBox<TType>::GetMaxPos() const noexcept
{
  return 
      this->GetOrigin() 
    + DVector3<TValueType>{this->GetLengthOf(EBoxDir::Right), this->GetLengthOf(EBoxDir::Up), this->GetLengthOf(EBoxDir::Front)};
}

template<typename TType>
inline bool DBox<TType>::IsSymmetrical() const noexcept
{
  using EDir = EBoxDir;
  return 
      (this->GetLengthOf(EDir::Right) == this->GetLengthOf(EDir::Left))
  &&  (this->GetLengthOf(EDir::Up) == this->GetLengthOf(EDir::Down))
  &&  (this->GetLengthOf(EDir::Front) == this->GetLengthOf(EDir::Back));
}

template<typename TType>
inline bool DBox<TType>::IsSquare() const noexcept
{
  using EDir = EBoxDir;
  return 
      this->IsSymmetrical() 
  &&  (this->GetLengthOf(EDir::Right) == this->GetLengthOf(EDir::Up))
  &&  (this->GetLengthOf(EDir::Right) == this->GetLengthOf(EDir::Front));
}

template<typename TType>
inline bool DBox<TType>::HasNaN() const noexcept
{
  return this->mOrigin.HasNaN() 
      || std::any_of(
          this->mLength.begin(), this->mLength.end(), 
          [](const auto& value) { return std::isnan(value); }
        );
}

template<typename TType>
inline bool DBox<TType>::HasInfinity() const noexcept
{
  return this->mOrigin.HasNaN() 
      || std::any_of(
          this->mLength.begin(), this->mLength.end(), 
          [](const auto& value) { return std::isinf(value); }
        );
}

template<typename TType>
inline bool DBox<TType>::HasOnlyNormal() const noexcept
{
  return this->mOrigin.HasNaN() 
      || std::any_of(
          this->mLength.begin(), this->mLength.end(), 
          [](const auto& value) { return std::isnormal(value); }
        );
}

} /// ::dy::math namespace