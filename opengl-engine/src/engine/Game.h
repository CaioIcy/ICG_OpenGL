#pragma once

namespace ogle {

enum GameStates : int;

/**
* @brief Main structure class for the game.
*
* Contains all the necessary functionalities to loop and update the game.
*
* @note Is a Singleton.
*/
class Game {

	private:
		struct ConstructorTag {}; /**< Private tag needed to use the constructor. */

	public:
		/**
		* @brief Singleton implementation for Game.
		*
		* @return The instance for a Game.
		*/
		static Game& Instance();

		/**
		* @brief The constructor.
		*
		* Since the std::make_unique in Game::Instance() can't access a private constructor,
		* we make this constructor public but need a ConstructorTag parameter. ConstructorTag
		* is an empty struct only accessible by this class, since it is private. This way the
		* constructor can only actually be used in a private setting.
		*/
		explicit Game(const ConstructorTag& private_tag);

		~Game();

		// Not copyable and not moveable.
		Game(const Game&) = delete;
		Game& operator=(const Game&) = delete;
		Game(Game&&) = delete;
		Game& operator=(Game&&) = delete;

		/**
		* @brief Loads, runs, and eventually unloads the game.
		*/
		void Start();
		
		/**
		* @brief Stops execution and closes the game.
		*/
		void Stop();

		/**
		* @brief Sets the current game state.
		*
		* @see StateGame::load()
		* @see StateGame::unload()
		*
		* @param game_state : The state you want to be changed into.
		*/
		void ChangeState(const GameStates game_state);

	private:
		void Load();
		void Unload();
		void Update(const double dt);
		void Render();

		/**
		* @brief The main game loop.
		*
		* Orders the game structure, such as inputs, updates, and rendering.
		*/
		void Run();

		class GameImpl* m_impl; /**< PIMPL idiom. */
};

} // namespace ogle
