#include "core/Systems.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SDL2/SDL_image.h>
#include <gflags/gflags.h>
#include "util/Assert.h"
#include "util/Logger.h"
#include "util/GlLog.h"

DECLARE_bool(exp);

namespace {
using namespace ogle;

using AtExitFunction = void (*) ();

void RegisterFunctionForExits(AtExitFunction function, const char* description) {
	const int k_registered_atexit = std::atexit(function);
	if(k_registered_atexit != 0){
		log_error() << "Failed to register " << description << " to exit.";
	}

	const int k_registered_at_quick_exit = std::at_quick_exit(function);
	if(k_registered_at_quick_exit != 0){
		log_error() << "Failed to register " << description << " to quick_exit.";
	}
}

} // namespace

namespace ogle {
namespace systems {

void InitializeGlfw() {
	log_debug() << "------- Initializing GLFW -------";

	glfwSetErrorCallback([](int error_code, const char* error_message) {
		log_error() << "GLFW Error [" << error_code << "]: " << error_message;
	});

	{
		int major = 0;
		int minor = 0;
		int rev = 0;
		glfwGetVersion(&major, &minor, &rev);
		log_debug() << "GLFW run-time version: " << major << "." << minor << "." << rev;
	}

	log_debug() << "GLFW compile-time version: " << GLFW_VERSION_MAJOR << "." <<
		GLFW_VERSION_MINOR << "." << GLFW_VERSION_REVISION;
	log_debug() << "GLFW version string: " << glfwGetVersionString();

	const int glfw_initialized = glfwInit();
	ASSERT(glfw_initialized == GL_TRUE, "Couldn't start GLFW.");
	RegisterFunctionForExits(glfwTerminate, "GLFW termination");
}

void InitializeGlew() {
	log_debug() << "------- Initializing GLEW -------";

	if(FLAGS_exp) {
		glewExperimental = GL_TRUE;
		log_debug() << "Using glewExperimental.";
	}
	else {
		glewExperimental = GL_FALSE;
		log_debug() << "Not using glewExperimental.";
	}
	
	GLenum glew_initialized = glewInit();
	ASSERTF(glew_initialized == GLEW_OK, "Couldn't start GLEW. Error: %s", glewGetErrorString(glew_initialized));

    gllog::CheckGlErrors("Resetting error flag due to GLEW invalid enum.");

	log_debug() << "Status: Using GLEW " <<  glewGetString(GLEW_VERSION);

	log_debug() << "OpenGL version: " << glGetString(GL_VERSION);
    log_debug() << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION);
    log_debug() << "Vendor: " << glGetString(GL_VENDOR);
    log_debug() << "Renderer: " << glGetString(GL_RENDERER);
}

void InitializeSdlImage() {
	log_debug() << "------- Initializing SDL2_image -------";

	const Uint32 k_img_flags = IMG_INIT_PNG;
	const bool success = (static_cast<Uint32>(IMG_Init(k_img_flags)) & k_img_flags);
	if(!success) {
		log_error() << "Could not initialize SDL_Image. " << IMG_GetError();
	}

	RegisterFunctionForExits(IMG_Quit, "SDL_image termination");
}

} // namespace systems
} // namespace ogle
