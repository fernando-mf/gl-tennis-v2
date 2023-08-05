#ifndef PA2_TENNISBALLMODEL_H
#define PA2_TENNISBALLMODEL_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include "../ShaderProgram.h"
#include "../Texture.h"

using namespace glm;

class TennisBallModel {
private:
    GLuint vaoBall;
    unsigned int verticesNum;
    Texture ballTexture;
public:
    TennisBallModel();

    void draw(mat4 hierarchyModelMatrix, ShaderProgram shaderProgram, GLuint renderingMode);
};

#endif //PA2_TENNISBALLMODEL_H