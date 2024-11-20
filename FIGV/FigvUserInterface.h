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

#ifndef FIGV_PRUEBA_1_IMGUI_FIGVUSERINTERFACE_H
#define FIGV_PRUEBA_1_IMGUI_FIGVUSERINTERFACE_H

#include <GLFW/glfw3.h>

/// Encapsula todo lo relativo a la gestión de la paleta de controles que forma
/// parte de la interfaz de usuario. En estas prácticas se implementa mediante
/// la biblioteca **ImGui**
class FigvUserInterface {

public:

    /// Construye el gestor de la interfaz de usuario pasándole la ventana
    /// principal de la aplicación, con la que va a estar asociado.
    ///
    /// @param associatedWindow Ventana principal de la aplicación con la que
    ///                         trabajará el gestor de ventanas que se
    ///                         construye
    ///
    /// Realiza los siguientes pasos:
    /// 1. Construye el contexto de **ImGui**. Se usa para dibujar los widgets
    ///    de la interfaz.
    /// 2. Establece el modo claro u oscuro en función del valor del atributo
    ///    FigvUserInterface::darkMode de la clase.
    /// 3. Usa el back-end apropiado para el gestor de ventanas y la biblioteca
    ///    gráfica elegidas (en este caso **GLFW** y **OpenGL**.
    ///
    ///  @note **ImGui** puede usarse con diferentes gestores de ventanas y
    ///        diferentes bibliotecas gráficas.
    explicit FigvUserInterface(GLFWwindow* associatedWindow);
    ~FigvUserInterface();

    // Los siguientes métodos encapsulan las llamadas a ImGui necesarias antes
    // y después de renderizar la escena, y las llamadas previas a construir los
    // elementos de la interfaz de usuario.
    // No deberían modificarse en ninguna aplicación gráfica que utilice esta
    // clase.
    void preRenderActions();
    void afterRenderActions();
    void prepareInterfaceObjects();

private:
    /// Ventaja GLFW con la que trabaja esta interfaz de usuario. Es su ventana
    /// asociada.
    GLFWwindow* associatedWindow;
    /// Cadena para almacenar la versión de OpenGL / GLSL que se usará en las
    /// llamadas a funciones gráficas y para compilar los shaders.
    const char* glsl_version;
    
    /// Bandera que se usa para establecer si se quiere dibujar **ImGui** en
    /// modo oscuro (`true`) o claro (`false`)
    bool darkMode;

    /// Este es el único método que hay que redeclarar. Es donde se describe
    /// cómo va a ser la interfaz de usuario de la aplicación. Incluye llamadas
    /// para construir los controles que van en la paleta de la aplicación.
    ///
    /// La primera línea debe ser una llamada a `ImGui::Begin("[nombre_paleta]");`
    /// y la última una llamada a `ImGui::End();` Entra ambas se escriben las
    /// llamadas que crean los distintos elementos de la paleta.
    ///
    /// Al final de este método hay una línea comentada. Si se descomenta se
    /// construye una segunda paleta, donde se demuestran todos los controles
    /// que pueden usarse con ImGui. El código que construye esa paleta se
    /// encuentra en el archvo `imgui_demo.cpp` estudia este archivo para ver
    /// la sintaxis y ejemplos de uso de los diferentes controles.
    void preparePalettes();
};


#endif //FIGV_PRUEBA_1_IMGUI_FIGVUSERINTERFACE_H
