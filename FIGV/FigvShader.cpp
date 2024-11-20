//
// Created by fconde on 4/10/23.
//

#include <fstream>
#include <glad/glad.h>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>
#include "FigvShader.h"
#include "FigvAuxiliaryFunctions.h"

FigvShader::FigvShader(const char* vertexPath, const char* fragmentPath) {

    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try
    {

        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch(std::ifstream::failure e)
    {
        FigvLog("FigvShader", __LINE__, "Error: Shader file not succesfully read");
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();


    unsigned int vertex, fragment;

    compileShader(GL_VERTEX_SHADER, vShaderCode, vertex);
    compileShader(GL_FRAGMENT_SHADER, fShaderCode, fragment);

    char infoLog[512];

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        FigvLog( "FigvShader", __LINE__, "Error: Shader linking failed" );
        FigvLog( "FigvShader", __LINE__, infoLog );
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void FigvShader::compileShader(int type, const char *&shaderCode, unsigned int &handler) {
    int compileSuccess;
    char infoLog[512];

    handler = glCreateShader(type);
    glShaderSource(handler, 1, &shaderCode, NULL);
    glCompileShader(handler);
    glGetShaderiv(handler, GL_COMPILE_STATUS, &compileSuccess);
    if(!compileSuccess)
    {
        glGetShaderInfoLog(handler, 512, NULL, infoLog);
        FigvLog("FigvShader", __LINE__, "Error: Shader compilation failed");
        FigvLog("FigvShader", __LINE__,  infoLog );
    };
}

void FigvShader::use() const {
    if (success) {
        glUseProgram(ID);
    } else {
        FigvLog("FigvShader", __LINE__, "Error: Attempt to use an invalid shader");
    }
}

void FigvShader::set(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void FigvShader::set(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void FigvShader::set(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void FigvShader::set(const std::string &name, const glm::vec3 &value) {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z);
}

void FigvShader::set(const std::string &name, glm::mat4 &value) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, false, glm::value_ptr(value));
}

