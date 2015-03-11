#include "input/InputHandler.h"
#include <GLFW/glfw3.h>
#include <cstring>
#include "util/Assert.h"
#include "util/Logger.h"

namespace ogle {

InputArray InputHandler::m_buttons;
std::queue<KeyInputInfo> InputHandler::m_key_input_queue;
bool InputHandler::m_initialized = false;
int InputHandler::m_buttons_map[JoystickButtons::JOYSTICK_BUTTON_Count];
int InputHandler::m_axes_map[JoystickAxes::JOYSTICK_AXIS_Count];
int InputHandler::xbox_360_button_map[JoystickButtons::JOYSTICK_BUTTON_Count] = {0, 1, 2, 3, 6, 7, 8, 4, 5, 9, 10};
int InputHandler::xbox_360_axes_map[JoystickAxes::JOYSTICK_AXIS_Count] = {0, 1, 3, 4, 6, 7, 2, 5};

void InputHandler::Initialize() {
	ASSERT(m_initialized == false, "Should not be already initialized.");

	// "When GLFW is initialized, detected joysticks are added to to the beginning of the
	// array, starting with GLFW_JOYSTICK_1. Once a joystick is detected, it keeps its 
	// assigned index until it is disconnected, so as joysticks are connected and disconnected,
	// they will become spread out."
	for(int i = GLFW_JOYSTICK_1; i < GLFW_JOYSTICK_LAST; i++) {
		if(glfwJoystickPresent(i) == GL_TRUE) {
			log_warn() << "Joystick [" << i << "] is present. (" << glfwGetJoystickName(i) << ")";
		}
	}

	/// @todo Multiple mappings.
	std::memcpy(&m_buttons_map, &xbox_360_button_map, sizeof m_buttons_map);
	std::memcpy(&m_axes_map, &xbox_360_axes_map, sizeof m_axes_map);

	m_buttons.fill(false);
	m_initialized = true;
}

void InputHandler::Reset() {
	m_buttons.fill(false);
}

bool InputHandler::IsButtonDown(const Buttons button) {
	return m_buttons[button];
}

void InputHandler::PollInput() {
	Reset();
	PollKeyInputQueue();
	PollJoystick();
}

void InputHandler::PollKeyInputQueue() {
	while(!m_key_input_queue.empty()) {
		KeyInputInfo key_input_info = m_key_input_queue.front();
		m_key_input_queue.pop();

		const bool key_press = key_input_info.action == GLFW_PRESS;
		const bool key_repeat = key_input_info.action == GLFW_REPEAT;

		switch(key_input_info.key) {
			case GLFW_KEY_Z: // Input considers repetition.
				m_buttons[Buttons::A] = key_press || key_repeat;
				break;
			case GLFW_KEY_X: // Input DOES NOT consider repetition.
				m_buttons[Buttons::B] = key_press;
				break;
			case GLFW_KEY_C:
				m_buttons[Buttons::X] = key_press;
				break;
			case GLFW_KEY_V:
				m_buttons[Buttons::Y] = key_press;
				break;
			case GLFW_KEY_ENTER:
				m_buttons[Buttons::Start] = key_press;
				break;
			case GLFW_KEY_BACKSPACE:
				m_buttons[Buttons::Select] = key_press;
				break;
			case GLFW_KEY_SLASH:
				m_buttons[Buttons::Guide] = key_press;
				break;
			case GLFW_KEY_KP_1:
				m_buttons[Buttons::L1] = key_press;
				break;
			case GLFW_KEY_KP_3:
				m_buttons[Buttons::R1] = key_press;
				break;
			case GLFW_KEY_O:
				m_buttons[Buttons::L3] = key_press;
				break;
			case GLFW_KEY_P:
				m_buttons[Buttons::R3] = key_press;
				break;
			case GLFW_KEY_W:
				m_buttons[Buttons::LeftAnalogUp] = key_press;
				break;
			case GLFW_KEY_S:
				m_buttons[Buttons::LeftAnalogDown] = key_press;
				break;
			case GLFW_KEY_A:
				m_buttons[Buttons::LeftAnalogLeft] = key_press;
				break;
			case GLFW_KEY_D:
				m_buttons[Buttons::LeftAnalogRight] = key_press;
				break;
			case GLFW_KEY_I:
				m_buttons[Buttons::RightAnalogUp] = key_press;
				break;
			case GLFW_KEY_K:
				m_buttons[Buttons::RightAnalogDown] = key_press;
				break;
			case GLFW_KEY_J:
				m_buttons[Buttons::RightAnalogLeft] = key_press;
				break;
			case GLFW_KEY_L:
				m_buttons[Buttons::RightAnalogRight] = key_press;
				break;
			case GLFW_KEY_KP_8:
				m_buttons[Buttons::DpadUp] = key_press;
				break;
			case GLFW_KEY_KP_5:
				m_buttons[Buttons::DpadDown] = key_press;
				break;
			case GLFW_KEY_KP_4:
				m_buttons[Buttons::DpadLeft] = key_press;
				break;
			case GLFW_KEY_KP_6:
				m_buttons[Buttons::DpadRight] = key_press;
				break;
			case GLFW_KEY_KP_7:
				m_buttons[Buttons::L2] = key_press;
				break;
			case GLFW_KEY_KP_9:
				m_buttons[Buttons::R2] = key_press;
				break;
			default:
				break;
		}

	}
}

void InputHandler::PollJoystick() {
	/// @todo Still polling the first available joystick. Improve this.
	/// @todo Control button repetition in the joystick.

	const float axis_threshold = 0.9f;
	const float trigger_threshold = 0.3f;
	const float dpad_threshold = 0.5f; // Probably unnecessary.

	for(int i = GLFW_JOYSTICK_1; i < GLFW_JOYSTICK_LAST; ++i) {
		if(glfwJoystickPresent(i) == GL_TRUE) {

			int numAxis = 0;
			const float* axes = glfwGetJoystickAxes(i, &numAxis);

			// Left analog.

			if(axes[m_axes_map[JoystickAxes::JOYSTICK_AXIS_LeftAnalogX]] >= axis_threshold) {
				m_buttons[Buttons::LeftAnalogRight] = true;
			}
			if(axes[m_axes_map[JoystickAxes::JOYSTICK_AXIS_LeftAnalogX]] <= -axis_threshold) {
				m_buttons[Buttons::LeftAnalogLeft] = true;
			}
			if(axes[m_axes_map[JoystickAxes::JOYSTICK_AXIS_LeftAnalogY]] >= axis_threshold) {
				m_buttons[Buttons::LeftAnalogDown] = true;
			}
			if(axes[m_axes_map[JoystickAxes::JOYSTICK_AXIS_LeftAnalogY]] <= -axis_threshold) {
				m_buttons[Buttons::LeftAnalogUp] = true;
			}

			// Right analog.

			if(axes[m_axes_map[JoystickAxes::JOYSTICK_AXIS_RightAnalogX]] >= axis_threshold) {
				m_buttons[Buttons::RightAnalogRight] = true;
			}
			if(axes[m_axes_map[JoystickAxes::JOYSTICK_AXIS_RightAnalogX]] <= -axis_threshold) {
				m_buttons[Buttons::RightAnalogLeft] = true;
			}
			if(axes[m_axes_map[JoystickAxes::JOYSTICK_AXIS_RightAnalogY]] >= axis_threshold) {
				m_buttons[Buttons::RightAnalogDown] = true;
			}
			if(axes[m_axes_map[JoystickAxes::JOYSTICK_AXIS_RightAnalogY]] <= -axis_threshold) {
				m_buttons[Buttons::RightAnalogUp] = true;
			}

			// D-Pad.

			if(axes[m_axes_map[JoystickAxes::JOYSTICK_AXIS_DpadX]] >= dpad_threshold) {
				m_buttons[Buttons::DpadRight] = true;
			}
			if(axes[m_axes_map[JoystickAxes::JOYSTICK_AXIS_DpadX]] <= -dpad_threshold) {
				m_buttons[Buttons::DpadLeft] = true;
			}
			if(axes[m_axes_map[JoystickAxes::JOYSTICK_AXIS_DpadY]] >= dpad_threshold) {
				m_buttons[Buttons::DpadDown] = true;
			}
			if(axes[m_axes_map[JoystickAxes::JOYSTICK_AXIS_DpadY]] <= -dpad_threshold) {
				m_buttons[Buttons::DpadUp] = true;
			}

			// Triggers.

			if(axes[m_axes_map[JoystickAxes::JOYSTICK_AXIS_R2]] >= trigger_threshold) {
				m_buttons[Buttons::R2] = true;
			}
			if(axes[m_axes_map[JoystickAxes::JOYSTICK_AXIS_L2]] >= trigger_threshold) {
				m_buttons[Buttons::L2] = true;
			}

			int numButtons = 0;
			const unsigned char* buttons = glfwGetJoystickButtons(i, &numButtons);
			
			if(buttons[m_buttons_map[JoystickButtons::JOYSTICK_BUTTON_A]]) {
				m_buttons[Buttons::A] = true;
			}
			if(buttons[m_buttons_map[JoystickButtons::JOYSTICK_BUTTON_B]]) {
				m_buttons[Buttons::B] = true;
			}
			if(buttons[m_buttons_map[JoystickButtons::JOYSTICK_BUTTON_X]]) {
				m_buttons[Buttons::X] = true;
			}
			if(buttons[m_buttons_map[JoystickButtons::JOYSTICK_BUTTON_Y]]) {
				m_buttons[Buttons::Y] = true;
			}
			if(buttons[m_buttons_map[JoystickButtons::JOYSTICK_BUTTON_Select]]) {
				m_buttons[Buttons::Select] = true;
			}
			if(buttons[m_buttons_map[JoystickButtons::JOYSTICK_BUTTON_Start]]) {
				m_buttons[Buttons::Start] = true;
			}
			if(buttons[m_buttons_map[JoystickButtons::JOYSTICK_BUTTON_Guide]]) {
				m_buttons[Buttons::Guide] = true;
			}
			if(buttons[m_buttons_map[JoystickButtons::JOYSTICK_BUTTON_L1]]) {
				m_buttons[Buttons::L1] = true;
			}
			if(buttons[m_buttons_map[JoystickButtons::JOYSTICK_BUTTON_R1]]) {
				m_buttons[Buttons::R1] = true;
			}
			if(buttons[m_buttons_map[JoystickButtons::JOYSTICK_BUTTON_L3]]) {
				m_buttons[Buttons::L3] = true;
			}
			if(buttons[m_buttons_map[JoystickButtons::JOYSTICK_BUTTON_R3]]) {
				m_buttons[Buttons::R3] = true;
			}

			break;
		}
	}
}

void InputHandler::KeyActionCallback(GLFWwindow* window, int key, int scancode, int action,
		int mods) {
	ASSERT(m_initialized == true, "InputHandler should be initialized first.");

	KeyInputInfo key_input_info = {window, key, scancode, action, mods};
	m_key_input_queue.push(key_input_info);
}

} // namespace ogle
