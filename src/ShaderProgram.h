#ifndef PA2_SHADERPROGRAM_H
#define PA2_SHADERPROGRAM_H

#include <GL/glew.h>
#include <glm/glm.hpp>

using namespace glm;

class ShaderProgram {
private:
    bool texturesEnabled = true;

    const char* readFile(const char* filePath);

    int compileShader(GLenum shaderType, const char *shaderPath);
public:
    int id;
    int viewMatrixLocation;
    int projectionMatrixLocation;
    int worldMatrixLocation;
    int texturesEnabledLocation;
    int lightSpaceMatrixLocation;
    int shadowMapLocation;
    int lightPositionLocation;

    ShaderProgram();

    ShaderProgram(const char *vertexShaderPath, const char *fragmentShaderPath);

    void setViewMatrix(mat4 viewMatrix);

    void setProjectionMatrix(mat4 projectionMatrix);

    void setWorldMatrix(mat4 worldMatrix);

    void initializeTextures();

    void useTextures();

    void useColors();

    void enableTextures();

    void disableTextures();

    void setLightSpaceMatrix(mat4 lightSpaceMatrix);

    void setShadowMap(int shadowMap);

    void setLightPosition(vec3 lightPosition);
};

#endif //PA2_SHADERPROGRAM_H