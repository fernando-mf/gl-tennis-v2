//
// Created by Fernando Mamani 40169982.
//

#ifndef ASSIGNMENT2_TENNISBALLFERNANDO_H
#define ASSIGNMENT2_TENNISBALLFERNANDO_H

#include <glm/glm.hpp>
#include <GL/glew.h>

#include "../Texture.h"
#include "../ShaderProgram.h"
#include "SphereFernando.h"

using namespace glm;

class TennisBallFernando {
private:
    SphereFernando tennisSphere;
    Texture tennisBallTexture;
public:
    TennisBallFernando();

    void draw(mat4 hierarchyModelMatrix, ShaderProgram coloredshader, GLuint renderingMode);
};


#endif //ASSIGNMENT2_TENNISBALLFERNANDO_H
