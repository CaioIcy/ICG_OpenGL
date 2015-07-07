/*

	Copyright 2011 Etay Meiri

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Tutorial 25 - SkyBox
*/

#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "util.h"
#include "pipeline.h"
#include "camera.h"
#include "texture.h"
#include "lighting_technique.h"
#include "glut_backend.h"
#include "mesh.h"
#include "skybox.h"

#define WINDOW_WIDTH  960
#define WINDOW_HEIGHT 540

static float px = 0.0f;
// static float rx = 0.0f;

class Main : public ICallbacks
{
public:

    Main()
    {
        m_pLightingTechnique = NULL;        
        m_pGameCamera = NULL;        
        m_scale = 0.0f;
        m_pSkyBox = NULL;

        m_mesh_spiderman = NULL;
        m_mesh_bike = NULL;
        m_mesh_quad = NULL;
        m_mesh_cube = NULL;

        m_dirLight.AmbientIntensity = 0.2f;
        m_dirLight.DiffuseIntensity = 0.8f;
        m_dirLight.Color = Vector3f(1.0f, 1.0f, 1.0f);
        m_dirLight.Direction = Vector3f(1.0f, -1.0f, 0.0f);
        
        m_persProjInfo.FOV = 60.0f;
        m_persProjInfo.Height = WINDOW_HEIGHT;
        m_persProjInfo.Width = WINDOW_WIDTH;
        m_persProjInfo.zNear = 1.0f;
        m_persProjInfo.zFar = 1000.0f;        
    }
    

    virtual ~Main()
    {
        SAFE_DELETE(m_pLightingTechnique);
        SAFE_DELETE(m_pGameCamera);        
        SAFE_DELETE(m_mesh_spiderman);
        SAFE_DELETE(m_mesh_bike);
        SAFE_DELETE(m_mesh_quad);
        SAFE_DELETE(m_mesh_cube);
        SAFE_DELETE(m_pSkyBox);
    }

    
    bool Init()
    {
        Vector3f Pos(0.0f, 1.0f, -20.0f);
        Vector3f Target(0.0f, 0.0f, 1.0f);
        Vector3f Up(0.0, 1.0f, 0.0f);

        m_pGameCamera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT, Pos, Target, Up);
     
        m_pLightingTechnique = new LightingTechnique();

        if (!m_pLightingTechnique->Init()) {
            printf("Error initializing the lighting technique\n");
            return false;
        }

        m_pLightingTechnique->Enable();
        m_pLightingTechnique->SetDirectionalLight(m_dirLight);
        m_pLightingTechnique->SetTextureUnit(0);
              
        m_mesh_spiderman = new Mesh();
        if (!m_mesh_spiderman->LoadMesh("../Content/spiderman/Spider-Man.obj")) {
            return false;
        }

        m_mesh_bike = new Mesh();
        if (!m_mesh_bike->LoadMesh("../Content/bike/Bicycle.obj")) {
            return false;
        }

        m_mesh_quad = new Mesh();
        if (!m_mesh_quad->LoadMesh("../Content/quad2.obj")) {
            return false;
        }

        m_mesh_cube = new Mesh();
        if (!m_mesh_cube->LoadMesh("../Content/Crate/Killer_Frost_Ice_Block.obj")) {
            return false;
        }
        
        m_pSkyBox = new SkyBox(m_pGameCamera, m_persProjInfo);
        
        if (!m_pSkyBox->Init(".",
                             "../Content/sky_right.jpg",
                             "../Content/sky_left.jpg",
                             "../Content/sky_top.jpg",
                             "../Content/sky_bot.jpg",
                             "../Content/sky_front.jpg",
                             "../Content/sky_back.jpg")) {
            return false;
        }
        
