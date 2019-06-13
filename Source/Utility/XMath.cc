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

/*
 *  Roots3And4.c
 *
 *  Utility functions to find cubic and quartic roots,
 *  coefficients are passed like this:
 *
 *      c[0] + c[1]*x + c[2]*x^2 + c[3]*x^3 + c[4]*x^4 = 0
 *
 *  The functions return the number of non-complex roots and
 *  put the values into the s array.
 *
 *  Author:         Jochen Schwarze (schwarze@isa.de)
 *
 *  Jan 26, 1990    Version for Graphics Gems
 *  Oct 11, 1990    Fixed sign problem for negative q's in SolveQuartic
 *  	    	    (reported by Mark Podlipec),
 *  	    	    Old-style function definitions,
 *  	    	    IsZero() as a macro
 *  Nov 23, 1990    Some systems do not declare acos() and cbrt() in
 *                  <math.h>, though the functions exist in the library.
 *                  If large coefficients are used, EQN_EPS should be
 *                  reduced considerably (e.g. to 1E-30), results will be
 *                  correct but multiple roots might be reported more
 *                  than once.
 */

#include <Math/Utility/XMath.h>
#include <Expr/XMacroes.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/* epsilon surrounding for near zero values */

#define EQN_EPS   1e-9
#define	IsZero(x)	((x) > -EQN_EPS && (x) < EQN_EPS)

#ifdef NOCBRT
#define cbrt(x) ((x) > 0.0 ? pow((double)(x), 1.0/3.0) : \
                ((x) < 0.0 ? -pow((double)-(x), 1.0/3.0) : 0.0))
#endif

namespace dy::math
{
  
std::vector<TReal> SolveQuadric(TReal c2, TReal c1, TReal c0)
{
  /* normal form: x^2 + px + q = 0 */
  const TReal p = c1 / (2 * c2);
  const TReal q = c0 / c2;
  const TReal D = p * p - q;
  std::vector<TReal> result;

  if (IsNearlyZero(D, TReal(1e-5)) == true)
  {
    result.emplace_back(-p);
    return result;
  }
  else if (D > 0)
  {
    TReal sqrt_D = std::sqrt(D);

    result.emplace_back(sqrt_D - p);
    result.emplace_back(-sqrt_D - p);
    std::sort(result.begin(), result.end());
  }

  return result;
}

std::vector<TReal> SolveCubic(TReal c3, TReal c2, TReal c1, TReal c0)
{
  TU32 num;

  /* normal form: x^3 + Ax^2 + Bx + C = 0 */
  const TReal A = c2 / c3;
  const TReal B = c1 / c3;
  const TReal C = c0 / c3;

  /*  substitute x = y - A/3 to eliminate quadric term: x^3 +px + q = 0 */
  const TReal sq_A = A * A;
  const TReal p = TReal(1) / 3 * (TReal(-1) / 3 * sq_A + B);
  const TReal q = TReal(1) / 2 * (TReal(2) / 27 * A * sq_A - TReal(1) / 3 * A * B + C);

  /* use Cardano's formula */
  const TReal cb_p = p * p * p;
  const TReal D = q * q + cb_p;

  std::vector<TReal> result;
  if (IsZero(D))
  {
    if (IsZero(q)) /* one triple solution */
    {
      result.emplace_back(TReal(0));
      num = 1;
    }
    else /* one single and one TReal solution */
    {
      const TReal u = cbrt(-q);
      result.emplace_back(2 * u);
      result.emplace_back(-u);
      num = 2;
    }
  }
  else if (D < 0) /* Casus irreducibilis: three real solutions */
  {
    const TReal phi = TReal(1) / 3 * std::acos(-q / std::sqrt(-cb_p));
    const TReal t = 2 * std::sqrt(-p);

    result.emplace_back(t * std::cos(phi));
    result.emplace_back(-t * std::cos(phi + TReal(M_PI) / 3));
    result.emplace_back(-t * std::cos(phi - TReal(M_PI) / 3));
    num = 3;
  }
  else /* one real solution */
  {
    const TReal sqrt_D = sqrt(D);
    const TReal u = cbrt(sqrt_D - q);
    const TReal v = -cbrt(sqrt_D + q);

    result.emplace_back(u + v);
    num = 1;
  }

  // Resubstitution & Sorting
  const TReal sub = TReal(1) / 3 * A;
  for (auto& value : result) { value -= sub; }
  std::sort(result.begin(), result.end());

  return result;
}

std::vector<TReal> SolveQuartic(TReal c4, TReal c3, TReal c2, TReal c1, TReal c0)
{
  // normal form: x^4 + Ax^3 + Bx^2 + Cx + D = 0 
  const TReal A = c3 / c4;
  const TReal B = c2 / c4;
  const TReal C = c1 / c4;
  const TReal D = c0 / c4;

  // substitute x = y - A/4 to eliminate cubic term: x^4 + px^2 + qx + r = 0
  const TReal sq_A = A * A;
  const TReal p = TReal(-3) / 8 * sq_A + B;
  const TReal q = TReal(1) / 8 * sq_A * A - TReal(1) / 2 * A * B + C;
  const TReal r = TReal(-3) / 256 * sq_A * sq_A + TReal(1) / 16 * sq_A * B - TReal(1) / 4 * A * C + D;

  std::vector<TReal> result;

  if (IsNearlyZero(r, TReal(1e-5)))
  {
    if (IsNearlyZero(q, TReal(1e-5)) == true)
    {
      if (IsNearlyZero(p, TReal(1e-5)) == true) { result.emplace_back(TReal(0)); }
      else
      {
        // y^2(y^2 + p) = 0
        result = SolveQuadric(1, 0, p);
        result.emplace_back(TReal(0));
      }
    }
    else
    {
      // y(y^3 + py + q) = 0 
      result = SolveCubic(1, 0, p, q);
      result.emplace_back(TReal(0));
    }
  }
  else
  {
    // solve the resolvent cubic and take the one real solution ...
    const TReal z = SolveCubic(1, TReal(-1) / 2 * p, -r, TReal(1) / 2 * r * p - TReal(1) / 8 * q * q).front();

    // to build two quadric equations
    TReal u = z * z - r;
    TReal v = 2 * z - p;

    if (IsNearlyZero(u))  { u = 0; }
    else if (u > 0)       { u = sqrt(u); }
    else { return {}; } // Can not find real root values.

    if (IsNearlyZero(v))  { v = 0; }
    else if (v > 0)       { v = sqrt(v); }
    else { return {}; } // Can not find real root values.

    const auto result1 = SolveQuadric(1, q < 0 ? -v : v, z - u);
    const auto result2 = SolveQuadric(1, q < 0 ? v : -v, z + u);
    std::merge(EXPR_BIND_BEGIN_END(result1), EXPR_BIND_BEGIN_END(result2), std::back_inserter(result));
  }

  /* resubstitute */
  const TReal sub = TReal(1) / 4 * A;
  for (auto& value : result) { value -= sub; }

  return result;
}

} /// ::dy::math namespace