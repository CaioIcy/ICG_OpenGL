#pragma once

#include <GL/glew.h>

class VertexData;

struct ShapeData {

	ShapeData();
	~ShapeData();

	GLsizeiptr VertexBufferSize() const;
	GLsizeiptr IndexBufferSize() const;

	VertexData* vertices;
	GLuint num_vertices;
	GLuint* indices;
	GLuint num_indices;
};
