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

template <typename TType, typename TAllocator>
DDynamicGrid2D<TType, TAllocator>::DDynamicGrid2D(size_type x, size_type y)
  : mGridX{x}, mGridY{y}
{
  assert(x > 0 && y > 0);
  this->mOwnerPtr = this->mAlloc.allocate(x * y);
  
  auto* pItem = this->mOwnerPtr;
  for (size_type i = 0, count = x * y; i < count; ++i)
  {
    // Always call default constructor.
    alloc_traits::construct(this->mAlloc, pItem);
    ++pItem;
  }
}

template <typename TType, typename TAllocator>
template <typename ... TArgs>
DDynamicGrid2D<TType, TAllocator>::DDynamicGrid2D(size_type x, size_type y, TArgs&&... args)
  : mGridX{x}, mGridY{y}
{
  assert(x > 0 && y > 0);
  this->mOwnerPtr = this->mAlloc.allocate(x * y);
  
  auto* pItem = this->mOwnerPtr;
  for (size_type i = 0, count = x * y; i < count; ++i)
  {
    // Always call default constructor.
    alloc_traits::construct(this->mAlloc, pItem, std::forward<TArgs>(args)...);
    ++pItem;
  }  
}

template <typename TType, typename TAllocator>
DDynamicGrid2D<TType, TAllocator>::DDynamicGrid2D(DDynamicGrid2D&& movedInstance) noexcept
  : mAlloc{ movedInstance.mAlloc },
    mOwnerPtr { movedInstance.mOwnerPtr },
    mGridX{ movedInstance.mGridX },
    mGridY{ movedInstance.mGridY }
{ 
  movedInstance.mOwnerPtr = nullptr;
}

template <typename TType, typename TAllocator>
DDynamicGrid2D<TType, TAllocator>::~DDynamicGrid2D()
{
  if (this->mOwnerPtr != nullptr)
  {
    auto* pItem = this->mOwnerPtr;
    const auto count = this->mGridX * this->mGridY;
    for (size_type i = 0; i < count; ++i)
    {
      // Call destructor.
      alloc_traits::destroy(this->mAlloc, pItem);
      ++pItem;
    }

    this->mAlloc.deallocate(this->mOwnerPtr, count);
    this->mOwnerPtr = nullptr;
  }
}

template <typename TType, typename TAllocator>
template <typename ... TArgs>
void DDynamicGrid2D<TType, TAllocator>::Resize(size_type col, size_type row, TArgs&&... initArgs)
{
  assert(col > 0 && row > 0);

  const int difCol = static_cast<int>(col) - static_cast<int>(this->mGridX);
  const int difRow = static_cast<int>(row) - static_cast<int>(this->mGridY);

  const int oldCol = static_cast<int>(this->mGridX) + (difCol < 0 ? difCol : 0);
  const int oldRow = static_cast<int>(this->mGridY) + (difRow < 0 ? difRow : 0);

  // Try to allocate new buffer and allocator.
  auto  newAlloc    = TAllocator{};
  auto* pNewBuffer  = newAlloc.allocate(col * row);

  auto* pNewItem  = pNewBuffer;
  auto* pOldItem  = this->mOwnerPtr;
  for (auto y = 0; y < oldRow; ++y)
  {
    // Call move constructor
    for (auto x = 0; x < oldCol; ++x)
    {
      alloc_traits::construct(newAlloc, pNewItem + x, std::move(*(pOldItem + x)));
    }

    // If oldCol < col (newCol), construct new values.... 
    for (auto x = oldCol; x < col; ++x)
    {
      // if sizeof...(initArgs) is not 0.
      if constexpr (sizeof...(initArgs) == 0)
      {
        alloc_traits::construct(newAlloc, pNewItem + x);
      }
      else
      {
        alloc_traits::construct(newAlloc, pNewItem + x, std::forward<TArgs>(initArgs)...);
      }
    }

    pNewItem += col;
    pOldItem += this->mGridX;
  }

  // If oldRow < row (newRow), construct new values...
  for (auto y = oldRow; y < row; ++y)
  {
    for (auto x = 0; x < col; ++x)
    {
      // if sizeof...(initArgs) is not 0.
      if constexpr (sizeof...(initArgs) == 0)
      {
        alloc_traits::construct(newAlloc, pNewItem + x);
      }
      else
      {
        alloc_traits::construct(newAlloc, pNewItem + x, std::forward<TArgs>(initArgs)...);
      }
    }

    pNewItem += col;
  }

  // Destroy and Deallocate old buffer.
  pOldItem = this->mOwnerPtr;
  for (auto y = 0; y < this->mGridY; ++y)
  {
    for (auto x = 0; x < this->mGridX; ++x)
    {
      alloc_traits::destroy(this->mAlloc, pOldItem);
      ++pOldItem;
    }
  }
  this->mAlloc.deallocate(this->mOwnerPtr, this->mGridX * this->mGridY);

  // Replace old variable with new value.
  this->mAlloc = std::move(newAlloc);
  this->mOwnerPtr = pNewBuffer;
  this->mGridX = col;
  this->mGridY = row;
}

