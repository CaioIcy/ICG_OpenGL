#include "graphics/VertexArray.h"
#include "util/GlLog.h"

namespace ogle {

VertexArray::VertexArray() :
	m_vao{0},
	m_vbo{0}
{
	const float vertices[] = {
		// triangle 1 vertices
		 0.25f,  0.25f, 0.0f, 1.0f,
		 0.25f, -0.25f, 0.0f, 1.0f,
		-0.25f, -0.25f, 0.0f, 1.0f,
	};

	// VAO
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	// VBO
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	Unbind();
}

VertexArray::VertexArray(const float* const vertices, const size_t size_vertices) :
	m_vao{0},
	m_vbo{0}
{
	// VAO
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	CHECK_GL_ERRORS("Creating a vertex array VAO.");

	// VBO
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, size_vertices, vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
	CHECK_GL_ERRORS("Creating a vertex array VBO.");

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	Unbind();
}

void VertexArray::Render() {
	Bind();
	Draw();
	Unbind();
}

void VertexArray::Bind() {
	glBindVertexArray(m_vao);
}

void VertexArray::Unbind() {
	glBindVertexArray(0);
}

void VertexArray::Draw() {
	glDrawArrays(GL_TRIANGLES, 0, 3);
	CHECK_GL_ERRORS("Rendering the vertex array.");
}


} // namespace ogle
