#include "graphics/Renderable.h"
#include "graphics/buffers/IndexBuffer.h"
#include "math/Math.h"
#include "util/Assert.h"
#include "graphics/ShapeData.h"
#include "graphics/buffers/ArrayBuffer.h"
#include "graphics/VertexData.h"

Renderable::Renderable() :
	m_shape_data{nullptr},
	m_vao{},
	m_ibo{nullptr},
	m_fed{false}
{
}

Renderable::~Renderable() {
	if(m_shape_data) delete m_shape_data;
	if(m_ibo) delete m_ibo;
}

void Renderable::Bind() {
	ASSERT(m_fed == true, "should be fed");
	m_vao.Bind();
	m_ibo->Bind();
}

void Renderable::Unbind() {
	ASSERT(m_fed == true, "should be fed");
	IndexBuffer::Unbind();
	VertexArray::Unbind();
}

void Renderable::Feed(ShapeData* sd) {
	m_shape_data = sd;
	m_vao.AddBuffer(new ArrayBuffer(sd->num_vertices * VertexData::TOTAL_COMPONENTS, sd->vertices, GL_STATIC_DRAW));
	m_ibo = new IndexBuffer(sd->num_indices, sd->indices, GL_STATIC_DRAW);
	m_fed = true;
}

VertexArray& Renderable::VAO() {
	return m_vao;
}

IndexBuffer* Renderable::IBO() const {
	ASSERT(m_fed == true, "should be fed");
	return m_ibo;
}

ShapeData* Renderable::SD() const {
	return m_shape_data;
}
