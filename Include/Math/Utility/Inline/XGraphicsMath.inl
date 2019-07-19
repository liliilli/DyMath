#ifndef __GNUC__
#pragma once
#endif
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

#include <Math/Utility/XGraphicsMath.h>
#include <Math/Utility/XLinearMath.h>

#ifdef near
#undef near
#endif
#ifdef far
#undef far
#endif

namespace dy::math::detail
{

/// @brief Get orthographic projection of OpenGL. \n
/// [ 2/(r-l)    0       0    -(r+l)/(r-l) ] \n
/// [   0     2/(t-b)    0    -(t+b)/(t-b) ] \n
/// [   0        0   -2/(f-n) -(f+n)/(f-n) ] \n
/// [   0        0       0          1      ]
template <::dy::math::EMatMajor TMajor, typename TType>
DMatrix4<TType, TMajor> OpenGlOrtho(TReal left, TReal right, TReal bottom, TReal top, TReal near, TReal far)
{
  return 
  {
    static_cast<TType>(2) / (right - left), 0, 0, -(right + left) / (right - left),
    0, static_cast<TType>(2) / (top - bottom), 0, -(top + bottom) / (top - bottom);
    0, 0, -static_cast<TType>(2) / (far - near), -(far + near) / (far - near),
    0, 0, 0, 1
  };
}

template <EMatMajor TMajor, typename TType>
DMatrix4<TType, TMajor> OpenGlOrtho(TReal fovY, TReal width, TReal height, TReal near, TReal far)
{
  return {};
}

template <EMatMajor TMajor, typename TType>
DMatrix4<TType, TMajor> OpenGlPersp(TReal left, TReal right, TReal bottom, TReal top, TReal near, TReal far)
{
  return {};
}

template <EMatMajor TMajor, typename TType>
DMatrix4<TType, TMajor> OpenGlPersp(TReal fovY, TReal width, TReal height, TReal near, TReal far)
{
  const TType halfFovyTan = std::tan(fovY / TType(2));
  const TType aspect = width / height;

  return 
  {
    TType(1) / (aspect * halfFovyTan), 0, 0, 0,
    0, TType(1) / (halfFovyTan), 0, 0,
    0, 0, -(far + near) / (far - near), -(TType(2) * far * near) / (far - near),
    0, 0, -TType(1), 0
  }
}

template <EMatMajor TMajor, typename TType>
DMatrix4<TType, TMajor> _CommonLookAt(
  const DVector3<TType>& position, 
  const DVector3<TType>& lookPosition,
  const DVector3<TType>& unitY)
{
  const DVector3<TType> unitFront = (lookPosition - position).Normalize();
  const DVector3<TType> unitSide  = Cross(unitFront, unitY).Normalize();
  const DVector3<TType> unitUp    = Cross(unitSide, unitFront);

  // in Row Major
  //  sx  sy  sz -dot(s,p)
  //  ux  uy  uz -dot(u,p)
  // -fx -fy -fz -dot(f,p)
  //   0   0   0     1
  return
  {
    unitSide.X, unitSide.Y, unitSide.Z, -Dot(unitSide, position),
    unitUp.X, unitUp.Y, unitUp.Z, -Dot(unitUp, position),
    -unitFront.X, -unitFront.Y, -unitFront.Z, Dot(unitFront, position),
    0, 0, 0, 1
  };
}

template <EMatMajor TMajor, typename TType>
DMatrix4<TType, TMajor> _CommonTranslate(const DMatrix4<TType, TMajor>& matrix, const DVector3<TType>& position)
{
  auto result = matrix;
  if constexpr (TMajor == EMatMajor::Column)
  {
    result[3][0] += position.X;
    result[3][1] += position.Y;
    result[3][2] += position.Z;
  }
  else
  {
    result[0][3] += position.X;
    result[1][3] += position.Y;
    result[2][3] += position.Z;
  }

  return result;
}

template <EMatMajor TMajor, typename TType>
DMatrix4<TType, TMajor> _CommonRotate(const DMatrix4<TType, TMajor>& matrix, const DVector3<TType>& radianEuler)
{
  return DQuaternion<TReal>(radianEuler, false).ToMatrix4<TMajor>() * matrix;
}

template <EMatMajor TMajor, typename TType>
DMatrix4<TType, TMajor> _CommonScale(const DMatrix4<TType, TMajor>& matrix, const DVector3<TType>& scale)
{
  auto result = matrix;
  result[0][0] *= scale.X;
  result[1][1] *= scale.Y;
  result[2][2] *= scale.Z;
  return result;
}

} /// ::dy::math::detail namespace

namespace dy::math
{

template <EMatMajor TMajor, typename TType>
DMatrix4<TType, TMajor> ProjectionMatrix(
  EGraphics graphics, EProjection project,
  TReal left, TReal right, TReal bottom, TReal top, TReal near, TReal far)
{
  switch (graphics)
  {
  case EGraphics::OpenGL: 
  {
    if (project == EProjection::Orthogonal) 
    { 
      return detail::OpenGlOrtho<TMajor, TType>(left, right, bottom, top, near, far);
    }
    else
    {
      return detail::OpenGlPersp<TMajor, TType>(left, right, bottom, top, near, far);
    }
  } break;
  default: break;
  }
  return {};
}

template <EMatMajor TMajor, typename TType>
DMatrix4<TType, TMajor> ProjectionMatrix(
  EGraphics graphics, EProjection project, 
  TReal fovY, TReal width, TReal height, TReal near, TReal far)
{
  switch (graphics)
  {
  case EGraphics::OpenGL: 
  {
    if (project == EProjection::Orthogonal) 
    { 
      return detail::OpenGlOrtho<TMajor, TType>(fovY, width, height, near, far);
    }
    else
    {
      return detail::OpenGlPersp<TMajor, TType>(fovY, width, height, near, far);
    }
  } break;
  default: break;
  }
  return {};
}

template <EMatMajor TMajor, typename TType>
DMatrix4<TType, TMajor> LookAt2(
  const DVector3<TType>& position, 
  const DVector3<TType>& lookPosition,
  const DVector3<TType>& unitY)
{
  return detail::_CommonLookAt<TMajor>(position, lookPosition, unitY);
}

template <EMatMajor TMajor, typename TType>
DMatrix4<TType, TMajor> Translate(
  const DMatrix4<TType, TMajor>& matrix,
  const DVector3<TType>& position)
{
  return detail::_CommonTranslate<TMajor>(matrix, position);
}

template <EMatMajor TMajor, typename TType>
DMatrix4<TType, TMajor> Rotate(const DMatrix4<TType, TMajor>& matrix, const DVector3<TType>& eulerAngle, bool isDegree)
{
  auto radianAngle = eulerAngle;
  if (isDegree == true)
  {
    radianAngle *= kToRadian<TReal>;
  }

  return detail::_CommonRotate(matrix, radianAngle);
}

template <EMatMajor TMajor, typename TType>
DMatrix4<TType, TMajor> Scale(const DMatrix4<TType, TMajor>& matrix, const DVector3<TType>& scale)
{
  return detail::_CommonScale(matrix, scale);
}

template <EMatMajor TMajor, typename TType>
DMatrix4<TType, TMajor> CreateModelMatrix(
  const DVector3<TType>& position,
  const DVector3<TType>& eulerAngle,
  const DVector3<TType>& scale,
  bool isDegree)
{
  return Translate<TReal>( 
    Rotate<TReal>( 
      Scale<TReal>( 
        DMatrix4<TReal, TMajor>::Identity(), scale
      ), eulerAngle, isDegree
    ), position
  ).Transpose();
}

} /// ::dy::math namespace