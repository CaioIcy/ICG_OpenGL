#include "engine/states/game/Placeholder.h"
#include <cstring>
#include <vector>
#include <glm/glm.hpp>
#include "engine/GameObject.h"
#include "input/InputHandler.h"
#include "util/Logger.h"
#include "util/Assert.h"

#include "graphics/VertexArray.h"
#include "graphics/ShaderProgram.h"
#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))

namespace {
using namespace ogle;

double total_elapsed_time = 0.0f;

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

void ComputePositionOffsets(float& fXOffset, float& fYOffset) {
    const float fLoopDuration = 1.0f;
	const float fScale = 3.14159f * 2.0f / fLoopDuration;

	float fCurrTimeThroughLoop = fmodf(total_elapsed_time, fLoopDuration);

	fXOffset = cosf(fCurrTimeThroughLoop * fScale) * 0.5f;
	fYOffset = sinf(fCurrTimeThroughLoop * fScale) * 0.5f;
}

} // namespace























namespace ogle {

Placeholder::Placeholder() :
	m_game_object{nullptr}
{
}

Placeholder::~Placeholder() {
	if(m_game_object != nullptr) {
		delete m_game_object;
	}
}

void Placeholder::Load() {
	log_info() << "Loading STATE placeholder...";

	// Create program
	m_game_object = new GameObject("4_triangle_circle");
}

void Placeholder::Unload() {
	log_info() << "Unloading STATE placeholder...";

	delete m_game_object;
	m_game_object = nullptr;
}

void Placeholder::Update(const double dt) {
	LogAnyInput();

	total_elapsed_time += dt;
	float x_offset = 0.0f;
	float y_offset = 0.0f;
	ComputePositionOffsets(x_offset, y_offset);

	m_game_object->SetXY(x_offset, y_offset);
}

void Placeholder::Render() {
	m_game_object->Render();
}

} // namespace ogle
