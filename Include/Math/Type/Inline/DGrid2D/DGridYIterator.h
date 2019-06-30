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

#include <iterator>
#include <type_traits>
#include <utility>
#include <vector>

#include <Math/Type/Inline/DGrid2D/DGridXIterator.h>

/// @class DGridYIterator
/// @tparam TType 
/// @brief
template <typename TType>
class DGridYIterator final
{
public:
  using value_type      = DGridXIterator<TType>;
  using size_type       = std::size_t;
  using difference_type = signed int;
  // The type std::iterator_traits<It>::reference must be exactly 
  // T& if It satisfies LegacyOutputIterator (It is mutable) [LegacyForwardIterator]
  using reference       = value_type&;
  using const_reference = std::add_lvalue_reference_t <const std::remove_reference_t<reference>>;
  using pointer         = value_type*;
  using iterator_category = std::random_access_iterator_tag;
  
  // The type It satisfies DefaultConstructible [LegacyForwardIterator]
  DGridYIterator() = default;
  DGridYIterator(
    typename value_type::value_type* pBuffer, 
    size_type rowLength, size_type colLength,
    size_type id)
    : mId{ id }
  { 
    for (size_type y = 0; y < rowLength; ++y)
    {
      this->mRowIterators.emplace_back(pBuffer, colLength);
      pBuffer += colLength;
    }
  };

  // CopyConstructible [LegacyIterator]
  DGridYIterator(const DGridYIterator&) = default;
  // CopyAssignable [LegacyIterator]
  DGridYIterator& operator=(const DGridYIterator&) = default;

  // lvalues of type It satisfy Swappable, [LegacyIterator]
  void swap(DGridYIterator& other) noexcept
  {
    std::swap(this->mRowIterators, other.mRowIterators);
    std::swap(this->mId, other.mId);
    std::swap(this->mCol, other.mCol);
  }

  // r is dereferenceable (see below) [LegacyIterator]
  reference operator*()
  {
      return this->mRowIterators[this->mId];
  }
  const_reference operator*() const
  { 
    return this->mRowIterators[this->mId]; 
  }

  // r is incrementable (the behavior of the expression ++r is defined) [LegacyIterator]
  DGridYIterator& operator++()
  {
    ++this->mId;
    return *this;
  }
  // r is incrementable (the behavior of the expression ++r is defined) [LegacyInputIterator]
  DGridYIterator operator++(int) 
  {
    DGridYIterator<value_type> returnInstance = *this; 
    ++(*this);
    return returnInstance;
  }

  // a is decrementable (there exists such b that a == ++b) [LegacyBidirectionalIterator]
  DGridYIterator& operator--()
  {
    --this->mId;
    return *this;
  }
  // a is decrementable (there exists such b that a == ++b) [LegacyBidirectionalIterator]
  DGridYIterator operator--(int)
  {
    DGridYIterator<value_type> returnInstance = *this; 
    --(*this);
    return returnInstance;
  }

  // r += n [LegacyRandomAccessIterator]
  DGridYIterator& operator+=(const difference_type& b)
  {
    difference_type m = b;
    if (m >= 0) { while (m--) ++(*this); }
    else        { while (m++) --(*this); }

    return *this;
  }
  // r -= n [LegacyRandomAccessIterator]
  DGridYIterator& operator-=(const difference_type& b)
  {
    return (*this) += -b;
  }
    
  // EqualityComparable [LegacyIterator]
  bool operator==(const DGridYIterator<TType>& b) const noexcept
  {
    return 
        (this->mRowIterators == b.mRowIterators)
    &&  (this->mId == b.mId)
    &&  (this->mCol == b.mCol);
  }

  // Precondition: i is dereferenceable. [LegacyInputIterator] 
  pointer operator->() 
  { 
    return &this->mRowIterators[this->mId]; 
  }
  const pointer operator->() const 
  { 
    return &this->mRowIterators[this->mId]; 
  }

  reference operator[](std::size_t b) const
  {
    return this->mRowIterators[this->mId + b];
  }

private:
  std::vector<value_type> mRowIterators;
  size_type   mId = 0;
  size_type   mCol = 0;
};

template <typename TType>
void swap(DGridYIterator<TType>& v1, DGridYIterator<TType>& v2) noexcept
{
  v1.swap(v2);
}

// EqualityComparable [LegacyInputIterator]
template <typename TType>
bool operator!=(const DGridYIterator<TType>& a, const DGridYIterator<TType>& b)
{
  return !(a == b);
}

template <typename TType>
DGridYIterator<TType> operator+(
  const DGridYIterator<TType> &a, 
  const typename DGridYIterator<TType>::difference_type &b)
{
  auto temp = a;
  return temp += b;
}

template <typename TType>
DGridYIterator<TType> operator+(
  const typename DGridYIterator<TType>::difference_type& b,
  const DGridYIterator<TType>& a)
{
  auto temp = a;
  return temp += b;
}

template <typename TType>
DGridYIterator<TType> operator-(
  const DGridYIterator<TType>& a, 
  const typename DGridYIterator<TType>::difference_type& b)
{
  auto temp = a;
  return temp -= b;
}

template <typename TType>
typename DGridYIterator<TType>::difference_type operator-(
  const DGridYIterator<TType>& b, 
  const DGridYIterator<TType>& a)
{
  if (a.mpRowStart < b.mpRowStart)
  {
    typename DGridYIterator<TType>::difference_type n = 0;
    while ((a.mpRowStart + n) == b.mpRowStart) { ++n; }

    return n;
  }
  else
  {
    typename DGridYIterator<TType>::difference_type n = 0;
    while ((b.mpRowStart + n) == a.mpRowStart) { ++n; }

    return -n;
  }
}

template <typename TType>
bool operator<(const DGridYIterator<TType>& a, const DGridYIterator<TType>& b)
{
  return (b - a) > 0;
}

template <typename TType>
bool operator>(const DGridYIterator<TType>& a, const DGridYIterator<TType>& b)
{
  return b < a;
}

template <typename TType>
bool operator>=(const DGridYIterator<TType>& a, const DGridYIterator<TType>& b)
{
  return !(a < b);
}

template <typename TType>
bool operator<=(const DGridYIterator<TType>& a, const DGridYIterator<TType>& b)
{
  return !(a > b);
}

// Validation Check.
static_assert(std::is_move_constructible_v<DGridYIterator<int>> == true);
static_assert(std::is_copy_constructible_v<DGridYIterator<int>> == true);
static_assert(std::is_move_assignable_v<DGridYIterator<int>> == true);
static_assert(std::is_copy_assignable_v<DGridYIterator<int>> == true);
static_assert(std::is_destructible_v<DGridYIterator<int>> == true);
#ifdef _MSVC_LANG
static_assert(std::_Is_swappable<DGridYIterator<int>>::value == true);
#else
static_assert(std::is_swappable_v<DGridYIterator<int>> == true);
#endif