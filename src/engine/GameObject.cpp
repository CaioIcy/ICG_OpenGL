#include "engine/GameObject.h"
#include "graphics/ShaderProgram.h"
#include "graphics/VertexArray.h"

namespace ogle {

GameObject::GameObject(const std::string shader_file_name) :
	m_program{std::make_unique<ShaderProgram>(shader_file_name)},
	m_vertex_array{std::make_unique<VertexArray>()},
	m_position{0, 0, 0}
{
}

void GameObject::Update(const double dt) {

}

void GameObject::Render() {
	m_program->Enable();
	m_vertex_array->Render();
	m_program->Disable();
}

void GameObject::SetXY(const float x, const float y) {
	m_position.x = x;
	m_position.y = y;

	m_program->Enable();
	m_program->SetUniform2f("offset", m_position.x, m_position.y);
	m_program->Disable();
}

} // namespace ogle
