//#include "Mesh.h"
//using namespace MikkaiEngine;
//Mesh::Mesh(std::vector<Vertex> vertexs, std::vector<uint> indexes, std::vector<Texture> textures)
//{
//    this->render = render;
//    this->vertices = vertexs;
//    this->indices = indexes;
//    this->textures = textures;
//
//    Init();
//}
//
//Mesh::~Mesh()
//{
//}
//
//void Mesh::Init()
//{
//    render->GenBuffers(VAO, VBO, EBO);
//    render->BindBuffer(VAO, VBO, vertices.size() * sizeof(Vertex), &vertices[0]);
//    render->BindIndexes(EBO, indices.size() * sizeof(unsigned int), &indices[0]);
//
//    render->SetBaseAttribs(0, 3, sizeof(Vertex), (void*)0);
//    render->SetBaseAttribs(1, 3, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
//    render->SetBaseAttribs(2, 2, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
//
//    for (int i = 0; i < textures.size(); i++)
//    {
//        textures[i].type.erase(0, 7);
//    }
//}
//
//void Mesh::Draw()
//{
//    render->DrawMesh(vertices, indices, textures, VAO);
//}
//
//void Mesh::DeInit()
//{
//    vertices.clear();
//    indices.clear();
//    textures.clear();
//    render->UnBind(VAO, VBO, EBO);
//}
