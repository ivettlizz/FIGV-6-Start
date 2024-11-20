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

#ifndef FIGV_PRUEBA_1_IMGUI_FIGVMESH_H
#define FIGV_PRUEBA_1_IMGUI_FIGVMESH_H

#include <glm/vec3.hpp>
#include <string>
#include <glm/vec2.hpp>
#include <vector>

/// Estructura que almacena la información de los vértices que componen una
/// malla.
///
/// @note En OpenGL Core Profile, la información relativa a un vértice puede
///       pasarse en modo entralazado o no entrelazado. En estas prácticas
///       usaremos el **modo entrelazado,** para cada vértice se especifica su
///       posición, normal y coordenadas de textura seguidas, antes de pasar a
///       la información del siguiente vértice.
///       Para facilitar este proceso se usa esta estructura.
struct FigvVertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

/// Malla de triángulos que puede renderizarse. Cada modelo 3D de un objeto
/// tiene asociada una o varias de esta mallas (mesh)
///
/// @see FigvModel
class FigvMesh {

public:
    /// A partir del vector de vértices que define la geometría de la malla y
    /// el vector de índices que define la topología de la malla, construye una
    /// malla lista para renderizar mediante OpenGL.
    ///
    /// Realiza los siguientes pasos:
    ///
    /// 1. Crea los VAO, VBO y EBO de la malla.
    /// 2. Activa el VAO
    /// 3. Copia los vértices en el VBO
    /// 4. Copia los índices en el EBO
    /// 5. Indica cómo encontrar cada nuevo vértice y dentro de este cómo
    ///    encontrar cada uno de sus componentes: posición, normal y coordenadas
    ///    de textura.
    FigvMesh(std::vector<FigvVertex> vertices,
             std::vector<unsigned int> indices);

    /// Se llama cada vez que haya que dibujar esta malla en la escena. Para ello
    /// se activa el VAO de esta malla y se llama a las órdenes de renderizado.
    void draw();

private:
    /// Vector de vértices que definen la geometría de la malla. Es un dato de
    /// entrada y se usa para construir el VBO de OpenGL.
    ///
    /// @see FigvMesh::VBO
    std::vector<FigvVertex> vertices;
    /// Vector de índices que definen la topología de la malla. Es un dato de
    /// entrada y se usa para construir el EBO de OpenGL.
    ///
    /// @see FigvMesh::EBO
    std::vector<unsigned int> indices;
    
    // Para dibujar una malla en OpenGL Core Profile hace falta un VAO (Vertex
    // Array Object) con al menos un VBO (Vertex Buffer Object) y al menos un
    // EBO (Element Buffer Object)
    
    /// Indice que identifica al VAO (Vertex Array Object) que permite renderizar
    /// esta malla.
    unsigned int VAO;
    /// Indice que identifica al VBO (Vertex Buffer Object) que permite renderizar
    /// esta malla. El VBO contiene la geometría, es decir la información de los
    /// vértices que definen la malla.
    unsigned int VBO;
    /// Indice que identifica al EBO (Element Buffer Object) que permite
    /// renderizar esta malla mediante triángulos. El EBO contiene la topología
    /// de la malla, es decir, información sobre cómo se combinan los diferentes
    /// vértices para formar los triángulos que componen la malla. El EBO contiene
    /// un array de índices que referencian a los distintos vértices de la malla.
    unsigned int EBO;
};

#endif //FIGV_PRUEBA_1_IMGUI_FIGVMESH_H
