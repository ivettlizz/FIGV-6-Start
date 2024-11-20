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

#include "FigvEventManager.h"
#include "imgui.h"
#include "FigvScene.h"

FigvEventManager* FigvEventManager::instance = NULL;

FigvEventManager::FigvEventManager() = default;

FigvEventManager* FigvEventManager::getInstance() {

    if (!instance) { instance = new FigvEventManager(); }
    return instance;
}

 // FIGV EVT: 3
int* FigvEventManager::getCameraMovement() {
 return &cameraMovement;
}

void FigvEventManager::processMouseClics(GLFWwindow* window, int button, int action, int mods) {

    ImGuiIO& io = ImGui::GetIO();
    io.AddMouseButtonEvent(button, action);

    if (!io.WantCaptureMouse) {
        if ((button == GLFW_MOUSE_BUTTON_1) && (action == GLFW_PRESS)) {
            glfwGetCursorPos(window, &lastX, &lastY);
            dragging = true;
        } else if ((button == GLFW_MOUSE_BUTTON_1) && (action == GLFW_RELEASE)) {
            dragging = false;
        }
    }
}

void FigvEventManager::processMouseScroll(double yDisplacement) {

    FigvScene::dollyCamera(float(yDisplacement));
}

void FigvEventManager::processCursorPosition(double xPos, double yPos) {

    if (dragging) {
        double xOffset = lastX - xPos;
        double yOffset = lastY - yPos;

        lastX = xPos;
        lastY = yPos;

        // FIGV EVT: 4
        if (cameraMovement == 0) {
            FigvScene::orbitCamera(float(-xOffset), float(-yOffset));
        } else {
            FigvScene::panCamera(float(xOffset), float(yOffset));
        }
    }
}
