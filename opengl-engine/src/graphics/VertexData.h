#pragma once

#include <cstddef>
#include "math/Math.h"

#define GL_OFFSETOF(type, member) ((const void*)offsetof(type, member))

struct VertexData {
	VertexData();

	VertexData(	const float x, const float y, const float z,
				const float r, const float g, const float b, const float a);

	vec3 position;
	static constexpr int LOC_POSITION = 0;
	static constexpr int CMP_POSITION = 3;

	vec4 color;
	static constexpr int LOC_COLOR = 1;
	static constexpr int CMP_COLOR = 4;
	
	static constexpr int TOTAL_COMPONENTS = CMP_POSITION + CMP_COLOR;
};
