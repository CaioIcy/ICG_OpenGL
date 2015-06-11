#pragma once

namespace ogle {

class vec4 {

	public:
		vec4(const float xx, const float yy, const float zz, const float ww);

		vec4& operator+=(const vec4& rhs);
		vec4& operator-=(const vec4& rhs);
		vec4& operator*=(const vec4& rhs);
		vec4& operator/=(const vec4& rhs);

		float x;
		float y;
		float z;
		float w;
};

inline vec4 operator+(vec4 lhs, const vec4& rhs);
inline vec4 operator-(vec4 lhs, const vec4& rhs);
inline vec4 operator*(vec4 lhs, const vec4& rhs);
inline vec4 operator/(vec4 lhs, const vec4& rhs);

} // namespace ogle
