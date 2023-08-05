//
// Created by Fernando Mamani 40169982.
//

#include "TennisBallFernando.h"

#include <glm/gtc/matrix_transform.hpp>

const vec3 COLOR_TENNIS_BALL = vec3(0.0f, 1.0f, 0.0f);

TennisBallFernando::TennisBallFernando() {
    this->tennisBallTexture = Texture("./assets/textures/tennis_ball.png");
    this->tennisSphere = SphereFernando(COLOR_TENNIS_BALL);
}

void TennisBallFernando::draw(glm::mat4 hierarchyModelMatrix, ShaderProgram shaderProgram, GLuint renderingMode) {
    float tennisBallRadius = 0.8f;
    mat4 partMatrix = translate(mat4(1.0f), vec3(0.0f, 11.0f, 0.0f)) *
                      scale(mat4(1.0f), vec3(tennisBallRadius));
    mat4 worldMatrix = hierarchyModelMatrix * partMatrix;

    tennisBallTexture.use();
    shaderProgram.setWorldMatrix(worldMatrix);
    tennisSphere.draw(renderingMode);
}