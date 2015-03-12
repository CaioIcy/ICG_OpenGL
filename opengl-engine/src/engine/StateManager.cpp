#include "engine/StateManager.h"
#include "util/Assert.h"
// Begin Game States includes
#include "engine/states/game/Placeholder.h"
// End Game States includes

namespace ogle {

StateManager::StateManager() :
	m_current_state{nullptr},
	m_game_states{}
{
	InitializeStates();
}

StateManager::~StateManager() {
	if(m_current_state != nullptr) {
		m_current_state->Unload();
	}
}

void StateManager::ChangeState(const GameStates game_state) {
	m_current_state->Unload();
	m_current_state = m_game_states.at(game_state).get();
	m_current_state->Load();
}

void StateManager::InitializeStates() {
#define ADD_STATE(GAMESTATE_ENUM, GStateClass) m_game_states.emplace((GAMESTATE_ENUM), \
	(std::make_unique<GStateClass>()))

	// Add all the states in the game here.
	ADD_STATE(PLACEHOLDER, Placeholder);

#undef ADD_STATE
}

void StateManager::LoadFirstState() {
	m_current_state = m_game_states.at(GameStates::PLACEHOLDER).get();
	ASSERT(m_current_state != nullptr, "Some game state should be loaded.");
	m_current_state->Load();
}

StateGame* StateManager::CurrentState() const {
	return m_current_state;
}

} // namespace ogle
