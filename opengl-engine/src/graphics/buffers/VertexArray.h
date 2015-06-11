#pragma once

#include <GL/glew.h>
#include <vector>

class ArrayBuffer;

class VertexArray {

	public:
		VertexArray();
		~VertexArray();

		void Bind();
		void AddBuffer(ArrayBuffer* buffer);

		static void Unbind();

	private:
		GLuint m_id;
		std::vector<ArrayBuffer*> m_array_buffers;
};
