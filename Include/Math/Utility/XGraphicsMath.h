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

//!
//! Shapes
//!

//!
//! IsRayIntersected
//!

/// @brief Check that Ray is intersected into Sphere.
template <typename TType>
[[nodiscard]] bool IsRayIntersected(const DRay<TType>& ray, const DSphere<TType>& sphere);

/// @brief Check that Ray is intersected into DBox.
/// In this function, DBox's x, y, z is aligned to world-space X, Y, Z axis (AABB).
/// @param ray Ray instance in world-space.
/// @param box Box instance.
template <typename TType>
[[nodiscard]] bool IsRayIntersected(const DRay<TType>& ray, const DBox<TType>& box);

/// @brief Check that Ray is intersected into DBox.
/// @param ray Ray instance in world-space.
/// @param box Box instance.
/// @param rotMatrix World-rotation matrix of box instance.
template <typename TType>
[[nodiscard]] bool IsRayIntersected(const DRay<TType>& ray, const DBox<TType>& box, const DMatrix3<TType>& rot);

/// @brief Check that Ray is intersected into DBox.
/// @param ray Ray instance in world-space.
/// @param box Box instance.
/// @param rot Quaternion that has rotation information of DBox.
template <typename TType>
[[nodiscard]] bool IsRayIntersected(const DRay<TType>& ray, const DBox<TType>& box, const DQuaternion<TType>& rot);

/// @brief Check that Ray is intersected into DBox.
/// @param ray Ray instance in world-space.
/// @param plane Plane instance in world-space.
template <typename TType>
[[nodiscard]] bool IsRayIntersected(const DRay<TType>& ray, const DPlane<TType>& plane);

/// @brief Check that Ray is intersected into DTorus.
/// @param ray Ray instance in world-space.
/// @param torus Torus instance in world-space.
template <typename TType>
[[nodiscard]] bool IsRayIntersected(const DRay<TType>& ray, const DTorus<TType>& torus);

/// @brief Check that Ray is intersected into DTorus.
/// @param ray Ray instance in world-space.
/// @param torus Torus instance.
/// @param rot World-rotation matrix of torus instance.
template <typename TType>
[[nodiscard]] bool IsRayIntersected(const DRay<TType>& ray, const DTorus<TType>& torus, const DMatrix3<TType>& rot);

/// @brief Check that Ray is intersected into DTorus.
/// @param ray Ray instance in world-space.
/// @param torus Torus instance.
/// @param rot Quaternion that has rotation information of DTorus.
template <typename TType>
[[nodiscard]] bool IsRayIntersected(const DRay<TType>& ray, const DTorus<TType>& torus, const DQuaternion<TType>& rot);

/// @brief Check that Ray is intersected into DCone.
/// @param ray Ray instance in world-space.
/// @param cone Cone instance in world-space.
template <typename TType>
[[nodiscard]] bool IsRayIntersected(const DRay<TType>& ray, const DCone<TType>& cone);

/// @brief Check that Ray is intersected into DCone.
/// @param ray Ray instance in world-space.
/// @param cone Cone instance.
/// @param rot World-rotation matrix of cone instance.
template <typename TType>
[[nodiscard]] bool IsRayIntersected(const DRay<TType>& ray, const DCone<TType>& cone, const DMatrix3<TType>& rot);

/// @brief Check that Ray is intersected into DCone.
/// @param ray Ray instance in world-space.
/// @param cone Cone instance.
/// @param rot Quaternion that has rotation information of DCone.
template <typename TType>
[[nodiscard]] bool IsRayIntersected(const DRay<TType>& ray, const DCone<TType>& cone, const DQuaternion<TType>& rot);

/// @brief Check that Ray is intersected into DCapsule.
/// @param ray Ray instance in world-space.
/// @param capsule Capsule instance in world-space.
template <typename TType>
[[nodiscard]] bool IsRayIntersected(const DRay<TType>& ray, const DCapsule<TType>& capsule);

/// @brief Check that Ray is intersected into DCapsule.
/// @param ray Ray instance in world-space.
/// @param capsule Capsule instance.
/// @param rot World-rotation matrix of capsule instance.
template <typename TType>
[[nodiscard]] bool IsRayIntersected(const DRay<TType>& ray, const DCapsule<TType>& capsule, const DMatrix3<TType>& rot);

