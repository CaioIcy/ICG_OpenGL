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

void GetGlVersion(int* out_major, int* out_minor, bool* out_over_3_1) {
	ASSERT(out_major != nullptr, "Should not be null.");
	ASSERT(out_minor != nullptr, "Should not be null.");
	ASSERT(out_over_3_1 != nullptr, "Should not be null.");
	bool found_supported_version = false;

	std::vector<std::pair<int, int>> experimental_versions;

	{
		LogBuffer log_version{log_debug()};
		log_version << "no experimental:\n";
		for(int major = 4; major > 0; major--) {
			for(int minor = 5; minor >= 0; minor--) {
				std::string version{"GL_VERSION_"};
				version += std::to_string(major) + "_" + std::to_string(minor);
				if(glewIsSupported(version.c_str())) {
					log_version << major << "." << minor << " / ";
					experimental_versions.emplace_back(major, minor);
				}
			}
		}
	}

	systems::InitializeGlew(false);

	int major_no_exp = 0;
	int minor_no_exp = 0;
	for(major_no_exp = 4; major_no_exp > 0; major_no_exp--) {
		for(minor_no_exp = 5; minor_no_exp >= 0; minor_no_exp--) {

			std::string version{"GL_VERSION_"};
			version += std::to_string(major_no_exp) + "_" + std::to_string(minor_no_exp);
			found_supported_version = glewIsSupported(version.c_str());
			if(found_supported_version) {
				break;
			}
		}
		if(found_supported_version) {
			break;
		}
	}
	
	int pairIdx = 0;
	while(!(experimental_versions[pairIdx].first == major_no_exp
			&& experimental_versions[pairIdx].second == minor_no_exp)) {
		pairIdx++;
	}

	(*out_major) = experimental_versions[pairIdx].first;
	(*out_minor) = experimental_versions[pairIdx].second;

	if(((*out_major) == 3 && (*out_minor) == 2) || (*out_major) > 3) {
		(*out_over_3_1) = true;
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
	m_impl->window = glfwCreateWindow(1024, 768, "ザ OGLE", nullptr, nullptr);
	ASSERT(m_impl->window != nullptr, "Could not create GLFW window.");
	glfwMakeContextCurrent(m_impl->window);

	// Initialize GLEW.
	systems::InitializeGlew(true);

	// Getting newest available GL version.
	int gl_major = 0;
	int gl_minor = 0;
	bool version_over_3_1 = false;
	GetGlVersion(&gl_major, &gl_minor, &version_over_3_1);
	log_debug() << "Setting GLFW context version as: " << gl_major << "." << gl_minor;

	glfwDestroyWindow(m_impl->window);

	// Setting window hints.
	if(version_over_3_1) {
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_minor);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);

	// Initialize the window.
	m_impl->window = glfwCreateWindow(1024, 768, "ザ OGLE", nullptr, nullptr);
	ASSERT(m_impl->window != nullptr, "Could not create GLFW window.");
	glfwMakeContextCurrent(m_impl->window);
	glfwSwapInterval(1);

	// Set callbacks.
	glfwSetKeyCallback(m_impl->window, [](GLFWwindow* window, int key, int scancode, int action,
			int mods){
		InputHandler::KeyActionCallback(window, key, scancode, action, mods);
	});

	glfwSetFramebufferSizeCallback(m_impl->window, [](GLFWwindow* window, int width, int height){
		static_cast<void>(window);
		glViewport(0, 0, width, height);
	});

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
    glClear(GL_COLOR_BUFFER_BIT);

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
