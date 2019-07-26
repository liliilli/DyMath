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

#include <ostream>

namespace dy::math
{

inline DTristateBool::DTristateBool(bool parent, bool input) 
  : __mParent(parent), __mInput(input), __mOutput(parent && input)
{
  this->__mOldOutput = this->__mOutput;
}

inline void DTristateBool::UpdateInput(bool newInput) noexcept
{
  this->__mInput = newInput;
  this->pUpdateOutputs();
}

inline void DTristateBool::UpdateParent(bool newParent) noexcept
{
  this->__mParent = newParent;
  this->pUpdateOutputs();
}

inline bool DTristateBool::GetParentFlag() const noexcept
{
  return this->__mParent;
}

inline bool DTristateBool::GetOutput() const noexcept
{
  return this->__mOutput;
}

inline bool DTristateBool::IsOutputValueChanged() const noexcept
{
  return this->__mOutput != this->__mOldOutput;
}

inline DTristateBool::operator bool() const noexcept
{
  return this->__mOutput;
}

inline void DTristateBool::pUpdateOutputs()
{
  this->__mOldOutput = this->__mOutput;
  this->__mOutput    = this->__mParent && this->__mInput;
}

template <typename TChar, typename TTraits>
std::basic_ostream<TChar, TTraits>&
operator<<(std::basic_ostream<TChar, TTraits>& os, const DTristateBool& vec)
{
  os << "[Parent : " << vec.GetParentFlag() << ", Output : " << vec.GetOutput() << ']';
  return os;
}

} /// ::dy::math namespace