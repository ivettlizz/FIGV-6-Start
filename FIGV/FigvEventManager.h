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

#ifndef FIGV_PRUEBA_1_IMGUI_FIGVEVENTMANAGER_H
#define FIGV_PRUEBA_1_IMGUI_FIGVEVENTMANAGER_H

#include <GLFW/glfw3.h>

/// Encapsula la gestión de los eventos de ratón. Se separa de la detección de
/// esos eventos que se se realiza en el archivo main.cpp
///
/// Se implementa como un **singleton** para asegurar que en la aplicación solo
/// hay un gestor de eventos y para facilitar su acceso desde cualquier módulo
/// que lo necesite.
class FigvEventManager {

public:

    static FigvEventManager *getInstance();

    ~FigvEventManager();
    
     // FIGV EVT: 2
    int *getCameraMovement();
    
    /// Gestiona los eventos de pulsación de un botón del ratón.
    void processMouseClics(GLFWwindow* window, int button, int action, int mods);
    /// Gestiona los eventos de movimiento de la rueda del ratón.
    void processMouseScroll(double yDisplacement);
    /// Gestiona los movimientos del ratón.
    void processCursorPosition(double xPos, double yPos);

private:
    /// El constructor es privado para impedir que pueda invocarse para construir
    /// otras instancias además del singleton.
    FigvEventManager();

    /// Ultima coordenada X esn la que el ratón estuvo pulsado. Permite averiguar
    /// el desplazamiento en X que se haya producido desde ese momento.
    double lastX = 0.0;
    /// Ultima coordenada Y en la que el ratón estuvo pulsado. Permite averiguar
    /// el desplazamiento en Y que se haya producido desde ese momento.
    double lastY = 0.0;
    /// Bandera, para poder distinguir si el ratón se está moviendo sin pulsar
    /// (`false`) o arrastrando mientras está pulsado (`true`)
    bool dragging = false;
    
     // FIGV EVT: 1
    int cameraMovement = 0;

    /// Unica instancia de la clase. Es de clase (static) para que pueda accederse
    /// con facilidad desde cualquier otro módulo.
    static FigvEventManager *instance;
};


#endif //FIGV_PRUEBA_1_IMGUI_FIGVEVENTMANAGER_H
