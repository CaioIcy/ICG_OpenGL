#include "ShapeGenerator.h"
#include <cstring>
#include "graphics/VertexData.h"
#include "graphics/Renderable.h"
#include "graphics/ShapeData.h"

#define NUM_ARRAY_ELEMENTS(array) sizeof(array) / sizeof(*array)

constexpr float PI{3.14159265359};

namespace ShapeGenerator {

Renderable* GenerateTriangle() {
	VertexData triangle[] = {
	//     x      y     z     r      g     b    a
		{-1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f},
		{ 0.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f},
		{ 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f}
	};
	GLuint indices[] = {
		0, 1, 2
	};
	ShapeData* shape_data = new ShapeData();

	// Vertices information
	shape_data->num_vertices = NUM_ARRAY_ELEMENTS(triangle);
	shape_data->vertices = new VertexData[shape_data->num_vertices];
	std::memcpy(shape_data->vertices, triangle, sizeof triangle);

	// Indices information	
	shape_data->num_indices = NUM_ARRAY_ELEMENTS(indices);
	shape_data->indices = new GLuint[shape_data->num_indices];
	std::memcpy(shape_data->indices, indices, sizeof indices);
	
	Renderable* r = new Renderable();
	r->Feed(shape_data);
	return r;
}

Renderable* GenerateQuad() {
	const float p = 0.75f;
	VertexData quad[] = {
	//     x      y     z     r      g     b    a
		{p, p, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f},
		{-p, p, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f},
		{p, -p, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f},
		{-p, -p, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f}
	};
	GLuint indices[] = {
		0, 1, 2,
		1, 2, 3
	};
	ShapeData* shape_data = new ShapeData();

	// Vertices information
	shape_data->num_vertices = NUM_ARRAY_ELEMENTS(quad);
	shape_data->vertices = new VertexData[shape_data->num_vertices];
	std::memcpy(shape_data->vertices, quad, sizeof quad);

	// Indices information	
	shape_data->num_indices = NUM_ARRAY_ELEMENTS(indices);
	shape_data->indices = new GLuint[shape_data->num_indices];
	std::memcpy(shape_data->indices, indices, sizeof indices);
	
	Renderable* r = new Renderable();
	r->Feed(shape_data);
	return r;
}

Renderable* GenerateCube() {
	VertexData cube[] = {
	//     x      y      z      r      g      b     a
		{-1.0f, +1.0f, +1.0f,  // 0
		+1.0f, +0.0f, +0.0f, 1.0f},
		{+1.0f, +1.0f, +1.0f,  // 1
		+0.0f, +1.0f, +0.0f, 1.0f},
		{+1.0f, +1.0f, -1.0f,  // 2
		+0.0f, +0.0f, +1.0f, 1.0f},
		{-1.0f, +1.0f, -1.0f,  // 3
		+1.0f, +1.0f, +1.0f, 1.0f},
			
		{-1.0f, +1.0f, -1.0f,  // 4
		+1.0f, +0.0f, +1.0f, 1.0f},
		{+1.0f, +1.0f, -1.0f,  // 5
		+0.0f, +0.5f, +0.2f, 1.0f},
		{+1.0f, -1.0f, -1.0f,  // 6
		+0.8f, +0.6f, +0.4f, 1.0f},
		{-1.0f, -1.0f, -1.0f,  // 7
		+0.3f, +1.0f, +0.5f, 1.0f},

		{+1.0f, +1.0f, -1.0f,  // 8
		+0.2f, +0.5f, +0.2f, 1.0f},
		{+1.0f, +1.0f, +1.0f,  // 9
		+0.9f, +0.3f, +0.7f, 1.0f},
		{+1.0f, -1.0f, +1.0f,  // 10
		+0.3f, +0.7f, +0.5f, 1.0f},
		{+1.0f, -1.0f, -1.0f,  // 11
		+0.5f, +0.7f, +0.5f, 1.0f},

		{-1.0f, +1.0f, +1.0f,  // 12
		+0.7f, +0.8f, +0.2f, 1.0f},
		{-1.0f, +1.0f, -1.0f,  // 13
		+0.5f, +0.7f, +0.3f, 1.0f},
		{-1.0f, -1.0f, -1.0f,  // 14
		+0.4f, +0.7f, +0.7f, 1.0f},
		{-1.0f, -1.0f, +1.0f,  // 15
		+0.2f, +0.5f, +1.0f, 1.0f},

		{+1.0f, +1.0f, +1.0f,  // 16
		+0.6f, +1.0f, +0.7f, 1.0f},
		{-1.0f, +1.0f, +1.0f,  // 17
		+0.6f, +0.4f, +0.8f, 1.0f},
		{-1.0f, -1.0f, +1.0f,  // 18
		+0.2f, +0.8f, +0.7f, 1.0f},
		{+1.0f, -1.0f, +1.0f,  // 19
		+0.2f, +0.7f, +1.0f, 1.0f},

		{+1.0f, -1.0f, -1.0f,  // 20
		+0.8f, +0.3f, +0.7f, 1.0f},
		{-1.0f, -1.0f, -1.0f,  // 21
		+0.8f, +0.9f, +0.5f, 1.0f},
		{-1.0f, -1.0f, +1.0f,  // 22
		+0.5f, +0.8f, +0.5f, 1.0f},
		{+1.0f, -1.0f, +1.0f,  // 23
		+0.9f, +1.0f, +0.2f, 1.0f},
	};

	GLuint indices[] = {
		 0,  1,  2,  0,  2,  3, // Top
		 4,  5,  6,  4,  6,  7, // Front
		 8,  9, 10,  8, 10, 11, // Right 
		12, 13, 14, 12, 14, 15, // Left
		16, 17, 18, 16, 18, 19, // Back
		20, 22, 21, 20, 23, 22, // Bottom
	};
	ShapeData* shape_data = new ShapeData();

	// Vertices information
	shape_data->num_vertices = NUM_ARRAY_ELEMENTS(cube);
	shape_data->vertices = new VertexData[shape_data->num_vertices];
	std::memcpy(shape_data->vertices, cube, sizeof cube);

	// Indices information	
	shape_data->num_indices = NUM_ARRAY_ELEMENTS(indices);
	shape_data->indices = new GLuint[shape_data->num_indices];
	std::memcpy(shape_data->indices, indices, sizeof indices);

	Renderable* r = new Renderable();
	r->Feed(shape_data);
	return r;
}

} // namespace ShapeGenerator
