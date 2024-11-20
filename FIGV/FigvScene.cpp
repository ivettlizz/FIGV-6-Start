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

#include "FigvScene.h"
#include <glm/gtc/type_ptr.hpp>
#include "FigvAuxiliaryFunctions.h"
#include "FigvMaterial.h"

FigvScene* FigvScene::instance = nullptr;

FigvScene::FigvScene() {
    
    FigvLog("FigvScene", __LINE__, "Initializing the scene");
    
    camera = new FigvCamera();
    models = std::vector<FigvModel>();
    
    // FIGV SCE: 7
    glm::mat4 T;
    glm::mat4 R;
    // 1
    T = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0, 0.0, 0.0));
    R = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.0));
    models.push_back(FigvModel("./models/spot/spot_triangulated.obj",
                            new FigvMaterial(8.0, 
                                                glm::vec3(1.0, 0.0, 0.0), 
                                                glm::vec3(1.0)),
                            T * R));
    // 2
    R = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));
    models.push_back(FigvModel("./models/bob/bob_tri.obj",
                            new FigvMaterial(),
                            R));
    // 3
    T = glm::translate(glm::mat4(1.0f), glm::vec3(2.0, 0.0, 0.0));
    models.push_back(FigvModel("./models/blub/blub_triangulated.obj",
                            new FigvMaterial(256.0, 
                                                glm::vec3(0.25, 0.5, 1.0), 
                                                glm::vec3(1.0)),
                            T));
    // FIGV SCE: 15
    lightSource = new FigvLightSource();
}

FigvScene::~FigvScene() = default;

FigvScene *FigvScene::getInstance() {
    // - Se usa lazy initialization. Sólo se construye cuando se necesita.
    if (!instance) { instance = new FigvScene(); }
    return instance;
}

void FigvScene::orbitCamera(float movementX, float movementY) {

    FigvScene::getInstance()->camera->orbit(movementX, movementY);
}

 // FIGV SCE: 2
 void FigvScene::panCamera(float movementX, float movementY) {
    FigvScene::getInstance()->camera->pan(movementX, movementY);
 }
void FigvScene::dollyCamera(float distance) {

    FigvScene::getInstance()->camera->dolly(distance);
}

void FigvScene::drawScene(FigvShader shader) {

    shader.use();
    glm::mat4 viewProj = FigvScene::getInstance()->camera->getViewProjectionMatrix();
    shader.set("mViewProjection", viewProj);
    
    shader.set("Ia", FigvScene::getInstance()->Ia);
    // FIGV SCE: 16
    FigvScene::getInstance()->lightSource->applyToShader(shader);
    
    shader.set("cameraPosition", FigvScene::getInstance()->camera->getPosition());
    // FIGV SCE: 8
    for (auto& model : FigvScene::getInstance()->models) {
         model.draw(shader);
    }
}

void FigvScene::setFrameSize(int width, int height) {

    FigvScene::getInstance()->camera->setAspect(width, height);
}

float* FigvScene::getIa() {
    return glm::value_ptr(Ia);
}

// FIGV SCE: 17
float* FigvScene::getId() {
 return lightSource->getId();
}
float* FigvScene::getIs() {
 return lightSource->getIs();
}

