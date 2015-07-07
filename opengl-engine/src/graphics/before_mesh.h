// /*

// 	Copyright 2011 Etay Meiri

//     This program is free software: you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation, either version 3 of the License, or
//     (at your option) any later version.

//     This program is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.

//     You should have received a copy of the GNU General Public License
//     along with this program.  If not, see <http://www.gnu.org/licenses/>.
// */

// #pragma once

// #include <map>
// #include <vector>
// #include <GL/glew.h>

// #include <assimp/cimport.h>
// #include <assimp/Importer.hpp>
// #include <assimp/scene.h>
// #include <assimp/postprocess.h>

// #include "ogldev/ogldev_util.h"
// #include "math/Math.h"
// #include "ogldev/ogldev_texture.h"
// #include "graphics/VertexData.h"
// #include "ShapeData.h"
// #include "Renderable.h"

// struct Vertex
// {
//     vec3 m_pos;
//     vec2 m_tex;
//     vec3 m_normal;

//     Vertex() {}

//     Vertex(const vec3& pos, const vec2& tex, const vec3& normal)
//     {
//         m_pos    = pos;
//         m_tex    = tex;
//         m_normal = normal;
//     }
// };


// class Mesh
// {
// public:
//     Mesh();

//     ~Mesh();

//     Renderable* LoadMesh(const std::string& Filename);

//     void Render();

// private:
//     Renderable* InitFromScene(const aiScene* pScene, const std::string& Filename);
//     Renderable* InitMesh(unsigned int Index, const aiMesh* paiMesh);
//     bool InitMaterials(const aiScene* pScene, const std::string& Filename);
//     void Clear();

//     static constexpr unsigned int INVALID_MATERIAL = 0xFFFFFFFF;

//     struct MeshEntry {
//         MeshEntry();

//         ~MeshEntry();

//         Renderable* Init(const std::vector<VertexData>& Vertices,
//                   const std::vector<unsigned int>& Indices);

//         GLuint VB;
//         GLuint IB;
//         unsigned int NumIndices;
//         unsigned int MaterialIndex;
//     };

//     std::vector<MeshEntry> m_Entries;
//     std::vector<Texture*> m_Textures;
// };

