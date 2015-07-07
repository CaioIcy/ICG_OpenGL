#pragma once

#include <GL/glew.h>
#include "engine/StateGame.h"
#include "graphics/Renderable.h"
#include "graphics/Renderer.h"
#include "math/Math.h"
#include "ogldev/ogldev_basic_lighting.h"
#include "ogldev/ogldev_camera.h"
#include "ogldev/ogldev_mesh.h"

namespace ogle {

class ShaderProgram;

/**
* @brief The state used for testing the engine.
*
* For now is just a placeholder, might have different states to test different things later.
*/
class Placeholder : public StateGame {

	public:
		/**
		* @brief The constructor.
		*/
		Placeholder();

		/**
		* @brief The destructor.
		*/
		~Placeholder();

		// Not copyable and not moveable.
		Placeholder(const Placeholder&) = delete;
		Placeholder& operator=(const Placeholder&) = delete;
		Placeholder(Placeholder&&) = delete;
		Placeholder& operator=(Placeholder&&) = delete;

		/**
		* @see StateGame::Load()
		*/
		virtual void Load() override;

		/**
		* @see StateGame::Unload()
		*/
		virtual void Unload() override;

		/**
		* @see StateGame::Update()
		*/
		virtual void Update(const double dt) override;

		/**
		* @see StateGame::Render()
		*/
		virtual void Render() override;

	private:
		Mesh* m_mesh_pls;
		Renderable* m_renderable;
		mat4 m_full_transform;
		ShaderProgram* m_program;
	    BasicLightingTechnique* m_pEffect;
	    DirectionalLight m_directionalLight;
		Camera* m_pGameCamera;

};

} // namespace ogle
