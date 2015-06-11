#include "engine/Game.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "core/Systems.h"
#include "engine/StateManager.h"
#include "engine/Timer.h"
#include "input/InputHandler.h"
#include "util/Assert.h"
#include "util/Logger.h"
#include "util/GlLog.h"

namespace {
using namespace ogle;

void GetGlVersion(int* out_major, int* out_minor) {
	ASSERT(out_major != nullptr, "Should not be null.");
	ASSERT(out_minor != nullptr, "Should not be null.");

	LogBuffer log_version{log_debug()};
	log_version << "Supported OpenGL versions:\n";

	bool no_supported = true;

	for(int major = 4; major > 0; major--) {
		for(int minor = 5; minor >= 0; minor--) {
			std::string version{"GL_VERSION_"};
			version += std::to_string(major) + "_" + std::to_string(minor);
			if(glewIsSupported(version.c_str())) {
				log_version << major << "." << minor;

				if(no_supported) {
					no_supported = false;
					(*out_major) = major;
					(*out_minor) = minor;
					log_version << " * ";
				}

				log_version << ", ";
			}
		}
	}
}

} // namespace

namespace ogle {

class GameImpl {

	public:
		GameImpl() :
			is_running{true},
			// event_handler{},
			state_manager{},
			window{nullptr}
		{
		}

		bool is_running; /**< Whether the game is currently running/looping or not. */
		StateManager state_manager;
		GLFWwindow* window;
};

Game& Game::Instance() {
	// "C++11 mandates that the initializer for a local static variable is only run once, even
	// in the presence of concurrency. So, assuming you’ve got a modern C++ compiler, this code
	// is thread-safe[...]"
	static auto instance = std::make_unique<Game>(ConstructorTag{});
	return *instance.get();
}

Game::Game(const ConstructorTag& private_tag) :
	m_impl{new GameImpl()}
{
	static_cast<void>(private_tag);
}

Game::~Game() {
	delete m_impl;
}

void Game::Start() {
	Load();
	Run();
	Unload();
}

void Game::Load() {
	// Initialize GLFW.
	systems::InitializeGlfw();

	// Initialize SDL_image.
	systems::InitializeSdlImage();

	// Initialize the input handler.
	InputHandler::Initialize();

	// Creating a valid OpenGL rendering context, so we can initialize GLEW.
	const int screen_width = 960;
	const int screen_height = 540;
	m_impl->window = glfwCreateWindow(screen_width, screen_height, "ザ OGLE", nullptr, nullptr);
	ASSERT(m_impl->window != nullptr, "Could not create GLFW window.");
	glfwMakeContextCurrent(m_impl->window);

	// Initialize GLEW.
	systems::InitializeGlew();

	// Getting newest available GL version.
	const int context_major = 3;
	const int context_minor = 2;
	int gl_major = 0;
	int gl_minor = 0;
	GetGlVersion(&gl_major, &gl_minor);
	ASSERTF(gl_major >= context_major, "Should have OpenGL %d.%d or higher.", context_major, context_minor);
	ASSERTF(!(gl_major == context_major && gl_minor < context_minor), "Should have OpenGL %d.%d or higher.", context_major, context_minor);

	glfwDestroyWindow(m_impl->window);

	// Setting window hints.
	log_debug() << "Setting GLFW context version as: " << context_major << "." << context_minor;
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, context_major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, context_minor);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);

	// Initialize the window.
	m_impl->window = glfwCreateWindow(screen_width, screen_height, "ザ OGLE", nullptr, nullptr);
	ASSERT(m_impl->window != nullptr, "Could not create GLFW window.");
	glfwMakeContextCurrent(m_impl->window);
	glfwSwapInterval(1);
	glfwSetWindowUserPointer(m_impl->window, m_impl->window);

	// Set callbacks.
	glfwSetKeyCallback(m_impl->window, [](GLFWwindow* window, int key, int scancode, int action,
			int mods){
		InputHandler::KeyActionCallback(window, key, scancode, action, mods);
	});

	glfwSetFramebufferSizeCallback(m_impl->window, [](GLFWwindow* window, int width, int height){
		static_cast<void>(window);
		glViewport(0, 0, width, height);
	});

	glEnable(GL_DEPTH_TEST);

	// Load the first state of the game.
	m_impl->state_manager.LoadFirstState();
}

void Game::Unload() {
	ASSERT(m_impl->window != nullptr, "GLFW window is null before destroying.");
	glfwDestroyWindow(m_impl->window);
}

void Game::Update(const double dt) {
	glfwPollEvents();
	InputHandler::PollInput();

	if(glfwWindowShouldClose(m_impl->window)) {
		Stop();
	}

	m_impl->state_manager.CurrentState()->Update(dt);
}

void Game::Render() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_impl->state_manager.CurrentState()->Render();

	if(!gllog::CheckGlErrors("Before swapping buffers for rendering.")) {
		glfwSwapBuffers(m_impl->window);
	}
}

void Game::Run() {
	// Get the first game time.
	const auto k_delta_time = 1.0 / 60.0;
	auto total_game_time = 0.0;
	auto accumulated_time = 0.0;

	Timer timer{};

	// This is the main game loop.
	while(m_impl->is_running) {

		accumulated_time += timer.FrameTime();

		while(accumulated_time >= k_delta_time) {
			Update(k_delta_time);

			accumulated_time -= k_delta_time;
			total_game_time += k_delta_time;
		}

	    Render();

		timer.Reset();
	}
}

void Game::ChangeState(const GameStates game_state) {
	/// @todo Implement the transition between states.
	/// @todo Maybe instead of having a ChangeState in game, place a StateManager reference in
	/// 	each game state.
	m_impl->state_manager.ChangeState(game_state);
}

void Game::Stop() {
	m_impl->is_running = false;
}

} // namespace ogle
