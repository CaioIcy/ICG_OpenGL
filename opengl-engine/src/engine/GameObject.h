#pragma once

#include <string>
#include <memory>
#include <glm/glm.hpp>

namespace ogle {

class ShaderProgram;
// class VertexArray;

class GameObject {

	public:
		GameObject(const std::string shader_file_name, const float* const vertices,
			const size_t size_vertices);

		void Update(const double dt);
		void Render();

		void SetX(const float x);
		void SetY(const float y);
		void SetTime(const float time); //delete

	private:
		std::unique_ptr<ShaderProgram> m_program;
		// std::unique_ptr<VertexArray> m_vertex_array;
		glm::vec3 m_position;
};

} // namespace ogle
