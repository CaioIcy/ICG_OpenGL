#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/*
-lglfw3 -lrt -lXrandr -lXinerama -lXi -lXcursor -lGL -lm -ldl -lXrender -ldrm -lXdamage -lX11-xcb -lxcb-glx -lxcb-dri2 -lxcb-dri3 -lxcb-present -lxcb-sync -lxshmfence -lXxf86vm -lXfixes -lXext -lX11 -lpthread -lxcb -lXau -lXdmcp -lGLEW
*/

int main(int argc, char** argv) {
	static_cast<void>(argc);
	static_cast<void>(argv);

	const int glfw_initialized = glfwInit();
	if(glfw_initialized != GL_TRUE) {
		std::cerr << "Failed to init GLFW.\n";
		return -1;
	}

	GLFWwindow* window = nullptr;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
	window = glfwCreateWindow(800, 600, "ICG Lista 1", nullptr, nullptr);
	if(window == nullptr) {
		std::cerr << "Failed to create window.\n";
		return -2;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	const int glew_initialized = glewInit();
	if(glew_initialized != GLEW_OK) {
		std::cerr << "Failed to init GLEW.\n";
		return -3;
	}

	while(!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glClearColor(0.2f, 0.2f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
	}

	return 0;
}
