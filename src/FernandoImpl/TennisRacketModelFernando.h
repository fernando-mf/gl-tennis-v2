//
// Created by Fernando Mamani 40169982.
//

#ifndef PA2_TENNISRACKETMODELFERNANDO_H
#define PA2_TENNISRACKETMODELFERNANDO_H

#include <glm/glm.hpp>
#include <GL/glew.h>

#include "../Cube.h"
#include "../ShaderProgram.h"
#include "../TennisRacketModel.h"

using namespace glm;

class RacketFernando {
private:
    Cube racketBody;
    Cube racketBodyAlt;
    Cube racketStrings;
public:
    mat4 racketHierarchyModelMatrix;

    RacketFernando();

    void
    draw(mat4 hierarchyModelMatrix, ShaderProgram coloredshader, GLuint renderingMode);
};

class TennisRacketModelFernando : public TennisRacketModel {
private:
    RacketFernando racket;
    Cube arm;
public:
    TennisRacketModelFernando(const vec3 &position);

    void animate(float lastFrameTime, float dt);

    void draw(mat4 hierarchyModelMatrix, ShaderProgram coloredshader, GLuint renderingMode) override;

    mat4 getRacketHierarchyModelMatrix();
};

#endif //PA2_TENNISRACKETMODELFERNANDO_H
