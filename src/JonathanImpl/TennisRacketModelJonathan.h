#ifndef PA2_TENNISRACKETMODELJONATHAN_H
#define PA2_TENNISRACKETMODELJONATHAN_H

#include "../TennisRacketModel.h"

#include <glm/gtc/matrix_transform.hpp>

class TennisRacketModelJonathan : public TennisRacketModel {
private:
    GLuint vaoArm;
    GLuint vaoRacketFrameRed;
    GLuint vaoRacketFrameGrey;
    GLuint vaoRacketString;
public:
    TennisRacketModelJonathan(const vec3 &position);

    void draw(mat4 hierarchyModelMatrix, ShaderProgram shaderProgram, GLuint renderingMode) override;
};

#endif //PA2_TENNISRACKETMODELJONATHAN_H