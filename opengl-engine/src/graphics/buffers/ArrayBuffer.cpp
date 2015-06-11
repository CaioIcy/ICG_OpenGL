#include "ArrayBuffer.h"

ArrayBuffer::ArrayBuffer(GLsizeiptr size, const GLvoid* data) :
	m_id{0}
{
	// FOR STACK ARRAYS ONLY. PROBABLY DELETE THIS LATER
	glGenBuffers(1, &m_id);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	ArrayBuffer::Unbind();
}

ArrayBuffer::ArrayBuffer(GLsizei size, const GLvoid* data, GLenum usage) :
	m_id{0}
{
	glGenBuffers(1, &m_id);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), data, usage);
	ArrayBuffer::Unbind();
}

ArrayBuffer::~ArrayBuffer() {
	glDeleteBuffers(1, &m_id);
}

void ArrayBuffer::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void ArrayBuffer::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
