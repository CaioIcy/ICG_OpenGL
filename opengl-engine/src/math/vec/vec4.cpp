#include "math/vec/vec4.h"

namespace ogle {

vec4::vec4(const float xx, const float yy, const float zz, const float ww) :
	x{xx},
	y{yy},
	z{zz},
	w{ww}
{
}

vec4& vec4::operator+=(const vec4& rhs) {
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	w += rhs.w;
	return *this;	
}

vec4& vec4::operator-=(const vec4& rhs) {
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	w -= rhs.w;
	return *this;
}

vec4& vec4::operator*=(const vec4& rhs) {
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;
	w *= rhs.w;
	return *this;
}

vec4& vec4::operator/=(const vec4& rhs) {
	x /= rhs.x;
	y /= rhs.y;
	z /= rhs.z;
	w /= rhs.w;
	return *this;
}

inline vec4 operator+(vec4 lhs, const vec4& rhs) {
	lhs += rhs;
	return lhs;
}

inline vec4 operator-(vec4 lhs, const vec4& rhs) {
	lhs -= rhs;
	return lhs;
}

inline vec4 operator*(vec4 lhs, const vec4& rhs) {
	lhs *= rhs;
	return lhs;
}

inline vec4 operator/(vec4 lhs, const vec4& rhs) {
	lhs /= rhs;
	return lhs;
}

} // namespace ogle
