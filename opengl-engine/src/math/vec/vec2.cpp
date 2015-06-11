#include "math/vec/vec2.h"

namespace ogle {

vec2::vec2(const float xx, const float yy) :
	x{xx},
	y{yy}
{
}

vec2& vec2::operator+=(const vec2& rhs) {
	x += rhs.x;
	y += rhs.y;
	return *this;	
}

vec2& vec2::operator-=(const vec2& rhs) {
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

vec2& vec2::operator*=(const vec2& rhs) {
	x *= rhs.x;
	y *= rhs.y;
	return *this;
}

vec2& vec2::operator/=(const vec2& rhs) {
	x /= rhs.x;
	y /= rhs.y;
	return *this;
}

inline vec2 operator+(vec2 lhs, const vec2& rhs) {
	lhs += rhs;
	return lhs;
}

inline vec2 operator-(vec2 lhs, const vec2& rhs) {
	lhs -= rhs;
	return lhs;
}

inline vec2 operator*(vec2 lhs, const vec2& rhs) {
	lhs *= rhs;
	return lhs;
}

inline vec2 operator/(vec2 lhs, const vec2& rhs) {
	lhs /= rhs;
	return lhs;
}

} // namespace ogle
