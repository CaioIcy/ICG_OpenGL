#pragma once

#include "graphics/Renderer.h"
#include <vector>

namespace ogle {

/**
* @brief Parent class for other game states.
*/
class StateGame {

	public:
		/**
		* @brief The destructor.
		*/
		virtual ~StateGame();

		/**
		* @brief Loads necessary objects.
		*
		* Pure virtual function. Purpose is to load all things relevant to the state.
		*/
		virtual void Load() = 0;

		/**
		* @brief Unloads necessary objects.
		*
		* Purpose is to unload whatever was previously loaded.
		*/
		virtual void Unload() = 0;

		/**
		* @brief Update all m_game_objects.
		*
		* Pure virtual function. Purpose is to update all the m_game_objects in the vector.
		*
		* @param dt : Delta time. Time elapsed between one frame and the other.
		*/
		virtual void Update(const double dt) = 0;

		/**
		* @brief Renders the state.
		* Pure virtual function.
		*/
		virtual void Render() = 0;

	protected:
		StateGame();

		std::vector<Renderer*> m_renderer;
};

} // namespace ogle
