#include <iostream>

#include "ShaderProgram.h"

using namespace std;
using namespace glm;

ShaderProgram::ShaderProgram() {}

ShaderProgram::ShaderProgram(const char *vertexShaderPath, const char *fragmentShaderPath) {
    // Compile vertex shader
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderPath);
    // Compile fragment shader
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderPath);

    // Create program and link shaders
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for linking errors
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        fprintf(stderr, "failed to link shader program\n%s\n", infoLog);
    }

    // Delete shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Store matrices locations
    glUseProgram(shaderProgram);

    this->viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
    this->projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projectionMatrix");
    this->worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");

    // Store shader program id
    this->id = shaderProgram;
}

void ShaderProgram::setViewMatrix(mat4 viewMatrix) {
    glUseProgram(this->id);
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
}

void ShaderProgram::setProjectionMatrix(mat4 projectionMatrix) {
    glUseProgram(this->id);
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
}

void ShaderProgram::setWorldMatrix(mat4 worldMatrix) {
    glUseProgram(this->id);
    glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]);
}

// Only texture shaders should call this
void ShaderProgram::initializeTextures() {
    glUseProgram(this->id);
    glActiveTexture(GL_TEXTURE0);
    GLuint textureLocation = glGetUniformLocation(this->id, "textureSampler");
    glUniform1i(textureLocation, 0);
}

// Acknowledgment that some of this method was based on online examples for file input in C++
const char* ShaderProgram::readFile(const char *filePath) {
    FILE *f = fopen(filePath, "rb");
    if (f == NULL) {
        fprintf(stderr, "failed to open file %s\n", filePath);
        exit(1);
    }
    fseek(f, 0, SEEK_END);

    long fileSize = ftell(f);
    rewind(f);

    char *contents = new char[fileSize + 1];
    fread(contents, fileSize, 1, f);
    fclose(f);

    contents[fileSize] = 0; // Add null terminator
    return contents;
}

int ShaderProgram::compileShader(GLenum shaderType, const char *shaderPath) {
    int shader = glCreateShader(shaderType);
    const char *shaderSource = readFile(shaderPath);
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);

    // Check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        fprintf(stderr, "failed to compile shader %s\n%s\n", shaderPath, infoLog);
    }

    return shader;
}