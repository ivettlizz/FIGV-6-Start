//
// Created by fconde on 4/10/23.
//

#pragma once

#ifndef FIGV_PRUEBA_1_IMGUI_FIGVSHADER_H
#define FIGV_PRUEBA_1_IMGUI_FIGVSHADER_H

#include <string>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>

/// Encapsula el proceso de lectura, compilación, enlazado, uso y paso de parámetros
/// a un shader.
///
/// Un shader es un programa que puede cargarse en la GPU para modificar la forma
/// en que se lleva a cabo el **pipeline de rendering.** Existen diversas etapas
/// del pipiline que se pueden programar. En estas práctica solo usaremos las
/// dos principales: vertex y shader.
class FigvShader {

public:
    // the program ID
    unsigned int ID;

    /// Construye un shader program, con dos shader objects (vertex y fragment)
    /// cuyo código está en los archivos cuyo path se pasa como argumento.
    ///
    /// @param vertexPath Ruta al archivo que contiene el vertex shader con el
    ///                   que construir el shader program.
    /// @param fragmentPath Ruta al archivo que contiene el fragment shader con
    ///                     el que construir el shader program.
    FigvShader(const char* vertexPath, const char* fragmentPath);

    /// Activa el shader program. A partir de la ejecución de este método, todas
    /// las órdenes de dibujo se renderizarán siguiendo las instrucciones de este
    /// shader object.
    ///
    /// @note Antes de aplicar el shader se comprueba si es un shader válido
    ///       (se ha podido compilar, asignar y enlazar correctamente) y si no
    ///       lo es, no se aplica. La comprobación se realiza mediante la bandera
    ///       booleana `success`
    void use() const;

    // Nota: Todos los métodos `set` están sobrecargados. El compilador sabe
    //       cuál hay que usar en cada caso por el tipo de los argumentos.
    
    /// Pasa un `bool` al shader que está en uso en este momento como parámetro
    /// de tipo **uniform**
    ///
    /// @param name Nombre del parámetro de tipo uniform en el shader. La
    ///             correspondencia es por nombres, por lo que eebe escribirse
    ///             tal y como aparece escrito en el shader.
    /// @param value Valor booleano que se quiere pasar.
    void set(const std::string &name, bool value) const;
    
    /// Pasa un `int` al shader que está en uso en este momento como parámetro
    /// de tipo **uniform**
    ///
    /// @param name Nombre del parámetro de tipo uniform en el shader. La
    ///             correspondencia es por nombres, por lo que eebe escribirse
    ///             tal y como aparece escrito en el shader.
    /// @param value Valor entero que se quiere pasar.
    void set(const std::string &name, int value) const;
    
    /// Pasa un `float` al shader que está en uso en este momento como parámetro
    /// de tipo **uniform**
    ///
    /// @param name Nombre del parámetro de tipo uniform en el shader. La
    ///             correspondencia es por nombres, por lo que eebe escribirse
    ///             tal y como aparece escrito en el shader.
    /// @param value Valor real que se quiere pasar.
    void set(const std::string &name, float value) const;

    /// Pasa un `vec3` (vector de tres coordenadas) al shader que está en uso en
    /// este momento como parámetro de tipo **uniform**
    ///
    /// @param name Nombre del parámetro de tipo uniform en el shader. La
    ///             correspondencia es por nombres, por lo que eebe escribirse
    ///             tal y como aparece escrito en el shader.
    /// @param value vector que se quiere pasar.
    void set(const std::string &name, const glm::vec3 &value);

    /// Pasa una `mat4` (matriz 4x4) al shader que está en uso en este momento 
    /// como parámetro de tipo **uniform**
    ///
    /// @param name Nombre del parámetro de tipo uniform en el shader. La
    ///             correspondencia es por nombres, por lo que eebe escribirse
    ///             tal y como aparece escrito en el shader.
    /// @param value matriz que se quiere pasar.
    void set(const std::string &name, glm::mat4 &value) const;

    
private:
    /// Compila un shader object (vertex o fragment). Este método de utilidad se
    /// usa por el constructor de la clase para compilar los shaders objects que
    /// después se asginan y enlazan para formar el shader program.
    ///
    /// @param type Tipo del shader object que se quiere compilar, en estas
    ///             prácticas puede tomar dos valores: `GL_VERTEX_SHADER` o
    ///             `GL_FRAGMENT_SHADER`
    /// @param shaderCode Cadena de caracteres que contiene el código del shader
    ///                   object que se quiere compilar. Es el texto tal y como
    ///                   se lee del archivo `.glsl`
    /// @param handler Identificador del shader object que se quiere compilar.
    void compileShader(int type, const char *&shaderCode, unsigned int &handler);
    
    /// Indica si el proceso de enlazado del shader program ha tenido éxito
    /// `true` o no `false`
    int success;
};


#endif //FIGV_PRUEBA_1_IMGUI_FIGVSHADER_H
