 #include "FigvLightSource.h"
 #include <glm/gtc/type_ptr.hpp>
 FigvLightSource::FigvLightSource() {}
 float* FigvLightSource::getId() {
 return glm::value_ptr(Id);
 }
 float* FigvLightSource::getIs() {
 return glm::value_ptr(Is);
 }

void FigvLightSource::applyToShader(FigvShader shader) {
 shader.set("Id", Id);
 shader.set("Is", Is);
 shader.set("lightPosition", position);
 }