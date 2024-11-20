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

#include <iostream>

#include "FigvAuxiliaryFunctions.h"

void FigvLog(std::string className, int line, std::string message) {
    std::cout << "FIGV: " << className << "(" << line << "): " << message << std::endl;
}
