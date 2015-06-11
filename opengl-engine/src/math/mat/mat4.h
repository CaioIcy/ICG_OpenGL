#pragma once

#include "math/vec/vec3.h"

namespace ogle {

class mat4 {

	public:
		static mat4 identity();
		static mat4 orthographic(const float left, const float right, const float bottom,
			const float top, const float near, const float far);
		static mat4 perspective(const float fov, const float aspect_ratio, const float near,
			const float far);
		static mat4 translation(const vec3& t);
		static mat4 rotation(const float angle, const vec3& axis);
		static mat4 scale(const vec3& s);

		mat4();
		mat4(const float diagonal);

		mat4& operator*=(const mat4& rhs);

		float elements[4*4];
};

inline mat4 operator*(mat4 lhs, const mat4& rhs) {
	lhs *= rhs;
	return lhs;
}

} // namespace ogle
