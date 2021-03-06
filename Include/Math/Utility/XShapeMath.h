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
#include <Math/Common/TGlobalTypes.h>
#include <Math/Type/Math/DVector3.h>
#include <Math/Type/Math/DQuat.h>
#include <Math/Type/Shape/DRay.h>
#include <Math/Type/Shape/DSphere.h>
#include <Math/Type/Shape/DBox.h>
#include <Math/Type/Shape/DPlane.h>
#include <Math/Type/Shape/DTorus.h>
#include <Math/Type/Shape/DCone.h>
#include <Math/Type/Shape/DCapsule.h>
#include <Math/Type/Micellanous/DBounds3D.h>

namespace dy::math
{

//!
//! Special DBounds3D functions
//!

/// @brief Get unioned Bounds3D (AABB) instance.
/// @param lhs Left handed side Bounds3D instance.
/// @param rhs Right handed side Bounds3D instance.
/// @return Unioned DBounds3D instance.
template <typename TType>
DBounds3D<TType> GetUnionOf(const DBounds3D<TType>& lhs, const DBounds3D<TType>& rhs);

/// @brief Get intersected DBounds3D box region (AABB) from given lhs and rhs if exist.
/// @param lhs Left handed side Bounds3D instance.
/// @param rhs Right handed side Bounds3D instance.
/// @return Unioned DBounds3D instance if intersection is exist. Otherwise value is null.
template <typename TType>
std::optional<DBounds3D<TType>> GetIntersectionOf(const DBounds3D<TType>& lhs, const DBounds3D<TType>& rhs); 

/// @brief Check whether given lhs and rhs DBounds3D is overlapped (Edge overlap is regarded as being overlapped)
/// @param lhs Left handed side Bounds3D instance.
/// @param rhs Right handed side Bounds3D instance.
/// @return If overlapped, return true.
template <typename TType>
[[nodiscard]] bool IsOverlapped(const DBounds3D<TType>& lhs, const DBounds3D<TType>& rhs); 

/// @brief Get bounding sphere of given DBounds3D instance.
/// @param bounds Bounds3D instance.
/// @return 3D Sphere instance.
template <typename TType>
DSphere<TType> GetBoundingSphereOf(const DBounds3D<TType>& bounds);

/// @brief Get expanded DBounds3D instance from given bounds with value length on each one side.
/// @param bounds Bounds3D instance.
/// @param value Extended length on each one side.
/// @return Expaneded DBounds3D instance.
template <typename TType>
DBounds3D<TType> GetExpandOf(const DBounds3D<TType>& bounds, TType value);

/// @brief Get moved (by offset) DBounds3D instance from given bounds.
/// If bounds is infinity, do nothing but return inputted bounds.
/// @param bounds Bounds3D instance.
/// @param offset Offset to move bounds.
/// @return Moved DBounds3D.
template <typename TType>
DBounds3D<TType> GetMovedOf(const DBounds3D<TType>& bounds, const DVector3<TType>& offset);

//!
//! GetDBounds3DOf functions
//!

/// @brief Get DBounds3D instance of world-space that covers given shape.
/// @param shape Sphere shape.
/// @return DBounds3D instance that covers given shape.
template <typename TType>
DBounds3D<TType> GetDBounds3DOf(const DSphere<TType>& shape);

/// @brief Get DBounds3D instance of world-space that covers given shape.
/// @param shape Plane shape.
/// @return DBounds3D instance that covers given shape.
template <typename TType>
DBounds3D<TType> GetDBounds3DOf(const DPlane<TType>& shape);

/// @brief Get DBounds3D instance of world-space that covers given shape.
/// @param shape Box shape.
/// @return DBounds3D instance that covers given shape.
template <typename TType>
DBounds3D<TType> GetDBounds3DOf(const DBox<TType>& shape);

/// @brief Get DBounds3D instance of world-space that covers given shape.
/// @param shape Box shape.
/// @param rotMatrix World-rotation matrix of box instance.
/// @return DBounds3D instance that covers given shape.
template <typename TType, EMatMajor TMajor>
DBounds3D<TType> GetDBounds3DOf(const DBox<TType>& shape, const DMatrix3<TType, TMajor>& rot);

/// @brief Get DBounds3D instance of world-space that covers given shape.
/// @param shape Box shape.
/// @param rot Quaternion that has rotation information of DBox.
/// @return DBounds3D instance that covers given shape.
template <typename TType>
DBounds3D<TType> GetDBounds3DOf(const DBox<TType>& shape, const DQuaternion<TType>& rot);

/// @brief Get DBounds3D instance of world-space that covers given shape.
/// @param shape Torus shape.
/// @return DBounds3D instance that covers given shape.
template <typename TType>
DBounds3D<TType> GetDBounds3DOf(const DTorus<TType>& shape);

/// @brief Get DBounds3D instance of world-space that covers given shape.
/// @param shape Torus shape.
/// @param rotMatrix World-rotation matrix of box instance.
/// @return DBounds3D instance that covers given shape.
template <typename TType, EMatMajor TMajor>
DBounds3D<TType> GetDBounds3DOf(const DTorus<TType>& shape, const DMatrix3<TType, TMajor>& rot);

/// @brief Get DBounds3D instance of world-space that covers given shape.
/// @param shape Torus shape.
/// @param rot Quaternion that has rotation information of DTorus.
/// @return DBounds3D instance that covers given shape.
template <typename TType>
DBounds3D<TType> GetDBounds3DOf(const DTorus<TType>& shape, const DQuaternion<TType>& rot);

/// @brief Get DBounds3D instance of world-space that covers given shape.
/// @param shape Cone shape.
/// @return DBounds3D instance that covers given shape.
template <typename TType>
DBounds3D<TType> GetDBounds3DOf(const DCone<TType>& shape);

/// @brief Get DBounds3D instance of world-space that covers given shape.
/// @param shape Cone shape.
/// @param rotMatrix World-rotation matrix of box instance.
/// @return DBounds3D instance that covers given shape.
template <typename TType, EMatMajor TMajor>
DBounds3D<TType> GetDBounds3DOf(const DCone<TType>& shape, const DMatrix3<TType, TMajor>& rot);

/// @brief Get DBounds3D instance of world-space that covers given shape.
/// @param shape Cone shape.
/// @param rot Quaternion that has rotation information of DCone.
/// @return DBounds3D instance that covers given shape.
template <typename TType>
DBounds3D<TType> GetDBounds3DOf(const DCone<TType>& shape, const DQuaternion<TType>& rot);

/// @brief Get DBounds3D instance of world-space that covers given shape.
/// @param shape Capsule shape.
/// @return DBounds3D instance that covers given shape.
template <typename TType>
DBounds3D<TType> GetDBounds3DOf(const DCapsule<TType>& shape);

/// @brief Get DBounds3D instance of world-space that covers given shape.
/// @param shape Capsule shape.
/// @param rotMatrix World-rotation matrix of box instance.
/// @return DBounds3D instance that covers given shape.
template <typename TType, EMatMajor TMajor>
DBounds3D<TType> GetDBounds3DOf(const DCapsule<TType>& shape, const DMatrix3<TType, TMajor>& rot);

/// @brief Get DBounds3D instance of world-space that covers given shape.
/// @param shape Capsule shape.
/// @param rot Quaternion that has rotation information of DCapsule.
/// @return DBounds3D instance that covers given shape.
template <typename TType>
DBounds3D<TType> GetDBounds3DOf(const DCapsule<TType>& shape, const DQuaternion<TType>& rot);

//!
//! IsRayIntersected
//!

/// @brief Check that DRay is intersected with DBounds3D(3D AABB).
/// @param ray Ray instance in world-space.
/// @param box Bounds3D instance in world-space.
template <typename TType>
[[nodiscard]] bool IsRayIntersected(const DRay<TType>& ray, const DBounds3D<TType>& bounds);

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
template <typename TType, EMatMajor TMajor>
[[nodiscard]] bool IsRayIntersected(const DRay<TType>& ray, const DBox<TType>& box, const DMatrix3<TType, TMajor>& rot);

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
template <typename TType, EMatMajor TMajor>
[[nodiscard]] bool IsRayIntersected(const DRay<TType>& ray, const DTorus<TType>& torus, const DMatrix3<TType, TMajor>& rot);

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
template <typename TType, EMatMajor TMajor>
[[nodiscard]] bool IsRayIntersected(const DRay<TType>& ray, const DCone<TType>& cone, const DMatrix3<TType, TMajor>& rot);

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
template <typename TType, EMatMajor TMajor>
[[nodiscard]] bool IsRayIntersected(const DRay<TType>& ray, const DCapsule<TType>& capsule, const DMatrix3<TType, TMajor>& rot);

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
template <typename TType, EMatMajor TMajor>
TReal GetSDFValueOf(const DVector3<TType>& point, const DBox<TType>& box, const DMatrix3<TType, TMajor>& rot);

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
template <typename TType, EMatMajor TMajor>
TReal GetSDFValueOf(const DVector3<TType>& point, const DTorus<TType>& torus, const DMatrix3<TType, TMajor>& rot);

/// @brief Get signed distance value of torus model from point.
template <typename TType>
TReal GetSDFValueOf(const DVector3<TType>& point, const DTorus<TType>& torus, const DQuaternion<TType>& rot);

/// @brief Get signed distance value of cone model from point.
template <typename TType>
TReal GetSDFValueOf(const DVector3<TType>& point, const DCone<TType>& cone);

/// @brief Get signed distance value of cone model from point.
template <typename TType, EMatMajor TMajor>
TReal GetSDFValueOf(const DVector3<TType>& point, const DCone<TType>& cone, const DMatrix3<TType, TMajor>& rot);

/// @brief Get signed distance value of cone model from point.
template <typename TType>
TReal GetSDFValueOf(const DVector3<TType>& point, const DCone<TType>& cone, const DQuaternion<TType>& rot);

/// @brief Get signed distance value of capsule model from point.
template <typename TType>
TReal GetSDFValueOf(const DVector3<TType>& point, const DCapsule<TType>& capsule);

/// @brief Get signed distance value of capsule model from point.
template <typename TType, EMatMajor TMajor>
TReal GetSDFValueOf(const DVector3<TType>& point, const DCapsule<TType>& capsule, const DMatrix3<TType, TMajor>& rot);

/// @brief Get signed distance value of capsule model from point.
template <typename TType>
TReal GetSDFValueOf(const DVector3<TType>& point, const DCapsule<TType>& capsule, const DQuaternion<TType>& rot);

//!
//! GetTValuesOf
//!

/// @brief Get positive 't' list to the point of given 3d bounds from given ray.
template <typename TType>
std::vector<TReal> GetTValuesOf(const DRay<TType>& ray, const DBounds3D<TType>& bounds);

/// @brief Get positive 't' list to the point of given sphere from given ray.
template <typename TType>
std::vector<TReal> GetTValuesOf(const DRay<TType>& ray, const DSphere<TType>& sphere);

/// @brief Get positive 't' list to the point of given box from given ray.
template <typename TType>
std::vector<TReal> GetTValuesOf(const DRay<TType>& ray, const DBox<TType>& box);

/// @brief Get positive 't' list to the point of given box from given ray.
template <typename TType, EMatMajor TMajor>
std::vector<TReal> GetTValuesOf(const DRay<TType>& ray, const DBox<TType>& box, const DMatrix3<TType, TMajor>& rot);

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
template <typename TType, EMatMajor TMajor>
std::vector<TReal> GetTValuesOf(const DRay<TType>& ray, const DTorus<TType>& torus, const DMatrix3<TType, TMajor>& rot);

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
template <typename TType, EMatMajor TMajor>
std::vector<TReal> GetTValuesOf(const DRay<TType>& ray, const DCone<TType>& cone, const DMatrix3<TType, TMajor>& rot);

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
template <typename TType, EMatMajor TMajor>
std::vector<TReal> GetTValuesOf(const DRay<TType>& ray, const DCapsule<TType>& capsule, const DMatrix3<TType, TMajor>& rot);

/// @brief Get positive 't' list to the point of given capsule from given ray.
/// @param ray Ray instance in world-space.
/// @param capsule Capsule instance.
/// @param rot Quaternion that has rotation information of DCapsule.
template <typename TType>
std::vector<TReal> GetTValuesOf(const DRay<TType>& ray, const DCapsule<TType>& capsule, const DQuaternion<TType>& rot);

//!
//! GetClosestTValueOf
//!

/// @brief Get positive `t` to the closest point of given 3d bounds from given ray.
/// If not found, just return nullopt value.
/// @param ray Ray instance in world-space.
/// @param bounds 3D-bounds in world-space.
template <typename TType>
std::optional<TReal> GetClosestTValueOf(const DRay<TType>& ray, const DBounds3D<TType>& bounds);

/// @brief Get positive `t` to the closest point of given 3d bounds from given ray.
/// If not found, just return nullopt value.
template <typename TType>
std::optional<TReal> GetClosestTValueOf(const DRay<TType>& ray, const DSphere<TType>& sphere);

/// @brief Get positive `t` to the closest point of given box from given ray.
/// If not found, just return nullopt value.
template <typename TType>
std::optional<TReal> GetClosestTValueOf(const DRay<TType>& ray, const DBox<TType>& box);

/// @brief Get positive `t` to the closest point of given box from given ray.
/// If not found, just return nullopt value.
template <typename TType, EMatMajor TMajor>
std::optional<TReal> GetClosestTValueOf(const DRay<TType>& ray, const DBox<TType>& box, const DMatrix3<TType, TMajor>& rot);

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
template <typename TType, EMatMajor TMajor>
std::optional<TReal> GetClosestTValueOf(const DRay<TType>& ray, const DTorus<TType>& torus, const DMatrix3<TType, TMajor>& rot);

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
template <typename TType, EMatMajor TMajor>
std::optional<TReal> GetClosestTValueOf(const DRay<TType>& ray, const DCone<TType>& cone, const DMatrix3<TType, TMajor>& rot);

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
template <typename TType, EMatMajor TMajor>
std::optional<TReal> GetClosestTValueOf(const DRay<TType>& ray, const DCapsule<TType>& capsule, const DMatrix3<TType, TMajor>& rot);

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
template <typename TType, EMatMajor TMajor>
std::optional<DVector3<TType>> 
GetNormalOf(const DRay<TType>& ray, const DBox<TType>& box, const DMatrix3<TType, TMajor>& rot);

/// @brief Try to get normal vector of box, when ray is intersected.
template <typename TType>
std::optional<DVector3<TType>> 
GetNormalOf(const DRay<TType>& ray, const DBox<TType>& box, const DQuaternion<TType>& rot);

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
template <typename TType, EMatMajor TMajor>
std::optional<DVector3<TType>> 
GetNormalOf(const DRay<TType>& ray, const DTorus<TType>& torus, const DMatrix3<TType, TMajor>& rot);

/// @brief Try to get normal vector of torus, when ray is intersected.
/// @param ray Ray instance in world-space.
/// @param torus Torus instance.
/// @param rot Quaternion that has rotation information of DTorus.
template <typename TType>
std::optional<DVector3<TType>> 
GetNormalOf(const DRay<TType>& ray, const DTorus<TType>& torus, const DQuaternion<TType>& rot);

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
template <typename TType, EMatMajor TMajor>
std::optional<DVector3<TType>> 
GetNormalOf(const DRay<TType>& ray, const DCone<TType>& cone, const DMatrix3<TType, TMajor>& rot);

/// @brief Try to get normal vector of cone, when ray is intersected.
/// @param ray Ray instance in world-space.
/// @param cone Cone instance.
/// @param rot Quaternion that has rotation information of DCone.
template <typename TType>
std::optional<DVector3<TType>> 
GetNormalOf(const DRay<TType>& ray, const DCone<TType>& cone, const DQuaternion<TType>& rot);

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
template <typename TType, EMatMajor TMajor>
std::optional<DVector3<TType>> 
GetNormalOf(const DRay<TType>& ray, const DCapsule<TType>& capsule, const DMatrix3<TType, TMajor>& rot);

/// @brief Try to get normal vector of capsule, when ray is intersected.
/// @param ray Ray instance in world-space.
/// @param capsule Cone instance.
/// @param rot Quaternion that has rotation information of DCapsule.
template <typename TType>
std::optional<DVector3<TType>> 
GetNormalOf(const DRay<TType>& ray, const DCapsule<TType>& capsule, const DQuaternion<TType>& rot);

} /// ::dy::math namespace
#include <Math/Utility/Inline/XShapeMath.inl>
#include <Math/Utility/Inline/XBounds3DMath.inl>
