#pragma once

#include <string>

namespace ogle {
namespace gllog {

/**
* Logs all set GL error flags, if any.
*
* @param message : The description of the context from which this method is being called.
*
* @return True if there were any error flags set.
*/
bool CheckGlErrors(const std::string& message);

} // namespace gllog
} // namespace ogle
