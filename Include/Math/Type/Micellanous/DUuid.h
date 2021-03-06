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
#include <string>
#include <Math/Common/XRttrEntry.h>

#ifdef MATH_ENABLE_UUID
namespace boost::uuids
{

struct uuid;

} /// Forward declaration.

namespace dy::math
{

/// @struct DUuid
/// @brief UUID structure.
/// This uses RAII to avoid build dependency of boost (so many files)
struct DUuid final
{
public:
  /// @brief If true, create new value when creating uuid instance.
  /// Otherwise, just let it empty value (00000000-0000-0000-0000-000000000000)
  explicit DUuid(bool iCreateValue = false);

  /// @brief Check string whether it is uuid string in runtime,
  /// and if true, convert string into uuid value. 
  /// Otherwise, just let it empty with error message.
  ///
  /// If iIsStrict is true, just error and abort program when conversion failed
  /// instead of printing error log.
  explicit DUuid(const std::string& iUuidString, bool iIsStrict = false);

  DUuid(const DUuid& uuid);
  DUuid& operator=(const DUuid& uuid);
  DUuid(DUuid&& uuid) noexcept;
  DUuid& operator=(DUuid&& uuid) noexcept; 
  ~DUuid();

  typedef uint8_t value_type;
  typedef uint8_t& reference;
  typedef uint8_t const& const_reference;
  typedef uint8_t* iterator;
  typedef uint8_t const* const_iterator;
  typedef std::ptrdiff_t difference_type;

  /// @brief Get size of uuid. Returned value is always 16.
  constexpr std::size_t Size() const noexcept 
  { 
    return 16; 
  }

  /// @brief Check uuid has valid value.
  [[nodiscard]] bool HasValue() const;

  /// @brief Return value as string.
  std::string ToString() const;

  // iteration
  iterator begin() noexcept;
  iterator end() noexcept;
  const_iterator begin() const noexcept;
  const_iterator end() const noexcept;

private:
  boost::uuids::uuid* mUuid = nullptr;

  friend struct std::hash<::dy::math::DUuid>;
  friend bool operator==(const DUuid& lhs, const DUuid& rhs) noexcept;
};

bool operator==(const DUuid& lhs, const DUuid& rhs) noexcept;
bool operator!=(const DUuid& lhs, const DUuid& rhs) noexcept;

} /// ::dy::math namespace

namespace std
{

template<> 
struct hash<::dy::math::DUuid>
{
  using argument_type = ::dy::math::DUuid;
  using result_type = std::size_t;
  result_type operator()(argument_type const& s) const noexcept;
};

} /// ::std for hashing of DUuid.

namespace dy::math
{

/// @brief Create UUID instance.
DUuid CreateUuid();

} /// ::dy::math namespace

#ifdef MATH_ENABLE_RTTR
namespace dy::math
{

class DReflectionMathUuid final : public ::dy::expr::reflect::DTypeClass
{
public:
  DReflectionMathUuid() : ::dy::expr::reflect::DTypeClass()
  {
    this->mTypeName   = "DUuid";
    this->mHashValue  = ::dy::expr::ToHashCrc32("DUuid");
    this->mTypeSize   = sizeof(DUuid);
    this->mIsPod      = std::is_pod_v<DUuid>;
  };
  virtual ~DReflectionMathUuid() = default;

private:
  /// @brief
  std::string DumpType(const void* pObj, std::size_t indent) const override final
  {
    const std::string indent0 = std::string(2 * indent, ' ');
    const std::string indent1 = std::string(2 * (indent + 1), ' ');
    const DUuid& obj = *(const DUuid*)pObj;

    std::stringstream stream;
    stream 
      << DType::DumpType(pObj, indent)
      << indent0 << R"("value" : )";
    if (obj.HasValue() == false) 
    {
      stream << R"("uuid is not initialized yet.")";
    }
    else
    {
      stream << R"(")" << obj.ToString() << R"(")";
    }
    stream << "\n";
    return stream.str();
  }
};

} /// ::dy::math namespace

template <>
class ::dy::expr::reflect::RReflectionTypeResolver<::dy::math::DUuid> final
{
public:
  static DType* Get() 
  { 
    static ::dy::math::DReflectionMathUuid instance;
    return &instance;
  }
};
#endif /// MATH_ENABLE_RTTR
#endif /// MATH_ENABLE_UUID from Cmake.