/// @brief Check that Ray is intersected into DCapsule.
/// @param ray Ray instance in world-space.
/// @param capsule Capsule instance.
/// @param rot Quaternion that has rotation information of DCapsule.
template <typename TType>
[[nodiscard]] bool IsRayIntersected(const DRay<TType>& ray, const DCapsule<TType>& capsule, const DQuaternion<TType>& rot);

//!
//! GetSDFValueOf
//!

/// @brief Get signed distance value of sphere model from point.
template <typename TType>
TReal GetSDFValueOf(const DVector3<TType>& point, const DSphere<TType>& sphere);

/// @brief Get signed distance value of box model from point.
template <typename TType>
TReal GetSDFValueOf(const DVector3<TType>& point, const DBox<TType>& box);

/// @brief Get signed distance value of box model from point.
template <typename TType>
TReal GetSDFValueOf(const DVector3<TType>& point, const DBox<TType>& box, const DMatrix3<TType>& rot);

/// @brief Get signed distance value of box model from point.
template <typename TType>
TReal GetSDFValueOf(const DVector3<TType>& point, const DBox<TType>& box, const DQuaternion<TType>& rot);

/// @brief Get signed distance value of plane model from point.
template <typename TType>
TReal GetSDFValueOf(const DVector3<TType>& point, const DPlane<TType>& plane);

/// @brief Get signed distance value of torus model from point.
template <typename TType>
TReal GetSDFValueOf(const DVector3<TType>& point, const DTorus<TType>& torus);

/// @brief Get signed distance value of torus model from point.
template <typename TType>
TReal GetSDFValueOf(const DVector3<TType>& point, const DTorus<TType>& torus, const DMatrix3<TType>& rot);

/// @brief Get signed distance value of torus model from point.
template <typename TType>
TReal GetSDFValueOf(const DVector3<TType>& point, const DTorus<TType>& torus, const DQuaternion<TType>& rot);

/// @brief Get signed distance value of cone model from point.
template <typename TType>
TReal GetSDFValueOf(const DVector3<TType>& point, const DCone<TType>& cone);

/// @brief Get signed distance value of cone model from point.
template <typename TType>
TReal GetSDFValueOf(const DVector3<TType>& point, const DCone<TType>& cone, const DMatrix3<TType>& rot);

/// @brief Get signed distance value of cone model from point.
template <typename TType>
TReal GetSDFValueOf(const DVector3<TType>& point, const DCone<TType>& cone, const DQuaternion<TType>& rot);

/// @brief Get signed distance value of capsule model from point.
template <typename TType>
TReal GetSDFValueOf(const DVector3<TType>& point, const DCapsule<TType>& capsule);

/// @brief Get signed distance value of capsule model from point.
template <typename TType>
TReal GetSDFValueOf(const DVector3<TType>& point, const DCapsule<TType>& capsule, const DMatrix3<TType>& rot);

/// @brief Get signed distance value of capsule model from point.
template <typename TType>
TReal GetSDFValueOf(const DVector3<TType>& point, const DCapsule<TType>& capsule, const DQuaternion<TType>& rot);

//!
//! GetTValuesOf
//!

/// @brief Get positive 't' list to the point of given sphere from given ray.
template <typename TType>
std::vector<TReal> GetTValuesOf(const DRay<TType>& ray, const DSphere<TType>& sphere);

/// @brief Get positive 't' list to the point of given box from given ray.
template <typename TType>
std::vector<TReal> GetTValuesOf(const DRay<TType>& ray, const DBox<TType>& box);

/// @brief Get positive 't' list to the point of given box from given ray.
template <typename TType>
std::vector<TReal> GetTValuesOf(const DRay<TType>& ray, const DBox<TType>& box, const DMatrix3<TType>& rot);

/// @brief Get positive 't' list to the point of given box from given ray.
template <typename TType>
std::vector<TReal> GetTValuesOf(const DRay<TType>& ray, const DBox<TType>& box, const DQuaternion<TType>& rot);

