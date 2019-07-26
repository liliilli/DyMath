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

//!
//! Specialized reflection ::dy::math::DClamp<T, S, E> type resolver.
//!

#if 0
template <typename TValue, ::dy::math::TI64 TStart, ::dy::math::TI64 TEnd>
class RReflectionDClamp final : public DType
{
public:
  RReflectionDClamp()
  {
    // Compile time branch for creating this->mTypeName.
    // If true, defer it until this->GetTypeName() is called.
    if constexpr (::dy::expr::reflect::IsPrimitiveTypeFunctionExist<TValueType> == false)
    {
      this->mTypeName = "DClamp<unknown type, unknown, unknown>";
    }
    else
    {
      this->mpInternalType = ::dy::expr::reflect::RReflectionTypeResolver<TValue>::Get();
    }

    // Common
    this->mHashValue  = ::dy::expr::ToHashCrc32("::dy::expr::DClamp");
    this->mTypeSize   = sizeof(::dy::math::DClamp<TValue, TStart, TEnd>);
    this->mIsPod      = std::is_pod_v<::dy::math::DClamp<TValue, TStart, TEnd>>;
  };
  virtual ~RReflectionDClamp() = default;

private:
  /// @brief The pointer of internal type `TValueType`.
  ::dy::expr::reflect::DType* mpInternalType = nullptr;

  /// @brief TypeName lazy intialization function.
  const std::string& GetTypeName() const noexcept override final 
  {
    static bool isTypeNameUpdated = false;
    if (this->mpInternalType != nullptr && isTypeNameUpdated == false)
    {
      assert(this->mpInternalType != nullptr);
      this->mTypeName = 
          "DClamp<" + this->mpInternalType->GetTypeName() + std::to_string(TStart) + ", " + std::to_string(TEnd) + ">";
      isTypeNameUpdated = true;
    }

    return DType::GetTypeName();
  }

  /// @brief
  std::string DumpType(const void* pObj, std::size_t indent) const override final
  {
    const std::string indent0 = std::string(2 * indent, ' ');
    const std::string indent1 = std::string(2 * (indent + 1), ' ');
    const std::unique_ptr<TValueType>& smtObj = *(const std::unique_ptr<TValueType>*)pObj;

    std::stringstream stream;
    stream 
      << ::dy::expr::reflect::DType::DumpType(pObj, indent)
      << indent0 << R"("start" : ")" << TStart << ",\n";
      << indent0 << R"("end" : ")" << TEnd << ",\n";
      << indent0 << R"("value" : )" << *(TValue const*)pObj << "\n";

    return stream.str();
  }
};

template <typename TValue, ::dy::math::TI64 TStart, ::dy::math::TI64 TEnd>
class ::dy::expr::reflect::RReflectionTypeResolver<::dy::math::DClamp<TValue, TStart, TEnd>> final
{
public:
  static DType* Get() 
  { 
    static RReflectionDClamp<TValue, TStart, TEnd> instance;
    return &instance;
  }
};
#endif
