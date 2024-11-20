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

#pragma once

#ifndef FIGV_PRUEBA_1_IMGUI_FIGVMODEL_H
#define FIGV_PRUEBA_1_IMGUI_FIGVMODEL_H

#include <string>
#include <vector>
#include <assimp/scene.h>
#include "FigvMesh.h"
#include "FigvMaterial.h"

/// Modelo 3D. Representa a un objeto que se quiere visualizar en la escena.
/// Está formado por una o varias mallas de triángulos (meshes)
///
/// @note Para la carga y procesamiento de los objetos desde archivos en disco
///       se usa la biblioteca **assimp.**
///
/// @see FigvMesh
class FigvModel {

public:
    // FIGV MDL: 2
    /// Construye un nuevo modelo de objeto 3D a partir de las información
    /// guardada en el archivo cuyo `path` se pasa como parámetro.
    ///
    /// @note Usa la biblioteca **assimp** para realizar la lectura y el parsing
    ///       de la información sobre las mallas que forman al modelo y que está
    ///       contenida en el archivo.
    FigvModel(std::string path, FigvMaterial* material, glm::mat4 transform);

    // FIGV MDL: 3
    /// Recorre cada una de las mallas que forman este modelo y les pide que
    /// se renderizen.
    void draw(FigvShader shader);

private:
    /// Mallas que componen este modelo de objeto 3D.
    ///
    /// @note Un modelo 3D puede estar compuesto de más de una malla.
    std::vector<FigvMesh> meshes;
    
    // FIGV MDL: 1
    FigvMaterial* material;
     // FIGV MDL: 7
    glm::mat4 transform;
    /// Método de utlidad basado en la bibloteca **assimp** que lee la información
    /// contenida en el archivo cuya ruta se pasa en `path` y la procesa
    /// recursivamente para reconstruir las mallas que conforman el modelo.
    ///
    /// @note Constuye un objeto de clase `aiScene` definida en la biblioteca
    ///       **assimp** que contiene toda la información relativa al modelo
    ///       leído del disco. Este objeto se pasa a los métodos auxiliares que
    ///       procesan nodos y mallas para su funcionamiento.
    void loadModel(std::string path);
    /// Método de utilidad basado en **assimp** que se llama cada vez que hay
    /// que procesar uno de los nodos del modelo. En cada nodo hay una o varias
    /// mallas.
    void processNode(aiNode *node, const aiScene *scene);
    /// Método de utilidad basado en **assimp** que se llama para procesar cada
    /// una de las mallas que conforman un nodo del modelo. Para cada malla que
    /// se procesa se obtiene su geometría y su topología y con ellas se
    /// construye un objeto FigvMesh.
    ///
    /// @see FigvMesh
    FigvMesh processMesh(aiMesh *mesh, const aiScene *scene);
};


#endif //FIGV_PRUEBA_1_IMGUI_FIGVMODEL_H