/// @brief Get positive 't' list to the point of given DPlane from given ray.
template <typename TType>
std::vector<TReal> GetTValuesOf(const DRay<TType>& ray, const DPlane<TType>& plane);

/// @brief Get positive 't' list to the point of given DTorus from given ray.
/// @param ray Ray instance in world-space.
/// @param torus Torus instance.
template <typename TType>
std::vector<TReal> GetTValuesOf(const DRay<TType>& ray, const DTorus<TType>& torus);

/// @brief Get positive 't' list to the point of given torus from given ray.
/// @param ray Ray instance in world-space.
/// @param torus Torus instance.
/// @param rot World-rotation matrix of torus instance.
template <typename TType>
std::vector<TReal> GetTValuesOf(const DRay<TType>& ray, const DTorus<TType>& torus, const DMatrix3<TType>& rot);

/// @brief Get positive 't' list to the point of given torus from given ray.
/// @param ray Ray instance in world-space.
/// @param torus Torus instance.
/// @param rot Quaternion that has rotation information of DTorus.
template <typename TType>
std::vector<TReal> GetTValuesOf(const DRay<TType>& ray, const DTorus<TType>& torus, const DQuaternion<TType>& rot);

/// @brief Get positive 't' list to the point of given DCone from given ray.
/// @param ray Ray instance in world-space.
/// @param cone Cone instance.
template <typename TType>
std::vector<TReal> GetTValuesOf(const DRay<TType>& ray, const DCone<TType>& cone);

/// @brief Get positive 't' list to the point of given cone from given ray.
/// @param ray Ray instance in world-space.
/// @param cone Cone instance.
/// @param rot World-rotation matrix of cone instance.
template <typename TType>
std::vector<TReal> GetTValuesOf(const DRay<TType>& ray, const DCone<TType>& cone, const DMatrix3<TType>& rot);

/// @brief Get positive 't' list to the point of given cone from given ray.
/// @param ray Ray instance in world-space.
/// @param cone Cone instance.
/// @param rot Quaternion that has rotation information of DCone.
template <typename TType>
std::vector<TReal> GetTValuesOf(const DRay<TType>& ray, const DCone<TType>& cone, const DQuaternion<TType>& rot);

/// @brief Get positive 't' list to the point of given DCapsule from given ray.
/// @param ray Ray instance in world-space.
/// @param capsule Capsule instance.
template <typename TType>
std::vector<TReal> GetTValuesOf(const DRay<TType>& ray, const DCapsule<TType>& capsule);

/// @brief Get positive 't' list to the point of given capsule from given ray.
/// @param ray Ray instance in world-space.
/// @param capsule Capsule instance.
/// @param rot World-rotation matrix of capsule instance.
template <typename TType>
std::vector<TReal> GetTValuesOf(const DRay<TType>& ray, const DCapsule<TType>& capsule, const DMatrix3<TType>& rot);

/// @brief Get positive 't' list to the point of given capsule from given ray.
/// @param ray Ray instance in world-space.
/// @param capsule Capsule instance.
/// @param rot Quaternion that has rotation information of DCapsule.
template <typename TType>
std::vector<TReal> GetTValuesOf(const DRay<TType>& ray, const DCapsule<TType>& capsule, const DQuaternion<TType>& rot);

//!
//! GetClosestTValueOf
//!

/// @brief Get positive `t` to the closest point of given sphere from given ray.
/// If not found, just return nullopt value.
template <typename TType>
std::optional<TReal> GetClosestTValueOf(const DRay<TType>& ray, const DSphere<TType>& sphere);

/// @brief Get positive `t` to the closest point of given box from given ray.
/// If not found, just return nullopt value.
template <typename TType>
std::optional<TReal> GetClosestTValueOf(const DRay<TType>& ray, const DBox<TType>& box);

/// @brief Get positive `t` to the closest point of given box from given ray.
/// If not found, just return nullopt value.
template <typename TType>
std::optional<TReal> GetClosestTValueOf(const DRay<TType>& ray, const DBox<TType>& box, const DMatrix3<TType>& rot);

