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

#include <cassert>
#include <memory>
#include <Math/Type/Inline/DGrid2D/DGridYIterator.h>
#include <Math/Type/Inline/DGrid2D/DGridYSubscript.h>

namespace dy::math
{

/// @class DDynamicGrid2D
/// @tparam TType
/// @tparam TAllocator
/// @brief Dynamic (Size-controllable) grid 2d container type that has continuous buffer.
template <typename TType, typename TAllocator = std::allocator<TType>>
class DDynamicGrid2D 
{
public:
  using value_type      = TType;
  using allocator_type  = TAllocator;
  using size_type       = std::size_t;
  using difference_type = std::ptrdiff_t;
  using reference       = value_type&;
  using const_reference = const value_type&;
  using alloc_traits    = std::allocator_traits<TAllocator>;
  using pointer         = typename alloc_traits::pointer;
  using const_pointer   = typename alloc_traits::const_pointer;
  using iterator        = DGridYIterator<value_type>;

  DDynamicGrid2D(size_type x, size_type y);

  template <typename... TArgs>
  DDynamicGrid2D(size_type x, size_type y, TArgs&&... args);

  DDynamicGrid2D(DDynamicGrid2D&& movedInstance) noexcept;

  virtual ~DDynamicGrid2D();

  /// @brief Resize container with col, row and constructor arguments of given type.
  /// col and row arguments must be bigger than 0. Otherwise, undefined behaviour will be happended.
  /// Cropped instance will be released, and other instances move to new serial buffer.
  template <typename... TArgs>
  void Resize(size_type col, size_type row, TArgs&&... initArgs);
  
  /// @brief Get row(y) size of container.
  size_type GetRowSize() const noexcept;

  /// @brief Get column(x) size of container.
  size_type GetColumnSize() const noexcept;

  /// @brief Set given value to [x, y] ( (*this)[y][x] ).
  /// If given x and y is out of range of container, undefined behaviour will be happended.
  void Set(size_type x, size_type y, const_reference value);

  /// @brief Get value reference of [x, y]. ( (*this)[y][x] ).
  /// If given x and y is out of range of container, undefined behaviour will be happended.
  reference Get(size_type x, size_type y);

  /// @brief Get value reference of [x, y]. ( (*this)[y][x] ).
  /// If given x and y is out of range of container, undefined behaviour will be happended.
  const_reference Get(size_type x, size_type y) const;

  /// @brief Get one-dimension serial container buffer pointer.
  pointer Data() noexcept;

  /// @brief Get one-dimension serial container buffer pointer.
  const_pointer Data() const noexcept;

  DGridYSubscript<value_type> operator[](std::size_t b);

  //!
  //! Iterators
  //!

  iterator begin() noexcept;
  iterator end() noexcept;

private:
  TAllocator  mAlloc;
  value_type* mOwnerPtr = nullptr;
  size_type   mGridX = 0;
  size_type   mGridY = 0;
};

} /// ::dy::math namespace
#include <Math/Type/Inline/DGrid2D/DDynamicGrid2D.inl>
