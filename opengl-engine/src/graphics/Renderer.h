#pragma once

#include <GL/glew.h>
#include <vector>
#include "math/Math.h"
#include "mesh.h"

class Renderable;

class Renderer {

	public:
		Renderer();
		~Renderer();

		void Submit(Renderable* renderable);
		void Render();

		void Push(const mat4& matrix);
		void Pop();
		Renderable* Init(string path);
		Mesh* GetMesh();
		mat4 GetNextTransformation();

	private:
		std::vector<Renderable*> m_renderables;
		std::vector<mat4> m_transformations;
		mat4 m_transformation_back;
		Mesh* m_mesh;
};
