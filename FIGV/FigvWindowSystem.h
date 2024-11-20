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

#ifndef FIGV_PRUEBA_1_IMGUI_FIGVWINDOWSYSTEM_H
#define FIGV_PRUEBA_1_IMGUI_FIGVWINDOWSYSTEM_H

#include <GLFW/glfw3.h>

/// Encapsula todo lo relativo a la gestión del sistema de ventanas, que en
/// estas prácticas se implementa mediante la biblioteca **GLFW**
class FigvWindowSystem {

public:
    /// Construye el sistema de ventanas con los parámetros que se quieran para
    /// la ventana principal.
    ///
    /// Realiza los siguientes pasos:
    /// 1. Inicializa **GLFW**
    /// 2. Construye la ventana principal de la aplicación, con el contexto
    ///    gráfico OpenGL.
    /// 3. Inicializa **GLAD** para que las llamadas a funciones OpenGL enlacen
    ///    con la versión de OpenGL 4.0
    ///
    /// @param width  Anchura de la ventana.
    /// @param height Altura de la ventana.
    /// @param name   Nombre que se quiera mostrar en la barra de título
    ///               de la ventana.
    ///
    /// @see FigvWindowSystem::initialize()
    FigvWindowSystem(int width, int height, const char* name);
    
    /// Destruye el sistema de ventanas.
    ///
    /// Realiza dos pasos:
    /// 1. Destruye la ventana principal de la aplicación.
    /// 2. Libera el resto de recursos usados por **GLFW**
    ~FigvWindowSystem();

    /// Método de utilidad para acceder desde fuera de la clase a la ventana
    /// principal de la aplicación.
    GLFWwindow* getAppWindow();
    
    /// Devuelve **verdadero** si se ha pedido el cierre de la ventana principal
    /// (por ejemplo pulsando el botón de cierre gestionado por el SSOO)
    bool getWindowShouldClose();
    
    /// Intercambia los búferes de renderizado.
    ///
    /// @note Las ventanas **GLFW** tienen por defecto un doble búfer. Eso
    ///       significa hay dos búferes de renderizado; un búfer que se
    ///       muestra en la ventana (front buffer) y un búfer oculto donde se
    ///       produce el proceso de rendering del siguiente fotograma (back
    ///       buffer).
    ///       Cuando se ha terminado el rendering de todo el fotograma,
    ///       se intercambian los búferes con este método. El búfer oculto se
    ///       muestra y el que se mostraba hasta ahora se oculta y sobre él se
    ///       renderiza el siguiente fotograma.
    void swapBuffers();

private:

    const char *windowName;
    GLFWwindow* window;
};


#endif //FIGV_PRUEBA_1_IMGUI_FIGVWINDOWSYSTEM_H
