
#include "../TennisRacketModel.h"

#include <glm/gtc/matrix_transform.hpp>

class TennisRacketModelMatthew : public TennisRacketModel {
private:
    GLuint upperArmAO;
    GLuint racketAO;
public:
    TennisRacketModelMatthew(const vec3 &position);

    void draw(mat4 hierarchyModelMatrix, ShaderProgram shaderProgram, GLuint renderingMode) override;
};
