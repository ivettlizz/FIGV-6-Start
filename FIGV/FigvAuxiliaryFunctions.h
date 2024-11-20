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

#ifndef FIGV_PRUEBA_1_IMGUI_FIGVAUXILIARYFUNCTIONS_H
#define FIGV_PRUEBA_1_IMGUI_FIGVAUXILIARYFUNCTIONS_H

#include <string>

/// @file

/// Función auxiliar para imprimir mensajes formateados.
/// El mensaje incluye el nombre de la clase donde se producen y la línea en la
/// que se invoca a esta función.
///
/// Un uso típico sería:
/// \code
/// FigvLog("NombreClase", __LINE__, "Mensaje a mostrar");
/// \endcode
///
/// Las ventajas de este método es que cada mensaje va precedido del prefijo:
/// **FIGV:** Con lo que en cualquier IDE se pueden filtrar facilmente los mensajes
/// de la aplicación, distinguiéndolos de los mensajes del sistema.
void FigvLog(std::string className, int linea, std::string message);

#endif //FIGV_PRUEBA_1_IMGUI_FIGVAUXILIARYFUNCTIONS_H
