 #ifndef FIGV_PRUEBA_1_IMGUI_FIGV_LIGHT_SOURCE_H
 #define FIGV_PRUEBA_1_IMGUI_FIGV_LIGHT_SOURCE_H
 
 #include <stdio.h>
 #include <glm/vec3.hpp>
 #include "FigvShader.h"
 struct FigvLightSource {
 public:
    FigvLightSource();
    FigvLightSource(glm::vec3 Id, glm::vec3 Is) : Id(Id), Is(Is) {}
   
    float* getId();
    float* getIs();
 // 2
    void applyToShader(FigvShader shader);
     private:
    // 1
    glm::vec3 position = glm::vec3(4.0, 8.0, 12.0);
    glm::vec3 Id = glm::vec3(0.8f);
    glm::vec3 Is = glm::vec3(1.0f);
 };
 #endif // FIGV_PRUEBA_1_IMGUI_FIGV_LIGHT_SOURCE_H