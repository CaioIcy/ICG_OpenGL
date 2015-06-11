#pragma once

#include <GL/glew.h>

class ArrayBuffer {
	public:
		ArrayBuffer(GLsizeiptr size, const GLvoid* data);
		ArrayBuffer(GLsizei size, const GLvoid* data, GLenum usage);

		~ArrayBuffer();

		void Bind();

		static void Unbind();

	private:
		GLuint m_id;
};
