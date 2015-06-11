#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(GLsizeiptr size, const GLvoid* data, GLenum usage, bool no) :
	m_id{0},
	m_num_indices{(GLsizei)(size / sizeof(GLuint))}
{
	// FOR STACK ARRAYS ONLY. PROBABLY DELETE THIS LATER
	(void)no;
	glGenBuffers(1, &m_id);
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
	IndexBuffer::Unbind();
}

IndexBuffer::IndexBuffer(GLsizei size, const GLuint* data, GLenum usage) :
	m_id{0},
	m_num_indices{size}
{
	glGenBuffers(1, &m_id);
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(GLuint), data, usage);
	IndexBuffer::Unbind();
}

IndexBuffer::~IndexBuffer() {
	glDeleteBuffers(1, &m_id);
}

void IndexBuffer::Bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

GLsizei IndexBuffer::NumIndices() {
	return m_num_indices;
}

void IndexBuffer::Unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
