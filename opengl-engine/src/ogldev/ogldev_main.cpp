// #include <iostream>
// #include <math.h>
// #include <GL/glew.h>

// #include "pipeline.h"
// #include "ogldev_camera.h"
// #include "texture.h"
// #include "ogldev_basic_lighting.h"
// #include "ogldev_glfw_backend.h"
// #include "ogldev_util.h"
// #include "mesh.h"
// #include <GLFW/glfw3.h>

// static constexpr int WINDOW_WIDTH  = 960;
// static constexpr int WINDOW_HEIGHT = 540;

// class Main : public ICallbacks
// {
// public:

//     Main()
//     {
//         m_pGameCamera = NULL;
//         m_pEffect = NULL;
//         m_scale = 0.0f;
//         m_directionalLight.Color = Vector3f(1.0f, 1.0f, 1.0f);
//         m_directionalLight.AmbientIntensity = 1.0f;
//         m_directionalLight.DiffuseIntensity = 0.01f;
//         m_directionalLight.Direction = Vector3f(1.0f, 0.0f, 1.0f);
//     }

//     virtual ~Main()
//     {
//         delete m_pEffect;
//         delete m_pGameCamera;
//         delete m_mesh_cycle;
//         delete m_mesh_spiderman;
//         delete m_mesh_quad;
//     }

//     bool Init()
//     {
//         Vector3f Pos(-15.0f, 4.0f, 10.0f);
//         Vector3f Target(0.0f, 0.0f, 1.0f);
//         Vector3f Up(0.0, 1.0f, 0.0f);
//         m_pGameCamera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT, Pos, Target, Up);

//         m_pEffect = new BasicLightingTechnique();

//         if (!m_pEffect->Init()){
//             printf("Error initializing the lighting technique\n");
//             return false;
//         }

//         m_pEffect->Enable();

//         m_pEffect->SetColorTextureUnit(0);

//         m_mesh_cycle = new Mesh();
//         m_mesh_spiderman = new Mesh();
//         m_mesh_quad = new Mesh();
//         m_mesh_block = new Mesh();

//         // return m_mesh_cycle->LoadMesh("../Content/phoenix_ugv.md2");
//         const bool loaded_meshes =
//             m_mesh_cycle->LoadMesh("../Content/Bicycle/Bicycle.obj") &&
//             m_mesh_spiderman->LoadMesh("../Content/spiderman/Spider-Man.obj") &&
//             m_mesh_quad->LoadMesh("../Content/quad2.obj") &&
//             m_mesh_block->LoadMesh("../Content/Killer_Frost_Ice_Block/Killer_Frost_Ice_Block.obj");
//             // m_mesh_spiderman->LoadMesh("../Content/guard/boblampclean.md5mesh");
//         return loaded_meshes;
//     }

//     void Run()
//     {
//         GLFWBackendRun(this);
//     }

//     virtual void RenderSceneCB() override
//     {
//         m_pGameCamera->OnRender();

//         glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

//         m_scale = 286.5f;
//         // std::cout << "scale: " << m_scale << std::endl;

//         Pipeline p;
//         p.Scale(1.f, 1.f, 1.f);
//         p.Rotate(0.0f, m_scale, 0.0f);
//         p.WorldPos(0.0f, 0.0f, 10.0f);
//         p.SetCamera(m_pGameCamera->GetPos(), m_pGameCamera->GetTarget(), m_pGameCamera->GetUp());
//         p.SetPerspectiveProj(60.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 1.0f, 100.0f);
//         m_pEffect->SetWVP(p.GetWVPTrans());
//         m_pEffect->SetWorldMatrix(p.GetWorldTrans());
//         m_pEffect->SetDirectionalLight(m_directionalLight);
//         m_pEffect->SetEyeWorldPos(m_pGameCamera->GetPos());
//         m_pEffect->SetMatSpecularIntensity(0.0f);
//         m_pEffect->SetMatSpecularPower(0);
//         m_mesh_cycle->Render();

//         p.Scale(0.9f, 0.9f, 0.9f);
//         p.WorldPos(-0.7f, 0.5f, 9.7f);
//         m_pEffect->SetWVP(p.GetWVPTrans());
//         m_pEffect->SetWorldMatrix(p.GetWorldTrans()); 
//         m_mesh_spiderman->Render();

//         static float posiX = 0.0;
//         posiX += 0.1;

//         p.Scale(2.9f, 2.9f, 0.9f);
//         p.WorldPos(5.0f, 2.5f, 9.7f);
//         p.Rotate(0.0f, posiX, 0.0f);
//         m_pEffect->SetWVP(p.GetWVPTrans());
//         m_pEffect->SetWorldMatrix(p.GetWorldTrans()); 
//         m_mesh_block->Render();

//         p.Scale(5.0f, 0.0f, 25.0f);
//         p.Rotate(0.0f, m_scale, 0.0f);
//         p.WorldPos(0.2f, -0.5f, 9.2f);
//         m_pEffect->SetWVP(p.GetWVPTrans());
//         m_pEffect->SetWorldMatrix(p.GetWorldTrans()); 
//         m_mesh_quad->Render();

//         GLFWBackendSwapBuffers();

//         m_pGameCamera->Update();
//     }


//     virtual void KeyboardCB(OGLDEV_KEY OgldevKey) override
//     {
//         if(OgldevKey == OGLDEV_KEY_Q) {
//             glfwSetWindowShouldClose(Window(), GL_TRUE);
//         }
//         else if(OgldevKey == OGLDEV_KEY_A) {
//             m_directionalLight.AmbientIntensity += 0.05f;
//         }
//         else if(OgldevKey == OGLDEV_KEY_S) {
//             m_directionalLight.AmbientIntensity -= 0.05f;
//         }
//         //m_pGameCamera->OnKeyboard(OgldevKey);
//     }


//     virtual void PassiveMouseCB(int x, int y) override
//     {
//         //m_pGameCamera->OnMouse(x, y);
//     }

// private:

//     GLuint m_VBO;
//     GLuint m_IBO;
//     BasicLightingTechnique* m_pEffect;
//     Mesh* m_mesh_cycle;
//     Mesh* m_mesh_spiderman;
//     Mesh* m_mesh_quad;
//     Mesh* m_mesh_block;
//     Camera* m_pGameCamera;
//     float m_scale;
//     DirectionalLight m_directionalLight;
// };


// int main(int argc, char** argv)
// {
//     GLFWBackendInit(argc, argv, true, false);

//     //bool GLFWBackendCreateWindow(unsigned int Width, unsigned int Height, bool isFullScreen, const char* pTitle);
//     if (!GLFWBackendCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, false, "Bicicleta + Spiderman = OP")) {
//         return 1;
//     }

//     Main* pApp = new Main();

//     if (!pApp->Init()) {
//         return 1;
//     }

//     pApp->Run();

//     delete pApp;

//     return 0;
// }
