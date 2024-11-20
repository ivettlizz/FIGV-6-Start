//
// FIGV (Fundamentos de Informática Gráfica y Visualización)
// Master en Desarrollo de Software, Universidad de Granada.
//
// Juan Carlos Torres Cantero
// ETSIIT, Depto. Lenguajes y Sistemas Informáticos, Universidad de Granada, jctorres@ugr.es
//
// Francisco de Asís Conde Rodríguez
// EPS, Depto. Informática, Universidad de Jaén, fconde@ujaen.es
//

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <glad/glad.h>
#include "FigvModel.h"
#include "FigvAuxiliaryFunctions.h"

// FIGV MDL: 4
// FIGV MDL: 4
FigvModel::FigvModel(std::string path, FigvMaterial* material, glm::mat4 transform) 
{
 loadModel(path);
 this->material = material;
 this->transform = transform;
}

// FIGV MDL: 5
void FigvModel::draw(FigvShader shader) {
    // FIGV MDL: 6
    material->applyToShader(shader);
    // FIGV MDL: 8
    shader.set("mModel", transform);
    for(unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].draw();
}

void FigvModel::loadModel(std::string path) {

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path,
                                             aiProcess_Triangulate |
                                             aiProcess_GenSmoothNormals |
                                             aiProcess_FlipUVs);
    // check for errors
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        FigvLog("FigvModel", __LINE__, "Error: Assimp");
        FigvLog("FigvModel", __LINE__, importer.GetErrorString());
        return;
    }

    // process ASSIMP's root node recursively
    processNode(scene->mRootNode, scene);
}

void FigvModel::processNode(aiNode *node, const aiScene *scene) {

    // process each mesh located at the current node
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        // the node object only contains indices to index the actual objects in 
        // the scene. The scene contains all the data, node is just to keep stuff
        // organized (like relations between nodes).
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    // after we've processed all of the meshes (if any) we then recursively 
    // process each of the children nodes
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

FigvMesh FigvModel::processMesh(aiMesh *mesh, const aiScene *scene) {

    // data to fill
    std::vector<FigvVertex> vertices;
    std::vector<unsigned int> indices;

    // walk through each of the mesh's vertices
    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        FigvVertex vertex;
        // we declare a placeholder vector since assimp uses its own vector class 
        // that doesn't directly convert to glm's vec3 class so we transfer the
        // data to this placeholder glm::vec3 first.
        glm::vec3 vector;
        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;
        // normals
        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.normal = vector;
        }
        // texture coordinates
        if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            // a vertex can contain up to 8 different texture coordinates. We 
            // thus make the assumption that we won't use models where a vertex
            // can have multiple texture coordinates so we always take the first
            // set (0).
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.texCoords = vec;
        }
        else
            vertex.texCoords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }
    // now walk through each of the mesh's faces (a face is a mesh its triangle)
    // and retrieve the corresponding vertex indices.
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    // return a mesh object created from the extracted mesh data
    return {vertices, indices};
}
