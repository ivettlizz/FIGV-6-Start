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

#ifndef FIGV_PRUEBA_1_IMGUI_FIGVSCENE_H
#define FIGV_PRUEBA_1_IMGUI_FIGVSCENE_H

#include "FigvShader.h"
#include "FigvCamera.h"
#include "FigvModel.h"
#include "FigvMaterial.h"
#include "FigvLightSource.h"

/// Encapsula la gestión de los elementos que componen una escena: cámara,
/// objetos, materiales y fuentes luminosas. Controla cómo se crean y destruyen.
/// Se encarga de pasar los parámetros de estos elementos al shader activo y
/// de pedir a los objetos que se dibujen.
///
/// Se implementa como un **singleton** para asegurar que en la aplicación solo
/// hay una escena y para facilitar su acceso desde cualquier módulo que lo
/// necesite.
class FigvScene {

public:

    ~FigvScene();

    static FigvScene *getInstance();

    /// Con este método, se pide a la cámara que realce un movimiento de órbita
    /// alrededor del punto de vista.
    ///
    /// @see FigvCamera::orbit()
    static void orbitCamera(float movementX, float movementY);
    
    // FIGV SCE: 1
    static void panCamera(float movementX, float movementY);
    /// Con este método, se pide a la cámara que se acerque o alejde del punto
    /// de vista.
    ///
    /// @see FigvCamera::dolly()
    static void dollyCamera(float distance);

    /// Este método es llamado por el FigRenderer cuando se debe dibujar la
    /// escena. El método pasa al shader los parámetros comunes (cámara, fuente
    /// luminosa, material) y pide al modelo 3D activo que se dibuje.
    static void drawScene(FigvShader shader);
    /// Este método debe ser llamado cada vez que se redimensiona la ventana de
    /// la aplicación, pasándole los nuevos valores de anchura y altura.
    /// El método los usa para actualizar el aspecto de la cámara virtual y que
    /// la imagen renderizada no se deforme (alargue o estreche).
    static void setFrameSize(int width, int height);

    /// @see FigvScene::Ia
    float* getIa();
    /// @see FigvScene::Id
    float* getId();
    /// @see FigvScene::Is
    float* getIs();

private:
    
    /// El constructor es privado para impedir que pueda invocarse para construir
    /// otras instancias además del singleton.
    /// Construye e nicializa la escena.
    ///
    /// Realiza dos acciones:
    /// 1. Construir la cámara virtual que se usará para visualizar la escena.
    /// 2. Cargar tres modelos de objetos 3D para visualizar. Los tres objetos
    ///    se cargan al principio de la ejecución de la aplicación, pero en
    ///    cada momento solo se muestra uno en la pantalla. El que se haya
    ///    seleccionado mediante la interfaz.
    FigvScene();

    static FigvScene *instance;

    /// Cámara virtual que se usa para visualizar la escena.
    FigvCamera* camera;

    /// Modelos 3D cargados listos para ser renderizados. En esta aplicación
    /// inicial se cargan tres modelos.
    std::vector<FigvModel> models;

    // Parámetros de la fuente luminosa que ilumina la escena. En esta versión
    // inicial de la aplicación de prácticas se usa una fuente luminosa de
    // modelado (situada en la posición de la cámara y que se mueve con ella)
    // de forma que no importa como se mueva la cámara, la escena está siempre
    // bien iluminada.
    
    /// Color / Intensidad de la iluminación que se debe al ambiente. Esta luz
    /// no se debe a ninguna fuente luminosa concreta. Se usa en el cálculo del
    /// término ambiente de la ecuación de iluminación.
    glm::vec3 Ia = glm::vec3(0.2f);

     // FIGV SCE: 14
    FigvLightSource* lightSource;
};


#endif //FIGV_PRUEBA_1_IMGUI_FIGVSCENE_H
