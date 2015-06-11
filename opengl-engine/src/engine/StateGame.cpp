#include "engine/StateGame.h"
										#include "util/Logger.h"

namespace ogle {

StateGame::StateGame() :
	m_renderer{nullptr}
{
										log_warn() << "StateGame()";
}

StateGame::~StateGame() {
										log_warn() << "~StateGame()";
	m_renderer.clear();
}

} // namespace ogle
