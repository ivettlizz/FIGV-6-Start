 #include <stdio.h>
 #include <glm/gtc/type_ptr.hpp>
 #include "FigvMaterial.h"
 #include "FigvShader.h"
 FigvMaterial::FigvMaterial() {}
 float* FigvMaterial::getShininess() {
    return &shininess;
 }
 float* FigvMaterial::getKd() {
    return glm::value_ptr(Kd);
 }
 float* FigvMaterial::getKs() {
    return glm::value_ptr(Ks);
 }
 void FigvMaterial::applyToShader(FigvShader shader) {
    shader.set("Kd", Kd);
    shader.set("Ks", Ks);
    shader.set("shininess", shininess);
 }