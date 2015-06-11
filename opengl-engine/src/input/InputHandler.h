#pragma once

#include <queue>
#include "input/InputKeys.h"

class GLFWwindow;

namespace ogle {

typedef struct {
	GLFWwindow* window;
	int key;
	int scancode;
	int action;
	int mods;
} KeyInputInfo;

enum JoystickButtons {
	JOYSTICK_BUTTON_A, JOYSTICK_BUTTON_B, JOYSTICK_BUTTON_X, JOYSTICK_BUTTON_Y,
	JOYSTICK_BUTTON_Select, JOYSTICK_BUTTON_Start, JOYSTICK_BUTTON_Guide,
	JOYSTICK_BUTTON_L1, JOYSTICK_BUTTON_R1,
	JOYSTICK_BUTTON_L3, JOYSTICK_BUTTON_R3,

	// Always last, to keep count.
	JOYSTICK_BUTTON_Count
};

enum JoystickAxes {
	JOYSTICK_AXIS_LeftAnalogX,
	JOYSTICK_AXIS_LeftAnalogY,
	JOYSTICK_AXIS_RightAnalogX,
	JOYSTICK_AXIS_RightAnalogY,
	JOYSTICK_AXIS_DpadX,
	JOYSTICK_AXIS_DpadY,
	JOYSTICK_AXIS_L2,
	JOYSTICK_AXIS_R2,

	// Always last, to keep count.
	JOYSTICK_AXIS_Count
};

class InputHandler {

	public:
		static void Initialize();
		static void KeyActionCallback(GLFWwindow* window, int key, int scancode, int action,
			int mods);
		static void PollInput();
		static bool IsButtonDown(const Buttons button);

	private:
		InputHandler();
		
		static void Reset();
		static void PollKeyInputQueue();
		static void PollJoystick();

		static std::queue<KeyInputInfo> m_key_input_queue;
		static InputArray m_buttons;
		static bool m_initialized;
		static int m_buttons_map[JoystickButtons::JOYSTICK_BUTTON_Count];
		static int m_axes_map[JoystickAxes::JOYSTICK_AXIS_Count];

		static int xbox_360_button_map[JoystickButtons::JOYSTICK_BUTTON_Count];
		static int xbox_360_axes_map[JoystickAxes::JOYSTICK_AXIS_Count];

		static int ps4_button_map[JoystickButtons::JOYSTICK_BUTTON_Count];
		static int ps4_axes_map[JoystickAxes::JOYSTICK_AXIS_Count];
};

} // namespace ogle
