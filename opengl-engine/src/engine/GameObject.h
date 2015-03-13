#pragma once

#include <string>
#include <memory>
#include <glm/glm.hpp>

namespace ogle {

class ShaderProgram;
class VertexArray;

class GameObject {

	public:
		GameObject(const std::string shader_file_name);

		void Update(const double dt);
		void Render();

		void SetXY(const float x, const float y, const float z);

	private:
		std::unique_ptr<ShaderProgram> m_program;
		std::unique_ptr<VertexArray> m_vertex_array;
		glm::vec4 m_position;
};

} // namespace ogle
