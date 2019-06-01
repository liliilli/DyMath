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

/// @class DGridXIterator
/// @tparam TType 
/// @brief
template <typename TType>
class DGridXIterator final
{
public:
  using value_type = TType;
  using size_type = std::size_t;
  using difference_type = signed int;
  // The type std::iterator_traits<It>::reference must be exactly 
  // T& if It satisfies LegacyOutputIterator (It is mutable) [LegacyForwardIterator]
  using reference = value_type&;
  using pointer = value_type*;
  using iterator_category = std::random_access_iterator_tag;
  
  // The type It satisfies DefaultConstructible [LegacyForwardIterator]
  DGridXIterator() = default;
  DGridXIterator(value_type*& pColStart, size_type colLength)
    : mpItem{ pColStart }, mCol { colLength }
  { };

  // CopyConstructible [LegacyIterator]
  DGridXIterator(const DGridXIterator&) = default;
  // CopyAssignable [LegacyIterator]
  DGridXIterator& operator=(const DGridXIterator&) = default;

  // lvalues of type It satisfy Swappable, [LegacyIterator]
  void swap(DGridXIterator& other)
  {
    std::swap(this->mpItem, other.mpItem);
    std::swap(this->mCol, other.mCol);
  }

  // r is dereferenceable (see below) [LegacyIterator]
  reference operator*() { return *this->mpItem; }
  const reference operator*() const { return *this->mpItem; }

  // r is incrementable (the behavior of the expression ++r is defined) [LegacyIterator]
  DGridXIterator& operator++()
  {
    ++this->mpItem;
    return *this;
  }

  // r is incrementable (the behavior of the expression ++r is defined) [LegacyInputIterator]
  DGridXIterator operator++(int) 
  {
    DGridXIterator<value_type> returnInstance = *this; 
    ++(*this);
    return returnInstance;
  }

  // a is decrementable (there exists such b that a == ++b) [LegacyBidirectionalIterator]
  DGridXIterator& operator--()
  {
    --this->mpItem;
    return *this;
  }
  // a is decrementable (there exists such b that a == ++b) [LegacyBidirectionalIterator]
  DGridXIterator operator--(int)
  {
    DGridXIterator<value_type> returnInstance = *this; 
    --(*this);
    return returnInstance;
  }

  // r += n [LegacyRandomAccessIterator]
  DGridXIterator& operator+=(const difference_type& b)
  {
    difference_type m = b;
    if (m >= 0) { while (m--) ++(*this); }
    else        { while (m++) --(*this); }

    return *this;
  }
  // r -= n [LegacyRandomAccessIterator]
  DGridXIterator& operator-=(const difference_type& b)
  {
    return (*this) += -b;
  }
    
  // EqualityComparable [LegacyIterator]
  bool operator==(const DGridXIterator<TType>& b) const noexcept
  {
    return 
        (this->mpItem == b.mpItem)
    &&  (this->mCol == b.mCol);
  }

  // Precondition: i is dereferenceable. [LegacyInputIterator] 
  pointer operator->() { return this->mpItem; }
  const pointer operator->() const { return this->mpItem; }

  reference operator[](std::size_t b)
  {
    return *(this->mpItem + b);
  }
  const reference operator[](std::size_t b) const
  {
    return *(this->mpItem + b);
  }

  size_type GetLength() const noexcept { return this->mCol; }

  pointer begin() noexcept
  {
    return this->mpItem;
  }

  pointer end() noexcept
  {
    return this->mpItem + this->mCol;
  }

private:
  value_type* mpItem = nullptr;
  size_type   mCol = 0;
};

template <typename TType>
void swap(DGridXIterator<TType>& v1, DGridXIterator<TType>& v2)
{
  v1.swap(v2);
}

// EqualityComparable [LegacyInputIterator]
template <typename TType>
bool operator!=(const DGridXIterator<TType>& a, const DGridXIterator<TType>& b)
{
  return !(a == b);
}

template <typename TType>
DGridXIterator<TType> operator+(
  const DGridXIterator<TType> &a, 
  const typename DGridXIterator<TType>::difference_type &b)
{
  auto temp = a;
  return temp += b;
}

template <typename TType>
DGridXIterator<TType> operator+(
  const typename DGridXIterator<TType>::difference_type& b,
  const DGridXIterator<TType>& a)
{
  auto temp = a;
  return temp += b;
}

template <typename TType>
DGridXIterator<TType> operator-(
  const DGridXIterator<TType>& a, 
  const typename DGridXIterator<TType>::difference_type& b)
{
  auto temp = a;
  return temp -= b;
}

template <typename TType>
typename DGridXIterator<TType>::difference_type operator-(
  const DGridXIterator<TType>& b, 
  const DGridXIterator<TType>& a)
{
  if (a.mpItem < b.mpItem)
  {
    typename DGridXIterator<TType>::difference_type n = 0;
    while ((a.mpItem + n) == b.mpItem) { ++n; }

    return n;
  }
  else
  {
    typename DGridXIterator<TType>::difference_type n = 0;
    while ((b.mpItem + n) == a.mpItem) { ++n; }

    return -n;
  }
}

template <typename TType>
bool operator<(const DGridXIterator<TType>& a, const DGridXIterator<TType>& b)
{
  return (b - a) > 0;
}

template <typename TType>
bool operator>(const DGridXIterator<TType>& a, const DGridXIterator<TType>& b)
{
  return b < a;
}

template <typename TType>
bool operator>=(const DGridXIterator<TType>& a, const DGridXIterator<TType>& b)
{
  return !(a < b);
}

template <typename TType>
bool operator<=(const DGridXIterator<TType>& a, const DGridXIterator<TType>& b)
{
  return !(a > b);
}

// Validation Check.
static_assert(std::is_move_constructible_v<DGridXIterator<int>> == true);
static_assert(std::is_copy_constructible_v<DGridXIterator<int>> == true);
static_assert(std::is_move_assignable_v<DGridXIterator<int>> == true);
static_assert(std::is_copy_assignable_v<DGridXIterator<int>> == true);
static_assert(std::is_destructible_v<DGridXIterator<int>> == true);
#ifdef _MSVC_LANG
static_assert(std::_Is_swappable<DGridXIterator<int>>::value == true);
#else
static_assert(std::is_swappable_v<DGridXIterator<int>> == true);
#endif