        return true;
    }

    
    void Run()
    {
        GLUTBackendRun(this);
    }

    
    virtual void RenderSceneCB()
    {
        m_pGameCamera->OnRender();
        m_scale = 10.5f;
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_pLightingTechnique->Enable();
       
        const float scale_pls = 5.5f;
        const float y_pls = -20.0f;

        Pipeline p;
        p.SetCamera(m_pGameCamera->GetPos(), m_pGameCamera->GetTarget(), m_pGameCamera->GetUp());
        p.SetPerspectiveProj(m_persProjInfo);
        m_pLightingTechnique->SetDirectionalLight(m_dirLight);
        
        p.Scale(scale_pls * 0.9f, scale_pls * 0.9f, scale_pls * 0.9f);
        p.Rotate(0.0f, m_scale, 0.0f);
        p.WorldPos(-0.7f, y_pls + 0.5f, 9.7f + px);
        m_pLightingTechnique->SetWVP(p.GetWVPTrans());
        m_pLightingTechnique->SetWorldMatrix(p.GetWorldTrans());
        m_mesh_spiderman->Render();

        p.Scale(scale_pls * 1.0f, scale_pls * 1.0f, scale_pls * 1.0f);
        p.Rotate(0.0f, m_scale, 0.0f);
        p.WorldPos(0.0f, y_pls + 0.0f, 10.0f + px);
        m_pLightingTechnique->SetWVP(p.GetWVPTrans());
        m_pLightingTechnique->SetWorldMatrix(p.GetWorldTrans());
        m_mesh_bike->Render();

        p.Scale(scale_pls * 5.0f, scale_pls * 0.0f, scale_pls * 25.0f);
        p.Rotate(0.0f, m_scale, 0.0f);
        p.WorldPos(0.2f, y_pls + -0.5f, 9.2f);
        m_pLightingTechnique->SetWVP(p.GetWVPTrans());
        m_pLightingTechnique->SetWorldMatrix(p.GetWorldTrans());
        m_mesh_quad->Render();

        static float cube_x = -10.0f;
        cube_x += 0.4f;
        if(cube_x >= -5.0f) { cube_x = -15.0f; }

        static float cube_z = -10.0f;
        cube_z += 0.4f;
        if(cube_z >= -5.0f) { cube_z = -15.0f; }

        p.Scale(scale_pls * 1.0f, scale_pls * 1.0f, scale_pls * 1.0f);
        p.Rotate(0.0f, m_scale, 0.0f);
        p.WorldPos(cube_x, y_pls + 10.0f, cube_z);
        m_pLightingTechnique->SetWVP(p.GetWVPTrans());
        m_pLightingTechnique->SetWorldMatrix(p.GetWorldTrans());
        m_mesh_cube->Render();
        
        m_pSkyBox->Render();
      
        glutSwapBuffers();
    }


    virtual void IdleCB()
    {
        RenderSceneCB();
    }
    

    virtual void SpecialKeyboardCB(int Key, int x, int y)
    {
        m_pGameCamera->OnKeyboard(Key);
    }


    virtual void KeyboardCB(unsigned char Key, int x, int y)
    {
        switch (Key) {
            // quit
            case 'q':
                glutLeaveMainLoop();
                break;

            // ambient intensity
            case 'a':
                m_dirLight.AmbientIntensity += 0.05f;
                break;
            case 's':
                m_dirLight.AmbientIntensity -= 0.05f;
                break;

            // diffuse intensity
            case 'z':
                m_dirLight.DiffuseIntensity += 0.05f;
                break;
            case 'x':
                m_dirLight.DiffuseIntensity -= 0.05f;
                break;

            // color
            case 'o':
                m_dirLight.Color.x += 0.05f;
                break;
            case 'p':
                m_dirLight.Color.x -= 0.05f;
                break;

            // px
            case 'u':
                px += 1.0f;
                break;
            case 'j':
                px -= 1.0f;
                break;

            // rotacao
            // case 'h':
            //     rx += 1.0f;
            //     break;
            // case 'k':
            //     rx -= 1.0f;
            //     break;

        }
    
    }


    virtual void PassiveMouseCB(int x, int y)
    {
        m_pGameCamera->OnMouse(x, y);
    }

 private:

    LightingTechnique* m_pLightingTechnique;
    Camera* m_pGameCamera;
    float m_scale;
    DirectionalLight m_dirLight;    
    Mesh* m_mesh_spiderman;    
    Mesh* m_mesh_bike;    
    Mesh* m_mesh_quad;    
    Mesh* m_mesh_cube;    
    SkyBox* m_pSkyBox;
    PersProjInfo m_persProjInfo;
};


int main(int argc, char** argv)
{
    GLUTBackendInit(argc, argv);

    if (!GLUTBackendCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, 32, false, "eskay-boquis")) {
        return 1;
    }

    Main* pApp = new Main();

    if (!pApp->Init()) {
        return 1;
    }

    pApp->Run();

    delete pApp;
 
    return 0;
}
