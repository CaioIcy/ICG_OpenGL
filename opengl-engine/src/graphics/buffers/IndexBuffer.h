#pragma once

#include <GL/glew.h>

class IndexBuffer {

	public:
		IndexBuffer(GLsizeiptr size, const GLvoid* data, GLenum usage, bool no);
		IndexBuffer(GLsizei size, const GLuint* data, GLenum usage);

		~IndexBuffer();

		void Bind();
		GLsizei NumIndices();

		static void Unbind();

	private:
		GLuint m_id;
		GLsizei m_num_indices;
};
