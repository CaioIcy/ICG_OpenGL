#pragma once

#include <GL/glew.h>

namespace ogle {

/**
* @todo Assert that the buffers were successfully created before rendering/binding/whatever.
*/
class VertexArray {

	public:
		VertexArray(); // delete
		VertexArray(const float* const vertices, const size_t size_vertices);

		void Render();

	private:
		void Bind();
		void Unbind();
		void Draw();

		GLuint m_vao;
		GLuint m_vbo;
};

} // namespace ogle
