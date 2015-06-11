#include "math/mat/mat4.h"
#include <cmath>
#include <cstring>
#include "math/MathUtils.h"
#include "util/Assert.h"

namespace ogle {

mat4::mat4() {
	for(int i = 0; i < 4*4; ++i) {
		elements[i] = 0.0f;
	}
}

mat4::mat4(const float diagonal) {
	for(int i = 0; i < 4*4; ++i) {
		elements[i] = 0.0f;
	}

	elements[0 + 0 * 4] = diagonal;
	elements[1 + 1 * 4] = diagonal;
	elements[2 + 2 * 4] = diagonal;
	elements[3 + 3 * 4] = diagonal;
}

mat4 mat4::identity() {
	return mat4(1.0f);
}

mat4 mat4::orthographic(const float left, const float right, const float bottom,
		const float top, const float near, const float far) {
	ASSERT((right - left) != 0.0f, "Can't divide by zero.");
	ASSERT((top - bottom) != 0.0f, "Can't divide by zero.");
	ASSERT((near - far) != 0.0f, "Can't divide by zero.");
	ASSERT((left - right) != 0.0f, "Can't divide by zero.");
	ASSERT((bottom - top) != 0.0f, "Can't divide by zero.");
	ASSERT((far - near) != 0.0f, "Can't divide by zero.");

	mat4 result{};

	// Main diagonal.
	result.elements[0 + 0 * 4] = 2.0f / (right - left);
	result.elements[1 + 1 * 4] = 2.0f / (top - bottom);
	result.elements[2 + 2 * 4] = 2.0f / (near - far);
	result.elements[3 + 3 * 4] = 1.0f;

	// Last column.
	result.elements[0 + 3 * 4] = (left + right) / (left - right);
	result.elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
	result.elements[2 + 3 * 4] = (far + near) / (far - near);

	return result;
}

mat4 mat4::perspective(const float fov, const float aspect_ratio, const float near,
		const float far) {
	ASSERT(std::tan(math::ToRadians(fov)) != 0.0f, "Can't divide by zero.");
	ASSERT((near - far) != 0.0f, "Can't divide by zero.");

	mat4 result{};

	const float q = 1.0f / std::tan(math::ToRadians(fov));
	const float a = q / aspect_ratio;
	const float b = (near + far) / (near - far);
	const float c = (2.0f * near * far) / (near - far);

	result.elements[0 + 0 * 4] = a;
	result.elements[1 + 1 * 4] = q;
	result.elements[2 + 2 * 4] = b;
	result.elements[3 + 2 * 4] = -1.0f;
	result.elements[2 + 3 * 4] = c;

	return result;
}

mat4 mat4::translation(const vec3& t) {
	mat4 result = mat4::identity();

	result.elements[0 + 3 * 4] = t.x;
	result.elements[1 + 3 * 4] = t.y;
	result.elements[2 + 3 * 4] = t.z;

	return result;
}

mat4 mat4::rotation(const float angle, const vec3& axis) {
	mat4 result = mat4::identity();

	const float r = math::ToRadians(angle);
	const float c = std::cos(r);
	const float s = std::sin(r);
	const float omc = 1.0f - c;
	const float x = axis.x;
	const float y = axis.y;
	const float z = axis.z;

	result.elements[0 + 0 * 4] = (x * omc) + c;
	result.elements[1 + 0 * 4] = (y * x * omc) + (z * s);
	result.elements[2 + 0 * 4] = (x * z * omc) - (y * s);

	result.elements[0 + 1 * 4] = (x * y * omc) - (z * s);
	result.elements[1 + 1 * 4] = (y * omc) + c;
	result.elements[2 + 1 * 4] = (y * z * omc) + (x * s);

	result.elements[0 + 2 * 4] = (x * z * omc) + (y * s);
	result.elements[1 + 2 * 4] = (y * z * omc) - (x * s);
	result.elements[2 + 2 * 4] = (z * omc) + c;

	return result;
}

mat4 mat4::scale(const vec3& s) {
	mat4 result{};

	result.elements[0 + 0 * 4] = s.x;
	result.elements[1 + 1 * 4] = s.y;
	result.elements[2 + 2 * 4] = s.z;
	result.elements[3 + 3 * 4] = 1.0f;

	return result;
}

mat4& mat4::operator*=(const mat4& rhs) {
	float result[16];
	for(int y = 0; y < 4; ++y) {
		for(int x = 0; x < 4; ++x) {
			float sum = 0.0f;
			for(int e = 0; e < 4; ++e) {
				sum += elements[x + e * 4] * rhs.elements[e + y * 4];
			}
			result[x + y * 4] = sum;
		}
	}
	std::memcpy(elements, result, sizeof(float) * 4 * 4);
	return *this;
}

} // namespace ogle
