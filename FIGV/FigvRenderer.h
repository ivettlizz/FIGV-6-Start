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

#ifndef FIGV_PRUEBA_1_IMGUI_FIGVRENDERER_H
#define FIGV_PRUEBA_1_IMGUI_FIGVRENDERER_H

#include <glm/vec4.hpp>
#include "FigvShader.h"

/// Encapsula todo el proceso de rendering de una escena. Prepara el contexto
/// gráfico de OpenGL para renderizar un nuevo frame. El proceso incluye entre
/// otras tareas borrar los buffers y activar el estado adecuado para el
/// contexto gráfico.
///
/// Se implementa como un **singleton** para asegurar que en la aplicación solo
/// hay un renderer y para facilitar su acceso desde cualquier módulo que lo
/// necesite.
class FigvRenderer {

public:
    ~FigvRenderer();

    static FigvRenderer *getInstance();

    float* getBackgroundColor();
    
    /// Este es el método principal de esta clase. Es el único que hay que llamar
    /// desde el ciclo de eventos. Se encarga de preparar el contexto gráfico
    /// para el renderizado de un nuevo frame y delega en la clase FigvScene para
    /// realizar el renderizado de cada objeto a mostrar.
    ///
    /// Este método se incluye para facilitar la sintaxis de la llamada al método
    /// render()
    static void renderScene();

private:
    /// El constructor es privado para impedir que pueda invocarse para construir
    /// otras instancias además del singleton.
    /// Construye e Inicializa el renderer.
    ///
    /// Realiza dos acciones:
    /// 1. Asigna un color de fondo.
    /// 2. Construye el shader program con el que se dibujan los objetos.
    FigvRenderer();
    
    /// Método que realmente realiza el rendering de la escena.
    void render();

    /// Unica instancia de la clase. Es de clase (static) para que pueda accederse
    /// con facilidad desde cualquier otro módulo.
    static FigvRenderer *instance;

    /// Color con el que e dibuja el fondo del contexto gráfico OpenGL
    glm::vec4 background;

    /// Shader program activo. Es el que se usa para controlar cómo la GPU
    /// dibuja los objetos de la escena.
    FigvShader* shader;
};


#endif //FIGV_PRUEBA_1_IMGUI_FIGVRENDERER_H
