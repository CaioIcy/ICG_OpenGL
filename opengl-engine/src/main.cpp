#include <csignal>
// #include <gflags/gflags.h>
#include "engine/Game.h"
#include "util/Logger.h"

// DEFINE_bool(exp, false, "Whether to use glewExperimental or not.");

using namespace ogle;

int main(int argc, char** argv) {
	// gflags::ParseCommandLineFlags(&argc, &argv, true);

	log_info() << "Starting OGLE...";

	// Avoid immediately shutting down when having SIGINT.
	std::signal(SIGINT, [](int signal_code){
		log_warn() << "External interruption signal (" << signal_code << ") caught. Stopping.";
		Game::Instance().Stop();
	});

	Game::Instance().Start();

	log_info() << "Exiting OGLE...";
	return 0;
}
