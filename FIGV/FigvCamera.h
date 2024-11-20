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

#ifndef FIGV_PRUEBA_1_IMGUI_FIGVCAMERA_H
#define FIGV_PRUEBA_1_IMGUI_FIGVCAMERA_H

#include <glm/glm.hpp>

/// En un programa gráfico, una cámara se representa como dos matrices, la de
/// visión que transforma la escena para facilitar los cálculos y la de proyección
/// que transforma una escena 3D en una 2D representable en una pantalla plana.
/// Esas matrices son muy complejas de construir para un operador humano por lo
/// que se construye un sistema de ejes de coordenadas a partir del cual
/// obtener las transformaciones adecuadas.
///
/// Esta clase encapsula todo el proceso para facilitar el uso de una camara
/// virtual en la aplicación.
class FigvCamera {

public:
    FigvCamera();

    /// Realiza un movimiento de órbita alrededor del punto de vista. El punto
    /// en el que está la cámara se mueve en círculos alrededor del punto hacia
    /// el que mira la cámara (punto de vista).
    ///
    /// El movimiento del punto en el que está la cámara es alrededor del eje X
    /// de la cámara y del eje Y del mundo.
    ///
    /// @param movementX Ángulo que controla el giro alrededor del eje Y del
    ///                  mundo.
    /// @param movementY Ángulo que controla el giro alrededor del eje X de la
    ///                  cámara.
    void orbit(float movementX, float movementY);
    
    // FIGV CAM: 1
    void pan(float movementX, float movementY);

    /// Acerca o aleja la cámara virtual. El punto en el que está la cámara se
    /// mueve a lo largo del eje Z de la cámara, el que se forma restandole
    /// el punto de vista. El resultado es que el punto donde está la camara se
    /// acerca o aleja del punto de vista.
    ///
    /// @param distance Distancia que se mueve el punto en el que está la
    ///        camara. Positivo acerca y negativo aleja.
    void dolly(float distance);
    
    /// Accede a las matrices de visión y proyección, ya multiplicadas y listas
    /// para aplicar a los vértices de la escena.
    ///
    /// @return Matriz de visión y proyección de la cámara ya multiplicadas entre
    ///         si.
    glm::mat4 getViewProjectionMatrix();
    /// Accede a la posición de la cámara. El punto desde el que se mira a la
    /// escena.
    glm::vec3 getPosition();

    /// Cambia el aspecto (relación entre anchura y altura) de la cámara. Esto
    /// permite redimensionar la ventana de la aplicación y que la imagen que
    /// se muestra en ella siga siendo proporcionada.
    void setAspect(int width, int height);

private:
    /// Punto en el que está situada la camara. Es desde donde se observa la
    /// escena.
    glm::vec3 position;
    /// Punto de interés. Es el punto hacia el que mira la camara.
    glm::vec3 lookAt;
    /// Aspecto. Relación entre el ancho y el alto del plano de proyección. Se
    /// mantiene igual al de la ventana de la aplicación, para que la escena
    /// se rendirize sin distorsiones.
    float aspect;
    /// Ángulo de visión horizontal expresado en grados sexagesimales.
    /// Internamente, la camara usa en sus cálculos, el ángulo de visión vertical
    /// expresado en radianes, pero este es más útil para un operador humano
    /// ya que es el que se usa en las camaras fotográficas.
    float fovX;
    /// Plano de recorte frontal. Es la distancia medida a lo largo del eje Z
    /// de la cámara a la que se sitúa este plano.
    /// Impide que los objetos situados detrás de la camara aparezcan en el
    /// rendering final. Debe ajustarse lo mas que se pueda al tamaño de la
    /// escena para que se aproveche al maximo la resolución del z-buffer.
    float zNear;
    /// Plano de recorte posterior. Es la distancia medida a lo largo del eje Z
    /// de la cámara a la que se sitúa este plano.
    /// Los objetos situados más lejos que este plano no aparecerán en la
    /// imagen renderizada. Debe ajustarse lo mas que se pueda al tamaño de la
    /// escena para que se aproveche al maximo la resolución del z-buffer.
    float zFar;

    // Estos vectores representan el sistema de coordenadas de la camara. Permiten
    // mover la camara de forma intuitiva, con movimientos como dolly o orbit,
    // que se usan en el cine.
    glm::vec3 vU;
    glm::vec3 vV;
    glm::vec3 vN;

    /// Calcula el sistema de ejes de la cámara a partir del punto donde está
    /// situada y el punto al que mira (punto de vista). Es privado porque solo
    /// debe llamarse desde otros métodos que cambien la posición o el punto de vista.
    void calculateVectors();
};


#endif //FIGV_PRUEBA_1_IMGUI_FIGVCAMERA_H
