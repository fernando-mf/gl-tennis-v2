#ifndef PA2_TENNISRACKETMODELKIRANF_H
#define PA2_TENNISRACKETMODELKIRANF_H

#include "../TennisRacketModel.h"

#include <glm/gtc/matrix_transform.hpp>

class TennisRacketModelKiranF : public TennisRacketModel {
private:
    GLuint vaoArm;
    GLuint vaoRacketFrameRed;
    GLuint vaoRacketFrameGrey;
    GLuint vaoRacketString;
    GLuint vaoSphere;

    std::vector<unsigned int> sphereIndices;
public:
    TennisRacketModelKiranF(const vec3 &position);

    void draw(mat4 hierarchyModelMatrix, ShaderProgram shaderProgram, GLuint renderingMode) override;
};

#endif //PA2_TENNISRACKETMODELKIRANF_H