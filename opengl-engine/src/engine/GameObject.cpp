#include "engine/GameObject.h"
#include "graphics/ShaderProgram.h"

namespace ogle {

GameObject::GameObject(const std::string shader_file_name, const float* const vertices,
		const size_t size_vertices) :
	m_program{std::make_unique<ShaderProgram>(shader_file_name)},
	// m_vertex_array{std::make_unique<VertexArray>(vertices, size_vertices)},
	m_position{0, 0, 0}
{
}

void GameObject::Update(const double dt) {
	m_program->Enable();
	// ?
	m_program->Disable();
}

void GameObject::Render() {
	m_program->Enable();
	// m_vertex_array->Render();
	m_program->Disable();
}

void GameObject::SetX(const float x) {
	m_position.x = x;
}

void GameObject::SetY(const float y) {
	m_position.y = y;
}

void GameObject::SetTime(const float time) {
	m_program->Enable();
	m_program->SetUniform1f("time", time);
	m_program->Disable();
}

} // namespace ogle
