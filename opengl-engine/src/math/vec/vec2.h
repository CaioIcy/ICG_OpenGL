#pragma once

namespace ogle {

class vec2 {

	public:
		vec2(const float xx, const float yy);

		vec2& operator+=(const vec2& rhs);
		vec2& operator-=(const vec2& rhs);
		vec2& operator*=(const vec2& rhs);
		vec2& operator/=(const vec2& rhs);

		float x;
		float y;
};

inline vec2 operator+(vec2 lhs, const vec2& rhs);
inline vec2 operator-(vec2 lhs, const vec2& rhs);
inline vec2 operator*(vec2 lhs, const vec2& rhs);
inline vec2 operator/(vec2 lhs, const vec2& rhs);

} // namespace ogle