/// @brief Get positive `t` to the closest point of given box from given ray.
/// If not found, just return nullopt value.
template <typename TType>
std::optional<TReal> GetClosestTValueOf(const DRay<TType>& ray, const DBox<TType>& box, const DQuaternion<TType>& rot);

/// @brief Get positive `t` to the closest point of given plane from given ray.
/// If not found, just return nullopt value.
template <typename TType>
std::optional<TReal> GetClosestTValueOf(const DRay<TType>& ray, const DPlane<TType>& plane);

/// @brief Get positive `t` to the closest point of given plane from given ray.
/// If not found, just return nullopt value.
/// @param ray Ray instance in world-space.
/// @param torus Torus instance.
template <typename TType>
std::optional<TReal> GetClosestTValueOf(const DRay<TType>& ray, const DTorus<TType>& torus);

/// @brief Get positive 't' list to the point of given torus from given ray.
/// @param ray Ray instance in world-space.
/// @param torus Torus instance.
/// @param rot World-rotation matrix of torus instance.
template <typename TType>
std::optional<TReal> GetClosestTValueOf(const DRay<TType>& ray, const DTorus<TType>& torus, const DMatrix3<TType>& rot);

/// @brief Get positive 't' list to the point of given torus from given ray.
/// @param ray Ray instance in world-space.
/// @param torus Torus instance.
/// @param rot Quaternion that has rotation information of DTorus.
template <typename TType>
std::optional<TReal> GetClosestTValueOf(const DRay<TType>& ray, const DTorus<TType>& torus, const DQuaternion<TType>& rot);

/// @brief Get positive `t` to the closest point of given plane from given ray.
/// If not found, just return nullopt value.
/// @param ray Ray instance in world-space.
/// @param cone Cone instance.
template <typename TType>
std::optional<TReal> GetClosestTValueOf(const DRay<TType>& ray, const DCone<TType>& cone);

/// @brief Get positive 't' list to the point of given cone from given ray.
/// @param ray Ray instance in world-space.
/// @param cone Cone instance.
/// @param rot World-rotation matrix of cone instance.
template <typename TType>
std::optional<TReal> GetClosestTValueOf(const DRay<TType>& ray, const DCone<TType>& cone, const DMatrix3<TType>& rot);

/// @brief Get positive 't' list to the point of given cone from given ray.
/// @param ray Ray instance in world-space.
/// @param cone Cone instance.
/// @param rot Quaternion that has rotation information of DCone.
template <typename TType>
std::optional<TReal> GetClosestTValueOf(const DRay<TType>& ray, const DCone<TType>& cone, const DQuaternion<TType>& rot);

/// @brief Get positive `t` to the closest point of given plane from given ray.
/// If not found, just return nullopt value.
/// @param ray Ray instance in world-space.
/// @param capsule Cone instance.
template <typename TType>
std::optional<TReal> GetClosestTValueOf(const DRay<TType>& ray, const DCapsule<TType>& capsule);

/// @brief Get positive 't' list to the point of given capsule from given ray.
/// @param ray Ray instance in world-space.
/// @param capsule Cone instance.
/// @param rot World-rotation matrix of capsule instance.
template <typename TType>
std::optional<TReal> GetClosestTValueOf(const DRay<TType>& ray, const DCapsule<TType>& capsule, const DMatrix3<TType>& rot);

/// @brief Get positive 't' list to the point of given capsule from given ray.
/// @param ray Ray instance in world-space.
/// @param capsule Cone instance.
/// @param rot Quaternion that has rotation information of DCapsule.
template <typename TType>
std::optional<TReal> GetClosestTValueOf(const DRay<TType>& ray, const DCapsule<TType>& capsule, const DQuaternion<TType>& rot);

//!
//! GetNormalOf
//!

/// @brief Try to get normal vector of sphere, when ray is intersected.
template <typename TType>
std::optional<DVector3<TType>> GetNormalOf(const DRay<TType>& ray, const DSphere<TType>& sphere);

/// @brief Try to get normal vector of box, when ray is intersected.
template <typename TType>
std::optional<DVector3<TType>> GetNormalOf(const DRay<TType>& ray, const DBox<TType>& box);

