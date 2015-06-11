#pragma once

#include <GL/glew.h>
#include "graphics/buffers/VertexArray.h"

class IndexBuffer;
class ShapeData;

class Renderable {
	public:
		Renderable();
		~Renderable();

		void Bind();
		void Unbind();
		void Feed(ShapeData* sd);

		VertexArray& VAO();
		IndexBuffer* IBO() const;
		ShapeData* SD() const;

	private:
		ShapeData* m_shape_data;
		VertexArray m_vao;
		IndexBuffer* m_ibo;
		bool m_fed;
};
