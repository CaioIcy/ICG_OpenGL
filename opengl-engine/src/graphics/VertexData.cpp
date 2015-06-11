#include "graphics/VertexData.h"

VertexData::VertexData() :
	position{},
	color{}
{}

VertexData::VertexData(
		const float x, const float y, const float z,
		const float r, const float g, const float b, const float a) :
	position{x, y, z},
	color{r, g, b, a}
{}
