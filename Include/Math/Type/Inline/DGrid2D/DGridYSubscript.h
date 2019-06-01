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

#include <cstdint>

template <typename TType>
class DGridYSubscript final
{
public:
  using value_type = TType;
  using size_type  = std::size_t;
  using reference  = value_type&;

  DGridYSubscript(value_type*& ptr, size_type xSize)
    : mPtr{ptr}, mGridX{xSize}
  { }

  reference operator[](std::size_t b)
  {
    return *(mPtr + b);
  }

  const reference operator[](std::size_t b) const
  {
    return *(mPtr + b);
  }

private:
  value_type* mPtr = nullptr;
  size_type mGridX = 0;

};