/// @brief Try to get normal vector of box, when ray is intersected.
template <typename TType>
std::optional<DVector3<TType>> GetNormalOf(const DRay<TType>& ray, const DBox<TType>& box, const DMatrix3<TType>& rot);

/// @brief Try to get normal vector of box, when ray is intersected.
template <typename TType>
std::optional<DVector3<TType>> GetNormalOf(const DRay<TType>& ray, const DBox<TType>& box, const DQuaternion<TType>& rot);

/// @brief Try to get normal vector of plane, when ray is intersected.
template <typename TType>
std::optional<DVector3<TType>> GetNormalOf(const DRay<TType>& ray, const DPlane<TType>& plane);

/// @brief Try to get normal vector of torus, when ray is intersected.
/// If not found, just return nullopt value.
/// @param ray Ray instance in world-space.
/// @param torus Torus instance.
template <typename TType>
std::optional<DVector3<TType>> GetNormalOf(const DRay<TType>& ray, const DTorus<TType>& torus);

/// @brief Try to get normal vector of torus, when ray is intersected.
/// @param ray Ray instance in world-space.
/// @param torus Torus instance.
/// @param rot World-rotation matrix of torus instance.
template <typename TType>
std::optional<DVector3<TType>> GetNormalOf(const DRay<TType>& ray, const DTorus<TType>& torus, const DMatrix3<TType>& rot);

/// @brief Try to get normal vector of torus, when ray is intersected.
/// @param ray Ray instance in world-space.
/// @param torus Torus instance.
/// @param rot Quaternion that has rotation information of DTorus.
template <typename TType>
std::optional<DVector3<TType>> GetNormalOf(const DRay<TType>& ray, const DTorus<TType>& torus, const DQuaternion<TType>& rot);

/// @brief Try to get normal vector of cone, when ray is intersected.
/// If not found, just return nullopt value.
/// @param ray Ray instance in world-space.
/// @param cone Cone instance.
template <typename TType>
std::optional<DVector3<TType>> GetNormalOf(const DRay<TType>& ray, const DCone<TType>& cone);

/// @brief Try to get normal vector of cone, when ray is intersected.
/// @param ray Ray instance in world-space.
/// @param cone Cone instance.
/// @param rot World-rotation matrix of cone instance.
template <typename TType>
std::optional<DVector3<TType>> GetNormalOf(const DRay<TType>& ray, const DCone<TType>& cone, const DMatrix3<TType>& rot);

/// @brief Try to get normal vector of cone, when ray is intersected.
/// @param ray Ray instance in world-space.
/// @param cone Cone instance.
/// @param rot Quaternion that has rotation information of DCone.
template <typename TType>
std::optional<DVector3<TType>> GetNormalOf(const DRay<TType>& ray, const DCone<TType>& cone, const DQuaternion<TType>& rot);

/// @brief Try to get normal vector of capsule, when ray is intersected.
/// If not found, just return nullopt value.
/// @param ray Ray instance in world-space.
/// @param capsule Cone instance.
template <typename TType>
std::optional<DVector3<TType>> GetNormalOf(const DRay<TType>& ray, const DCapsule<TType>& capsule);

/// @brief Try to get normal vector of capsule, when ray is intersected.
/// @param ray Ray instance in world-space.
/// @param capsule Cone instance.
/// @param rot World-rotation matrix of capsule instance.
template <typename TType>
std::optional<DVector3<TType>> GetNormalOf(const DRay<TType>& ray, const DCapsule<TType>& capsule, const DMatrix3<TType>& rot);

/// @brief Try to get normal vector of capsule, when ray is intersected.
/// @param ray Ray instance in world-space.
/// @param capsule Cone instance.
/// @param rot Quaternion that has rotation information of DCapsule.
template <typename TType>
std::optional<DVector3<TType>> GetNormalOf(const DRay<TType>& ray, const DCapsule<TType>& capsule, const DQuaternion<TType>& rot);

} /// ::dy::math namespace
#include <Math/Utility/Inline/XGraphicsMath.inl>
#include <Math/Utility/Inline/XVectorMath.inl>
#include <Math/Utility/Inline/XShapeMath.inl>
