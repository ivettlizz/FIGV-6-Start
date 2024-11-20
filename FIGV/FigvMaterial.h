 #ifndef FIGV_PRUEBA_1_IMGUI_FIGVMATERIAL_H
 #define FIGV_PRUEBA_1_IMGUI_FIGVMATERIAL_H
 #include <glm/vec3.hpp>
 #include "FigvShader.h"

struct FigvMaterial {
 public:
 FigvMaterial();
 FigvMaterial(float shininess, glm::vec3 Kd, glm::vec3 Ks):
 shininess(shininess), Kd(Kd), Ks(Ks) {}
 float* getShininess();
 float* getKd();
 float* getKs();
 void applyToShader(FigvShader shader);
 private:
 float shininess = 64.0f;
 glm::vec3 Kd = glm::vec3(1.0f, 0.75f, 0.25f);
 glm::vec3 Ks = glm::vec3(1.0f);
 };
 #endif // FIGV_PRUEBA_1_IMGUI_FIGVMATERIAL_H