#include "graphics/buffers/VertexArray.h"
#include "graphics/buffers/ArrayBuffer.h"
#include "graphics/VertexData.h"

VertexArray::VertexArray() :
	m_id{0},
	m_array_buffers{}
{
	glGenVertexArrays(1, &m_id);
}

VertexArray::~VertexArray() {
	for(auto buffer : m_array_buffers) {
		delete buffer;
	}

	glDeleteVertexArrays(1, &m_id);
}

void VertexArray::Bind() {
	glBindVertexArray(m_id);
}

void VertexArray::AddBuffer(ArrayBuffer* buffer) {
	Bind();
	buffer->Bind();
	m_array_buffers.push_back(buffer);

	glEnableVertexAttribArray(VertexData::LOC_POSITION);
	glVertexAttribPointer(VertexData::LOC_POSITION, VertexData::CMP_POSITION, GL_FLOAT, GL_FALSE,
		VertexData::TOTAL_COMPONENTS * sizeof(GLfloat), GL_OFFSETOF(VertexData, position));

	glEnableVertexAttribArray(VertexData::LOC_COLOR);
	glVertexAttribPointer(VertexData::LOC_COLOR, VertexData::CMP_COLOR, GL_FLOAT, GL_FALSE,
		VertexData::TOTAL_COMPONENTS * sizeof(GLfloat), GL_OFFSETOF(VertexData, color));

	buffer->Unbind();
	VertexArray::Unbind();
}

void VertexArray::Unbind() {
	glBindVertexArray(0);
}
