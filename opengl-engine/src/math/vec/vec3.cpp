#include "math/vec/vec3.h"

namespace ogle {

vec3::vec3(const float xx, const float yy, const float zz) :
	x{xx},
	y{yy},
	z{zz}
{
}

vec3& vec3::operator+=(const vec3& rhs) {
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;	
}

vec3& vec3::operator-=(const vec3& rhs) {
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

vec3& vec3::operator*=(const vec3& rhs) {
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;
	return *this;
}

vec3& vec3::operator/=(const vec3& rhs) {
	x /= rhs.x;
	y /= rhs.y;
	z /= rhs.z;
	return *this;
}

inline vec3 operator+(vec3 lhs, const vec3& rhs) {
	lhs += rhs;
	return lhs;
}

inline vec3 operator-(vec3 lhs, const vec3& rhs) {
	lhs -= rhs;
	return lhs;
}

inline vec3 operator*(vec3 lhs, const vec3& rhs) {
	lhs *= rhs;
	return lhs;
}

inline vec3 operator/(vec3 lhs, const vec3& rhs) {
	lhs /= rhs;
	return lhs;
}

} // namespace ogle
