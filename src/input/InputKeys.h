#pragma once

#include <array>

namespace ogle {

/// @todo Implement a customizable input scheme (choose which buttons do what ingame).
enum Buttons {
	A, B, X, Y,
	Select, Start, Guide,
	L1, R1,
	L3, R3,
	LeftAnalogUp, LeftAnalogDown,
	LeftAnalogLeft, LeftAnalogRight,
	RightAnalogUp, RightAnalogDown,
	RightAnalogLeft, RightAnalogRight,
	DpadUp, DpadDown,
	DpadLeft, DpadRight,
	L2,
	R2,

	// Always last, to keep count.
	Count
};

using InputArray = std::array<bool, Buttons::Count>;

} // namespace ogle
