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

namespace dy::math
{

template <typename TType>
DVector3<TType> Reflect(const DVector3<TType>& incident, const DVector3<TType>& normal)
{
  return 2.0f * Dot(incident, normal) * normal - incident;
}

template <typename TType, typename TScalar>
std::optional<DVector3<TType>> Refract(
  TScalar incidentIor, TScalar transmitIor, 
  const DVector3<TType>& incident, const DVector3<TType>& normal)
{
  // Reference https://physics.stackexchange.com/questions/435512/snells-law-in-vector-form
  const auto mu = TType(incidentIor) / TType(transmitIor);
  const auto nm = normal * -1.0f;
  const auto ni = Dot(incident, nm);
  const auto disc2 = 1 - (mu * mu) * (1 - (ni * ni));

  // Transmitted vector's the angle must be less than pi / 2. (90' degree).
  if (disc2 < 0) { return std::nullopt; }

  return (sqrt(disc2) * nm) + (mu * (incident - (ni * nm))) * TType(-1.0);
}

template <typename TType, typename TScalar>
TReal Schlick(
  TScalar incidentIor, TScalar transmitIor, 
  const DVector3<TType>& incident, const DVector3<TType>& normal)
{
  // https://en.wikipedia.org/wiki/Schlick%27s_approximation
  const auto ro = std::pow(
      (incidentIor - transmitIor) / (incidentIor + transmitIor)
    , 2.0f);
  return TReal(
      ro 
    + (1 - ro) * std::pow((1 - Dot(incident, normal)), 5.0f)
  );
}

} /// ::dy::math namespace