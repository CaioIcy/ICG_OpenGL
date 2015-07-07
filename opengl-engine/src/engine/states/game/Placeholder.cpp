#include "engine/states/game/Placeholder.h"

#include <cstring>
#include <vector>
#include <iostream>
#include <glm/glm.hpp>

#include "engine/GameObject.h"
#include "graphics/Renderable.h"
#include "input/InputHandler.h"
#include "math/Math.h"
#include "util/Logger.h"
#include "util/Assert.h"
#include "graphics/Shader.h"
#include "graphics/ShaderProgram.h"
#include "graphics/ShapeGenerator.h"
#include "ogldev/ogldev_pipeline.h"

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))
#define aisgl_min(x,y) (x<y?x:y)
#define aisgl_max(x,y) (y>x?y:x)

namespace {
using namespace ogle;

/* the global Assimp scene object */
const  aiScene* scene = NULL;
aiVector3D scene_min, scene_max, scene_center;

float scale_pls = 280.0f;

}




namespace ogle {

Placeholder::Placeholder() :
	StateGame(),
	m_mesh_pls{nullptr},
	m_renderable{nullptr},
	m_full_transform{},
	m_program{nullptr},
	m_pEffect{nullptr},
	m_pGameCamera{nullptr}
{
}

Placeholder::~Placeholder() {
	if(m_renderable != nullptr) {
		delete m_renderable;
	}
	if(m_program != nullptr) {
		delete m_program;
	}
	if(m_mesh_pls != nullptr) {
		delete m_mesh_pls;
	}
}

void Placeholder::Load() {
	log_info() << "Loading STATE placeholder...";

	// constrct

	m_pGameCamera = NULL;
    m_pEffect = NULL;
    m_directionalLight.Color = Vector3f(1.0f, 1.0f, 1.0f);
    m_directionalLight.AmbientIntensity = 1.0f;
    m_directionalLight.DiffuseIntensity = 0.01f;
    m_directionalLight.Direction = Vector3f(1.0f, 0.0f, 1.0f);

    // load
	Vector3f Pos(-15.0f, 4.0f, 10.0f);
    Vector3f Target(0.0f, 0.0f, 1.0f);
    Vector3f Up(0.0, 1.0f, 0.0f);
    m_pGameCamera = new Camera(960, 540, Pos, Target, Up);

    m_pEffect = new BasicLightingTechnique();

    if (!m_pEffect->Init()){
    	log_error() << "caralho";
    }

    m_pEffect->Enable();

    m_pEffect->SetColorTextureUnit(0);

    // const bool loaded = true;
    m_mesh_pls = new Mesh();
    if(m_mesh_pls == nullptr) {
    	log_error() << " VELHO ERA PRA TA CARREGADO";
    }

	const bool loaded = m_mesh_pls->LoadMesh("assets/models/bike/Bicycle.obj");

	if(loaded) {
		log_info() << "CARREGOU ESSA PORRA";
	}
	else {
		log_error() << "altas merda";
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    // glEnable(GL_DEPTH_TEST);
}

void Placeholder::Unload() {
	log_info() << "Unloading STATE placeholder...";

	// if(m_renderable != nullptr) {
	// 	delete m_renderable;
	// }
    delete m_pEffect;
    delete m_pGameCamera;

	aiReleaseImport(scene);
	aiDetachAllLogStreams();
}

void Placeholder::Update(const double dt) {
	// LogAnyInput();
	// log_info() << "Updating STATE placeholder...";
	// update

}

void Placeholder::Render() {

	// log_info() << "Rendering meshpls...";
	m_pGameCamera->OnRender();


	Pipeline p;
	p.Scale(1.f, 1.f, 1.f);
	p.Rotate(0.0f, scale_pls, 0.0f);
	p.WorldPos(0.0f, 0.0f, 10.0f);
	p.SetCamera(m_pGameCamera->GetPos(), m_pGameCamera->GetTarget(), m_pGameCamera->GetUp());
	p.SetPerspectiveProj(60.0f, 960, 540, 1.0f, 100.0f);
	m_pEffect->SetWVP(p.GetWVPTrans());
	m_pEffect->SetWorldMatrix(p.GetWorldTrans());
	m_pEffect->SetDirectionalLight(m_directionalLight);
	m_pEffect->SetEyeWorldPos(m_pGameCamera->GetPos());
	m_pEffect->SetMatSpecularIntensity(0.0f);
	m_pEffect->SetMatSpecularPower(0);
	m_mesh_pls->Render();

	scale_pls += 0.01f;

	m_pGameCamera->Update();
}

} // namespace ogle
