#include "graphics/ShapeData.h"
#include "graphics/VertexData.h"

ShapeData::ShapeData() :
	vertices{nullptr},
	num_vertices{0},
	indices{nullptr},
	num_indices{0} 
{}

ShapeData::~ShapeData() {
	delete[] vertices;
	delete[] indices;
}

GLsizeiptr ShapeData::VertexBufferSize() const {
	return num_vertices * sizeof(VertexData);
}

GLsizeiptr ShapeData::IndexBufferSize() const {
	return num_indices * sizeof(GLuint);
}
