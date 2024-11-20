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

#include <glm/gtc/epsilon.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include "FigvCamera.h"
#include "FigvAuxiliaryFunctions.h"

FigvCamera::FigvCamera() {

    this->position = glm::vec3(0.0f, 5.0f, 10.0f);
    this->lookAt = glm::vec3(0.0f, 0.0f, 0.0f);
    // El valor inicial no es relevante. En el momento en que se construye la
    // ventana principal se actualiza
    this->aspect = 1.0;
    this->fovX = 40.0f;
    this->zNear = 1.0f;
    this->zFar = 50.0f;

    calculateVectors();
}

void FigvCamera::calculateVectors() {

    vN = glm::normalize(position - lookAt);

    if (glm::all(glm::epsilonEqual(vN, glm::vec3(0.0f, -1.0f, 0.0f), 0.000001f))) {
        vV = glm::vec3(0.0f, 0.0f, 1.0f);
    } else if(glm::all(glm::epsilonEqual(vN, glm::vec3(0.0f, 1.0f, 0.0f), 0.000001f))) {
        vV = glm::vec3(0.0f, 0.0f, -1.0f);
    } else {
        vV = glm::vec3(0.0f, 1.0f, 0.0f);
    }

    vU = glm::normalize(glm::cross(vV, vN));

    vV = glm::normalize(glm::cross(vN, vU));
}

void FigvCamera::orbit(float movementX, float movementY) {

    glm::mat4 TR = glm::transpose(glm::translate(glm::mat4(1.0f), lookAt));
    glm::mat4 TRI = glm::transpose(glm::translate(glm::mat4(1.0f), -lookAt));
    glm::mat4 R;
    glm::mat4 T;

    R = glm::rotate(glm::mat4(1.0f), glm::radians(movementY), vU);
    T = TR * R;
    T = T * TRI;
    vV = glm::normalize(R * glm::vec4(vV, 0.0f));
    vN = glm::normalize(R * glm::vec4(vN, 0.0f));
    position = T *glm::vec4(position, 1.0f);

    R = glm::transpose((glm::rotate(glm::mat4(1.0f), glm::radians(-movementX), glm::vec3(0.0, 1.0, 0.0))));
    T = TR * R;
    T = T * TRI;
    vU = glm::normalize(T * glm::vec4(vU, 0.0f));
    vV = glm::normalize(T * glm::vec4(vV, 0.0f));
    vN = glm::normalize(T * glm::vec4(vN, 0.0f));
    position = T * glm::vec4(position, 1.0f);
}

 // FIGV CAM: 2
void FigvCamera::pan(float movementX, float movementY) {
    glm::mat4 R;
    glm::mat4 T;
    // 1
    glm::mat4 TR = glm::translate(glm::mat4(1.0f), position);
    glm::mat4 TRI = glm::translate(glm::mat4(1.0f), -position);
    // 2
    R = glm::rotate(glm::mat4(1.0f), glm::radians(movementY * 0.1f), vU);
    // 3
    T = TR * R * TRI;
    // 4
    vV = glm::normalize(T * glm::vec4(vV, 0.0f));
    vN = glm::normalize(T * glm::vec4(vN, 0.0f));
    lookAt = T * glm::vec4(lookAt, 1.0f);
    // 5
    R = glm::rotate(glm::mat4(1.0f), glm::radians(movementX * 0.1f), 
    glm::vec3(0.0, 1.0, 0.0));
    T = TR * R * TRI;
    // 6
    vU = glm::normalize(T * glm::vec4(vU, 0.0f));
    vV = glm::normalize(T * glm::vec4(vV, 0.0f));
    vN = glm::normalize(T * glm::vec4(vN, 0.0f));
    lookAt = T * glm::vec4(lookAt, 1.0f);
}

void FigvCamera::dolly(float distance) {

    glm::vec3 V = vN;
    float distApplied = distance;

    if (distance > 0.0f) {
        float dist = glm::distance(position, lookAt);
        if (distApplied > dist) {
            distApplied = dist / 2.0f;
            if (distApplied < 0.01f) { return; }
        }
    }

    V *= -distApplied;
    position += V;
}

glm::mat4 FigvCamera::getViewProjectionMatrix() {

    float fovY = 2.0f * atanf( tanf( glm::radians(fovX)/2.0f) / 2.0f);
    glm::mat4 viewMat = glm::lookAt(position, lookAt, vV);
    glm::mat4 projectionMat = glm::perspective(fovY, aspect, zNear, zFar);

    return projectionMat * viewMat;
}

void FigvCamera::setAspect(int width, int height) {
    aspect = float(width) / float(height);
}

glm::vec3 FigvCamera::getPosition() {
    return position;
}
