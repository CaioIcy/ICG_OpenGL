#include "util/GlLog.h"
#include <GL/glew.h>
#include <sstream>
#include "util/Logger.h"

namespace {

std::string GlErrorToString(GLenum gl_error) {
	std::string gl_error_str{"UNKNOWN_ERROR"};

	switch(gl_error) {
		case GL_NO_ERROR:
			gl_error_str = "GL_NO_ERROR";
			break;
		case GL_INVALID_ENUM:
			gl_error_str = "GL_INVALID_ENUM";
			break;
		case GL_INVALID_VALUE:
			gl_error_str = "GL_INVALID_VALUE";
			break;
		case GL_INVALID_OPERATION:
			gl_error_str = "GL_INVALID_OPERATION";
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			gl_error_str = "GL_INVALID_FRAMEBUFFER_OPERATION";
			break;
		case GL_OUT_OF_MEMORY:
			gl_error_str = "GL_OUT_OF_MEMORY";
			break;
		case GL_STACK_UNDERFLOW:
			gl_error_str = "GL_STACK_UNDERFLOW";
			break;
		case GL_STACK_OVERFLOW:
			gl_error_str = "GL_STACK_OVERFLOW";
			break;
		default:
			break;
	}

	return gl_error_str;
}

} // namespace

namespace ogle {
namespace gllog {

bool CheckGlErrors(const std::string& message) {
	bool has_errors = false;

	GLenum gl_error = glGetError();
	if(gl_error != GL_NO_ERROR) {

		has_errors = true;
		LogBuffer log_gl_errors{log_error()};

		log_gl_errors << message << "\n\t";
		while(gl_error != GL_NO_ERROR) {
			log_gl_errors << "[" << GlErrorToString(gl_error) << "] ";
			gl_error = glGetError();
		}
	}

	return has_errors;
}

} // namespace gllog
} // namespace ogle
