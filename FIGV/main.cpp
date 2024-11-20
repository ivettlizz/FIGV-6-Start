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

#include "FigvWindowSystem.h"
#include "FigvScene.h"
#include "FigvAuxiliaryFunctions.h"
#include "FigvUserInterface.h"
#include "FigvRenderer.h"
#include "FigvEventManager.h"

// Callbacks que se registran para ser llamados cuando ocurran eventos en la
// ventana principal de la aplicación.
// Deben ser funciones (no métodos de clases). Todos ellos delegan en otras
// clases de la aplicación para realizar su función.

void scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
    FigvEventManager::getInstance()->processMouseScroll(yOffset);
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    FigvEventManager::getInstance()->processMouseClics(window, button, action, mods);
}

void cursorPosCallback(GLFWwindow* window, double xPos, double yPos) {
    FigvEventManager::getInstance()->processCursorPosition(xPos, yPos);
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    FigvScene::setFrameSize(width, height);
}

/// @file

/// Función principal de la aplicación. Implementa el ciclo de eventos que
/// está en el corazón de cualquier aplicación gráfica interactiva.
/// @note Salvo en casos muy especiales, no es necesario cambiar nada de
///       esta función.

int main() {
    FigvLog("main", __LINE__, "Starting application");

    const unsigned int WINDOW_WIDTH = 1600;
    const unsigned int WINDOW_HEIGHT = 900;
    const char* windowName = "FIGV";

    // - El primer paso en una aplicación gráfica interactiva es siempre
    //   construir la interfaz y registrar los callbacks que serán llamados
    //   cuando ocurran los eventos de interacción.
    
    FigvWindowSystem* windowSystem = new FigvWindowSystem(WINDOW_WIDTH, WINDOW_HEIGHT, windowName);

    auto* userInterface = new FigvUserInterface(windowSystem->getAppWindow());

    glfwSetScrollCallback(windowSystem->getAppWindow(), scrollCallback);
    glfwSetMouseButtonCallback(windowSystem->getAppWindow(), mouseButtonCallback);
    glfwSetCursorPosCallback(windowSystem->getAppWindow(), cursorPosCallback);
    glfwSetFramebufferSizeCallback(windowSystem->getAppWindow(), framebufferSizeCallback);

    // - El segundo paso es iniciar el ciclo de eventos. Los eventos de la
    //   aplicación se colocan en una cola a la espera de ser procesados.
    //   en cada paso por el ciclo de eventos se atienden los eventos que haya
    //   pendientes y se redibuja la escena.
    //   El ciclo termina cuando se cierra la ventana de la aplicación.
    
    while (!windowSystem->getWindowShouldClose()) {

        glfwPollEvents();

        userInterface->prepareInterfaceObjects();
        userInterface->preRenderActions();

        FigvRenderer::renderScene();

        userInterface->afterRenderActions();
        windowSystem->swapBuffers();
    }

    // - Cuando finaliza el ciclo de eventos, hay que destruir los recursos
    //   utilizados y salir de la aplicación.
    
    delete(userInterface);
    delete(windowSystem);

    FigvLog("main", __LINE__, "Ending application");

    return 0;
}
