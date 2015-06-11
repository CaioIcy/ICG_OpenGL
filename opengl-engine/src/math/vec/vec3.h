#pragma once

namespace ogle {

class vec3 {

	public:
		vec3(const float xx, const float yy, const float zz);

		vec3& operator+=(const vec3& rhs);
		vec3& operator-=(const vec3& rhs);
		vec3& operator*=(const vec3& rhs);
		vec3& operator/=(const vec3& rhs);

		float x;
		float y;
		float z;
};

inline vec3 operator+(vec3 lhs, const vec3& rhs);
inline vec3 operator-(vec3 lhs, const vec3& rhs);
inline vec3 operator*(vec3 lhs, const vec3& rhs);
inline vec3 operator/(vec3 lhs, const vec3& rhs);

} // namespace ogle
