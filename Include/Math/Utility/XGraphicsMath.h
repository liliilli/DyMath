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

#include <optional>

#include <Math/Type/Math/DMatrix4.h>
#include <Math/Type/Micellanous/EGraphics.h>
#include <Math/Type/Micellanous/EProjection.h>

#include <Math/Type/Shape/DRay.h>
#include <Math/Type/Shape/DSphere.h>
#include <Math/Type/Shape/DBox.h>
#include <Math/Type/Shape/DPlane.h>
#include <Math/Type/Shape/DTorus.h>
#include <Math/Type/Shape/DCone.h>
#include <Math/Type/Shape/DCapsule.h>

namespace dy::math
{

//!
//! Camera & View Screen
//!

/// @brief Create projection matrix following graphics and project value.
/// Dy system use right-hand coorindate system, so each EGraphics value create matrix of each variant version.
/// @tparam TType result type.
template <typename TType>
DMatrix4<TType> ProjectionMatrix(
  EGraphics graphics, EProjection project,
  TReal left, TReal right, TReal botton, TReal top, TReal near, TReal far);

/// @brief Create projection matrix following graphics and project value.
/// Dy system use right-hand coorindate system, so each EGraphics value create matrix of each variant version.
/// @tparam TType result type.
template <typename TType>
DMatrix4<TType> ProjectionMatrix(
  EGraphics graphics, EProjection project,
  TReal fovY, TReal width, TReal height, TReal near, TReal far);

/// @brief Create look-at matrix.
/// This function does only support OpenGL look-at matrix.
/// Recommend to use LookAt2 function.
template <typename TType>
[[deprecated("This function does not support variant API. Use LookAt2.")]] DMatrix4<TType> LookAt(
  const DVector3<TType>& position, 
  const DVector3<TType>& lookPosition,
  const DVector3<TType>& unitY);

/// @brief Create look-at matrix. 
/// This function automatically normalize calculated right, up, front vector.
/// @param graphics Graphics API value.
/// @param position position.
/// @param lookPosition destination position.
/// @param unitY level's unit-Y position.
template <typename TType>
DMatrix4<TType> LookAt2(
  EGraphics graphics,
  const DVector3<TType>& position, 
  const DVector3<TType>& lookPosition,
  const DVector3<TType>& unitY);

/// @brief Create position translated matrix.
/// To get properly calculated matrix, matrix's Graphics API alignment and graphics value should be same.
/// This function does not check matrix's Graphics API alignment.
/// Calculation will be held by EGraphcis::graphics value.
template <typename TType>
DMatrix4<TType> Translate(
  EGraphics graphics,
  const DMatrix4<TType>& matrix,
  const DVector3<TType>& position);

/// @brief Create angle rotated matrix.
/// To get properly calculated matrix, matrix's Graphics API alignment and graphics value should be same.
/// This function does not check matrix's Graphics API alignment.
/// Calculation will be held by EGraphcis::graphics value.
template <typename TType>
DMatrix4<TType> Rotate(
  EGraphics graphics,
  const DMatrix4<TType>& matrix,
  const DVector3<TType>& eulerAngle,
  bool isDegree = true);

/// @brief Create scaled matrix.
/// To get properly calculated matrix, matrix's Graphics API alignment and graphics value should be same.
/// This function does not check matrix's Graphics API alignment.
/// Calculation will be held by EGraphcis::graphics value.
template <typename TType>
DMatrix4<TType> Scale(
  EGraphics graphics,
  const DMatrix4<TType>& matrix,
  const DVector3<TType>& scale);

/// @brief Create `Model` (TRSv) matrix.
/// To get properly calculated matrix, matrix's Graphics API alignment and graphics value should be same.
/// This function does not check matrix's Graphics API alignment.
/// Calculation will be held by EGraphcis::graphics value.
template <typename TType>
DMatrix4<TType> CreateModelMatrix(
  EGraphics graphics,
  const DVector3<TType>& position,
  const DVector3<TType>& eulerAngle,
  const DVector3<TType>& scale,
  bool isDegree = true);

//!
//! Vector Calculation
//!

/// @brief Get reflection vector of incident and normal vector.
/// @param incident Incident vector to surface. Incident vector must be forward to outside.
/// @param normal Normal vector to surface. Normal vector must be forward to outside.
/// @return Reflection vector forward to outside direction.
template <typename TType>
DVector3<TType> Reflect(const DVector3<TType>& incident, const DVector3<TType>& normal);

/// @brief Get refraction vector of incident, normal and two of index of refraction.
/// @param incidentIor IOR of incident vector side of surface.
/// @param transmitIor IOR of refraction vector side of surface.
/// @param incident Incident vector to surface. Incident vector must be forward to outside.
/// @param normal Normal vector to surface. Normal vector must be forward to outside.
/// @return If refraction vector can not calculated, just return null value.
template <typename TType, typename TScalar>
std::optional<DVector3<TType>> Refract(
  TScalar incidentIor, TScalar transmitIor, 
  const DVector3<TType>& incident, const DVector3<TType>& normal);

/// @brief Do schlick's approximation to get approximated Fresnel factor in specular reflection, between two media.
/// @param incidentIor IOR of incident vector side of surface.
/// @param transmitIor IOR of refraction vector side of surface.
/// @param incident Incident vector to surface. Incident vector must be forward to outside.
/// @param normal Normal vector to surface. Normal vector must be forward to outside.
template <typename TType, typename TScalar>
TReal Schlick(
  TScalar incidentIor, TScalar transmitIor, 
  const DVector3<TType>& incident, const DVector3<TType>& normal);

} /// ::dy::math namespace
#include <Math/Utility/Inline/XGraphicsMath.inl>
#include <Math/Utility/Inline/XVectorMath.inl>
