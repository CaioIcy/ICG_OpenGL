#include "engine/states/game/Placeholder.h"

#include <cstring>
#include <vector>
#include <iostream>
#include <glm/glm.hpp>

#include "engine/GameObject.h"
#include "graphics/Renderable.h"
#include "input/InputHandler.h"
#include "math/Math.h"
#include "util/Logger.h"
#include "util/Assert.h"
#include "graphics/Shader.h"
#include "graphics/ShaderProgram.h"
#include "graphics/ShapeGenerator.h"

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))
#define aisgl_min(x,y) (x<y?x:y)
#define aisgl_max(x,y) (y>x?y:x)

namespace {
using namespace ogle;

/* the global Assimp scene object */
const  aiScene* scene = NULL;
aiVector3D scene_min, scene_max, scene_center;

void LogAnyInput() {
	if(InputHandler::IsButtonDown(Buttons::A)) {
		log_warn() << "A";
	}

	if(InputHandler::IsButtonDown(Buttons::B)) {
		log_warn() << "B";
	}

	if(InputHandler::IsButtonDown(Buttons::X)) {
		log_warn() << "X";
	}

	if(InputHandler::IsButtonDown(Buttons::Y)) {
		log_warn() << "Y";
	}

	if(InputHandler::IsButtonDown(Buttons::Select)) {
		log_warn() << "Select";
	}

	if(InputHandler::IsButtonDown(Buttons::Start)) {
		log_warn() << "Start";
	}

	if(InputHandler::IsButtonDown(Buttons::Guide)) {
		log_warn() << "Guide";
	}

	if(InputHandler::IsButtonDown(Buttons::L1)) {
		log_warn() << "L1";
	}

	if(InputHandler::IsButtonDown(Buttons::R1)) {
		log_warn() << "R1";
	}

	if(InputHandler::IsButtonDown(Buttons::L3)) {
		log_warn() << "L3";
	}

	if(InputHandler::IsButtonDown(Buttons::R3)) {
		log_warn() << "R3";
	}

	if(InputHandler::IsButtonDown(Buttons::LeftAnalogUp)) {
		log_warn() << "LeftAnalogUp";
	}

	if(InputHandler::IsButtonDown(Buttons::LeftAnalogDown)) {
		log_warn() << "LeftAnalogDown";
	}

	if(InputHandler::IsButtonDown(Buttons::LeftAnalogLeft)) {
		log_warn() << "LeftAnalogLeft";
	}

	if(InputHandler::IsButtonDown(Buttons::LeftAnalogRight)) {
		log_warn() << "LeftAnalogRight";
	}

	if(InputHandler::IsButtonDown(Buttons::RightAnalogUp)) {
		log_warn() << "RightAnalogUp";
	}

	if(InputHandler::IsButtonDown(Buttons::RightAnalogDown)) {
		log_warn() << "RightAnalogDown";
	}

	if(InputHandler::IsButtonDown(Buttons::RightAnalogLeft)) {
		log_warn() << "RightAnalogLeft";
	}

	if(InputHandler::IsButtonDown(Buttons::RightAnalogRight)) {
		log_warn() << "RightAnalogRight";
	}

	if(InputHandler::IsButtonDown(Buttons::DpadUp)) {
		log_warn() << "DpadUp";
	}

	if(InputHandler::IsButtonDown(Buttons::DpadDown)) {
		log_warn() << "DpadDown";
	}

	if(InputHandler::IsButtonDown(Buttons::DpadLeft)) {
		log_warn() << "DpadLeft";
	}

	if(InputHandler::IsButtonDown(Buttons::DpadRight)) {
		log_warn() << "DpadRight";
	}

	if(InputHandler::IsButtonDown(Buttons::L2)) {
		log_warn() << "L2";
	}

	if(InputHandler::IsButtonDown(Buttons::R2)) {
		log_warn() << "R2";
	}
}

}













namespace ogle {

Placeholder::Placeholder() :
	StateGame(),
	m_renderable{nullptr},
	m_full_transform{},
	m_program{nullptr}
{
	log_warn() << "Placeholder()";
}

Placeholder::~Placeholder() {
	log_warn() << "~Placeholder()";
	if(m_renderable != nullptr) {
		delete m_renderable;
	}
	if(m_program != nullptr) {
		delete m_program;
	}
}

void Placeholder::Load() {
	log_info() << "Loading STATE placeholder...";

	m_renderer.push_back(new Renderer());
	m_renderer.back()->Init();
	m_renderer.push_back(new Renderer());	
	m_renderer.back()->Submit(ShapeGenerator::GenerateCube());

	m_program = new ShaderProgram("cubemvp");
	m_program->Enable();

}

void Placeholder::Unload() {
	log_info() << "Unloading STATE placeholder...";

	// if(m_renderable != nullptr) {
	// 	delete m_renderable;
	// }
	aiReleaseImport(scene);
	aiDetachAllLogStreams();
}

void Placeholder::Update(const double dt) {
	LogAnyInput();
	log_info() << "Updating STATE placeholder...";
	// update
	static float x = 0.0f;
	static float y = 0.0f;

	static float dx = 0.01f;
	dx += 0.00008;
	x += dx;
	y += 0.008f;
	x = fmodf(x, 180.0f);
	y = fmodf(y, 180.0f);

	mat4 translation = glm::translate(mat4(), vec3(0.0f, -1.0f, -1.0f));
	mat4 translation2 = glm::translate(mat4(), vec3(4.0f, 0.5f, -6.0f));
	
	mat4 rotation_x = glm::rotate(mat4(), x, vec3(0.0f, 1.0f, 0.0f));
	mat4 rotation_x2 = glm::rotate(mat4(), x, vec3(0.0f, -1.0f, 0.0f));
	mat4 rotation_y = glm::rotate(mat4(), y, vec3(0.0f, 1.0f, 0.0f));
	mat4 rotation = rotation_x * rotation_y;
	
	const float fov = math::ToRadians(90.0f);
	mat4 projection = glm::perspective(fov, (960.0f/540.0f), 0.1f, 10.0f);

	mat4 translation3 = glm::translate(mat4(), vec3(-1.5f, 0.0f, 0.0f));
	mat4 translation4 = glm::translate(mat4(), vec3(1.5f, 0.0f, 0.0f));
	
	m_full_transform = projection * translation * rotation_x;
	mat4 m_full_transform2 =  projection * translation2 * rotation_x2;
	m_renderer[2]->Push(m_full_transform2 * translation3);
	m_renderer[1]->Push(projection * translation * glm::rotate(mat4(), y, vec3(0.0f, fov, 0.0f))
	* glm::scale(mat4(), vec3(0.2, 0.2, 0.2)));
}

void Placeholder::Render() {
	log_info() << "Rendering Bike...";
	m_program->SetUniformMat4("full_transform_matrix", m_renderer[1]->GetNextTransformation());
	m_renderer[1]->GetMesh()->Render();
	log_info() << "Rendering Cube...";
	m_program->SetUniformMat4("full_transform_matrix", m_renderer[2]->GetNextTransformation());
	m_renderer[2]->Render();
		
}

} // namespace ogle
