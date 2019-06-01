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

#include <Math/Type/Math/DVector3.h>
#include <Math/Type/Color/DColorRGB.h>
#include <Math/Utility/XMath.h>
#include <cmath>
#include <algorithm>

#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif

namespace dy::math
{

/// @brief 
/// @param 
template <typename TType>
DColorRGB<TType> HueToRgb(TType hue)
{
  hue = Frac(hue); 
  TType r = std::abs(hue * 6 - 3) - 1;    // Red
  TType g = 2 - std::abs(hue * 6 - 2);    // Green
  TType b = 2 - std::abs(hue * 6 - 4);    // Blue

  auto rgb = DVector3<TType>{ r, g, b };  // Combine components
  rgb = Saturate(rgb);                    // Clamp between 0 and 1

  return { rgb.X, rgb.Y, rgb.Z };
}

template <typename TType>
DColorRGB<TType> HsvToRgb(const DVector3<TType>& hsv)
{
  auto rgb = HueToRgb(hsv.X);
  rgb = Lerp(DColorRGB<TType>{1.0}, rgb, hsv.Y);
  rgb = rgb * hsv.Z;

  return rgb;
}

/// @brief Convert RGB to [0, 1] Hue, saturation and value (Brightness).
/// @param rgb RGB color vector.
/// @reference https://www.ronja-tutorials.com/2019/04/16/hsv-colorspace.html
template <typename TType>
DVector3<TType> RgbToHsv(const DColorRGB<TType>& rgb)
{
  TType maxComp = std::max<TType>({ rgb.R, rgb.G, rgb.B });
  TType minComp = std::min<TType>({ rgb.R, rgb.G, rgb.B });
  TType diff    = maxComp - minComp;
  TType hue     = 0;

       if (maxComp == rgb.R) { hue = 0 + (rgb.G - rgb.B) / diff; }
  else if (maxComp == rgb.G) { hue = 2 + (rgb.B - rgb.R) / diff; }
  else if (maxComp == rgb.B) { hue = 4 + (rgb.R - rgb.G) / diff; }

  hue = (hue / 6) - static_cast<TI32>(hue / 6);

  TType saturation  = diff / maxComp;
  TType value       = maxComp;
  return DVector3<TType>{hue, saturation, value};
}

/// @brief Convert RGB to [0, 1] Hue, Saturation and Brightness Value.
/// @param rgb24 RGB color vector (24bit TU8 component type).
DVector3<TType> RgbToHsv(const DColorRGB24& rgb24)
{
  return RgbToHsv(static_cast<DColorRGB<TReal>>(rgb24));
}

/// @brief Helper function of TReal conversion from RGB to HSV.
/// @param rgb RGB color vector.
DVector3<TReal> RgbToHsvR(const DColorRGB<TReal>& rgb)
{
  return RgbToHsv<TReal>(rgb);
}

} /// ::dy::math namespace
