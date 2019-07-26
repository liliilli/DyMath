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

#include <Math/Common/XRttrEntry.h>

namespace dy::math
{

/// @class DTristateBool
/// @brief 3-state boolean helper type.
class DTristateBool final
{
public:
  DTristateBool() = default;
  DTristateBool(bool parent, bool input);

  /// @brief Update input boolean value.
  /// @param newInput input value to insert.
  void UpdateInput(bool newInput) noexcept;

  /// @brief Update parent boolean value.
  /// @param newParent parent value to insert.
  void UpdateParent(bool newParent) noexcept;

  /// @brief Get parent's flag (true/false) of this instance.
  /// @return parent flag value.
  bool GetParentFlag() const noexcept;

  /// @brief Get output value.
  /// @return Output value.
  bool GetOutput() const noexcept;

  /// @brief Check output value is changed. but might be ABA problem when values are changed.
  /// @return Check old-output and output, if changed return true or false.
  bool IsOutputValueChanged() const noexcept;

  /// @brief Check output value is true.
  /// @return Output value.
  operator bool() const noexcept;

  //! Tri-state boolean
  //!
  //!       mParent----.                Parent | Input | Output
  //!               __ |                     X |     X |      X
  //!              |  \o                     X |     O |      X
  //! mInput _____o|   \_____o mOutput       O |     X |      X
  //!              |   /                     O |     O |      O
  //!              |__/
  //!

  /// Parent boolean value.
  bool __mParent = false;

  /// Input boolean value.
  bool __mInput = false;

  /// Output boolean value.
  mutable bool __mOutput = false;

  /// Old-output boolean value (previous output value)
  mutable bool __mOldOutput = false;

private:
  /// @brief Update output / oldOutput value comparing parent and input.
  void pUpdateOutputs();

#ifdef MATH_ENABLE_RTTR
  EXPR_BIND_REFLECTION();
#endif
};

} /// ::dy::math namespace
#include <Math/Type/Inline/Micellanous/DTristateBool.inl>
