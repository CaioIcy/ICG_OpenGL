#include <csignal>
#include "engine/Game.h"
#include "util/Logger.h"

using namespace ogle;

int main(int argc, char** argv) {

	// Unused for now, so avoiding compiler warnings.
	(static_cast<void>(argc));
	(static_cast<void>(argv));

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
