#include <cmath>

namespace ogle {
namespace math {

float ToRadians(const float degrees) {
	return (degrees * 180.0f) / M_PI;
}

float ToDegrees(const float radians) {
	return (radians * M_PI) / 180.0f;
}

} // namespace math
} // namespace ogle