template <typename TType, typename TAllocator>
typename DDynamicGrid2D<TType, TAllocator>::size_type 
DDynamicGrid2D<TType, TAllocator>::GetRowSize() const noexcept
{
  return this->mGridY;
}

template <typename TType, typename TAllocator>
typename DDynamicGrid2D<TType, TAllocator>::size_type 
DDynamicGrid2D<TType, TAllocator>::GetColumnSize() const noexcept
{
  return this->mGridX;
}

template <typename TType, typename TAllocator>
void DDynamicGrid2D<TType, TAllocator>::Set(size_type x, size_type y, const_reference value)
{
  assert(x < this->mGridX && y < this->mGridY);
  auto* pItem = mOwnerPtr + (y * mGridX) + x;
  *pItem = value;
}

template <typename TType, typename TAllocator>
typename DDynamicGrid2D<TType, TAllocator>::reference 
DDynamicGrid2D<TType, TAllocator>::Get(size_type x, size_type y)
{
  assert(x < this->mGridX && y < this->mGridY);
  return *(mOwnerPtr + (y * mGridX) + x);
}

template <typename TType, typename TAllocator>
typename DDynamicGrid2D<TType, TAllocator>::const_reference 
DDynamicGrid2D<TType, TAllocator>::Get(size_type x, size_type y) const
{
  assert(x < this->mGridX && y < this->mGridY);
  return *(mOwnerPtr + (y * mGridX) + x);
}

template <typename TType, typename TAllocator>
typename DDynamicGrid2D<TType, TAllocator>::pointer 
DDynamicGrid2D<TType, TAllocator>::Data() noexcept
{
  return this->mOwnerPtr;
}

template <typename TType, typename TAllocator>
typename DDynamicGrid2D<TType, TAllocator>::const_pointer 
DDynamicGrid2D<TType, TAllocator>::Data() const noexcept
{
  return this->mOwnerPtr;
}

template <typename TType, typename TAllocator>
DGridYSubscript<typename DDynamicGrid2D<TType, TAllocator>::value_type> 
DDynamicGrid2D<TType, TAllocator>::operator[](std::size_t b)
{
  value_type* ptr = this->mOwnerPtr + (b * this->mGridX);
  return {ptr, this->mGridX};
}

template <typename TType, typename TAllocator>
typename DDynamicGrid2D<TType, TAllocator>::iterator 
DDynamicGrid2D<TType, TAllocator>::begin() noexcept
{
  return {this->mOwnerPtr, this->mGridY, this->mGridX, 0};
}

template <typename TType, typename TAllocator>
typename DDynamicGrid2D<TType, TAllocator>::iterator 
DDynamicGrid2D<TType, TAllocator>::end() noexcept
{
  return {this->mOwnerPtr, this->mGridY, this->mGridX, this->mGridY};
}

} /// ::dy::math namespace
