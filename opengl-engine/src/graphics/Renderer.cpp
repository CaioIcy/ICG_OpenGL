#include "graphics/Renderer.h"
#include "graphics/Renderable.h"
#include "graphics/buffers/IndexBuffer.h"
#include "graphics/ShapeData.h"
#include <iostream>

Renderer::Renderer() :
	m_renderables{},
	m_transformations{},
	m_transformation_back{},
	m_mesh{new Mesh()}
{
}

Renderer::~Renderer() {
	for(auto renderable : m_renderables) {
		delete renderable;
	}
}

Renderable* Renderer::Init(string path){
	return m_mesh->LoadMesh(path);
}

void Renderer::Submit(Renderable* renderable) {
	m_renderables.push_back(renderable);
}

void Renderer::Render() {
	for(auto renderable : m_renderables) {
		
		renderable->VAO().Bind();
		
		/*glEnableVertexAttribArray(VertexData::LOC_POSITION);
		glVertexAttribPointer(VertexData::LOC_POSITION, VertexData::CMP_POSITION, GL_FLOAT, GL_FALSE,
		VertexData::TOTAL_COMPONENTS * sizeof(GLfloat), GL_OFFSETOF(VertexData, position));

		glEnableVertexAttribArray(VertexData::LOC_COLOR);
		glVertexAttribPointer(VertexData::LOC_COLOR, VertexData::CMP_COLOR, GL_FLOAT, GL_FALSE,
		VertexData::TOTAL_COMPONENTS * sizeof(GLfloat), GL_OFFSETOF(VertexData, color));*/
		
		renderable->IBO()->Bind();
		
		glDrawElements(GL_TRIANGLES, renderable->IBO()->NumIndices(), GL_UNSIGNED_INT, nullptr);
	}
}

void Renderer::Push(const mat4& matrix) {
	m_transformations.push_back(matrix);
}

void Renderer::Pop() {
	if(!m_transformations.empty()) {
		m_transformation_back = m_transformations.back();
		m_transformations.pop_back();
	}
}

mat4 Renderer::GetNextTransformation() {
	Pop();
	return m_transformation_back;
}

Mesh* Renderer::GetMesh(){
	return m_mesh;
}
