//
// Created by Fernando Mamani 40169982.
//

#include "TennisRacketModelFernando.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace glm;
using namespace std;

//
// Racket model
//

const vec3 COLOR_RACKET_BODY = vec3(0.44f, 0.0f, 0.008f);
const vec3 COLOR_RACKET_BODY_ALT = vec3(0.61f, 0.61f, 0.61f);
const vec3 COLOR_RACKET_STRINGS = vec3(0.31f, 0.68f, 0.027f);


RacketFernando::RacketFernando() {
    this->racketBody = Cube(COLOR_RACKET_BODY);
    this->racketBodyAlt = Cube(COLOR_RACKET_BODY_ALT);
    this->racketStrings = Cube(COLOR_RACKET_STRINGS);
}

void RacketFernando::draw(mat4 hierarchyModelMatrix, ShaderProgram colorShader,
                          GLuint renderingMode) {
    // handle
    const float racketSize = 0.3f;
    const float racketHandleLength = 3.0f;

    mat4 partMatrix = translate(mat4(1.0f), vec3(0.0f, racketHandleLength / 2, 0.0f)) *
                      scale(mat4(1.0f), vec3(racketSize, racketHandleLength, racketSize));
    mat4 groupMatrix = hierarchyModelMatrix;

    mat4 worldMatrix = groupMatrix * partMatrix;
    colorShader.setWorldMatrix(worldMatrix);
    glBindVertexArray(this->racketBody.getVertexBufferObject());
    glDrawArrays(renderingMode, 0, 36);

    // racket rim
    const float racketRimWidth = 2.2f;
    const float racketRimHeight = 3.0f;

    // calculate desired width based on inclination angle
    const float racketRimWidthBottom = (racketRimWidth / 2) / cos(radians(50.0f));

    // bottom - left
    groupMatrix = groupMatrix *
                  translate(mat4(1.0f), vec3(0.0f, racketHandleLength, 0.0f));

    partMatrix = rotate(mat4(1.0f), radians(-45.0f), vec3(0.0f, 0.0f, 1.0f)) *
                 translate(mat4(1.0f), vec3(-racketRimWidthBottom / 2, racketSize / 2, 0.0f)) *
                 scale(mat4(1.0f), vec3(racketRimWidthBottom, racketSize, racketSize));

    worldMatrix = groupMatrix * partMatrix;
    colorShader.setWorldMatrix(worldMatrix);
    glBindVertexArray(this->racketBodyAlt.getVertexBufferObject());
    glDrawArrays(renderingMode, 0, 36);

    // bottom - right
    partMatrix = rotate(mat4(1.0f), radians(45.0f), vec3(0.0f, 0.0f, 1.0f)) *
                 translate(mat4(1.0f), vec3(racketRimWidthBottom / 2, racketSize / 2, 0.0f)) *
                 scale(mat4(1.0f), vec3(racketRimWidthBottom, racketSize, racketSize));
    worldMatrix = groupMatrix * partMatrix;
    colorShader.setWorldMatrix(worldMatrix);
    glBindVertexArray(this->racketBodyAlt.getVertexBufferObject());
    glDrawArrays(renderingMode, 0, 36);

    // bottom - straight
    partMatrix = translate(mat4(1.0f), vec3(0.0f, 1.0f, 0.0f)) *
                 scale(mat4(1.0f), vec3(racketRimWidthBottom - 0.5f, racketSize, racketSize));
    worldMatrix = groupMatrix * partMatrix;
    colorShader.setWorldMatrix(worldMatrix);
    glBindVertexArray(this->racketBody.getVertexBufferObject());
    glDrawArrays(renderingMode, 0, 36);

    // left
    groupMatrix = groupMatrix *
                  translate(mat4(1.0f), vec3(0.0f, 1.2f, 0.0f));

    partMatrix = translate(mat4(1.0f), vec3(-racketRimWidth / 2, racketRimHeight / 2, 0.0f)) *
                 scale(mat4(1.0f), vec3(racketSize, racketRimHeight, racketSize));

    worldMatrix = groupMatrix * partMatrix;
    colorShader.setWorldMatrix(worldMatrix);
    glBindVertexArray(this->racketBody.getVertexBufferObject());
    glDrawArrays(renderingMode, 0, 36);

    // right
    partMatrix = translate(mat4(1.0f), vec3(racketRimWidth / 2, racketRimHeight / 2, 0.0f)) *
                 scale(mat4(1.0f), vec3(racketSize, racketRimHeight, racketSize));

    worldMatrix = groupMatrix * partMatrix;
    colorShader.setWorldMatrix(worldMatrix);
    glBindVertexArray(this->racketBody.getVertexBufferObject());
    glDrawArrays(renderingMode, 0, 36);

    // top left base
    partMatrix = translate(mat4(1.0f), vec3(-racketRimWidth / 2, racketRimHeight - 0.05f, 0.0f)) *
                 rotate(mat4(1.0f), radians(45.0f), vec3(0.0f, 0.0f, 1.0f)) *
                 translate(mat4(1.0f), vec3((racketRimWidth / 4) / 2, 0.0f, 0.0f)) *
                 scale(mat4(1.0f), vec3(racketRimWidth / 4, racketSize, racketSize));
    worldMatrix = groupMatrix * partMatrix;
    colorShader.setWorldMatrix(worldMatrix);
    glBindVertexArray(this->racketBodyAlt.getVertexBufferObject());
    glDrawArrays(renderingMode, 0, 36);

    // top left base 2
    partMatrix = translate(mat4(1.0f), vec3(-racketRimWidth / 2 + 0.3f, racketRimHeight + 0.3f, 0.0f)) *
                 rotate(mat4(1.0f), radians(25.0f), vec3(0.0f, 0.0f, 1.0f)) *
                 translate(mat4(1.0f), vec3((racketRimWidth / 4) / 2, 0.0f, 0.0f)) *
                 scale(mat4(1.0f), vec3(racketRimWidth / 4, racketSize, racketSize));
    worldMatrix = groupMatrix * partMatrix;
    colorShader.setWorldMatrix(worldMatrix);
    glBindVertexArray(this->racketBody.getVertexBufferObject());
    glDrawArrays(renderingMode, 0, 36);

    // top
    partMatrix = translate(mat4(1.0f), vec3(0.0f, racketRimHeight + 0.5f, 0.0f)) *
                 scale(mat4(1.0f), vec3(racketRimWidth / 3.5, racketSize, racketSize));
    worldMatrix = groupMatrix * partMatrix;
    colorShader.setWorldMatrix(worldMatrix);
    glBindVertexArray(this->racketBodyAlt.getVertexBufferObject());
    glDrawArrays(renderingMode, 0, 36);

    // top right base 2
    partMatrix = translate(mat4(1.0f), vec3(racketRimWidth / 2 - 0.3f, racketRimHeight + 0.3f, 0.0f)) *
                 rotate(mat4(1.0f), radians(155.0f), vec3(0.0f, 0.0f, 1.0f)) *
                 translate(mat4(1.0f), vec3((racketRimWidth / 4) / 2, 0.0f, 0.0f)) *
                 scale(mat4(1.0f), vec3(racketRimWidth / 4, racketSize, racketSize));
    worldMatrix = groupMatrix * partMatrix;
    colorShader.setWorldMatrix(worldMatrix);
    glBindVertexArray(this->racketBody.getVertexBufferObject());
    glDrawArrays(renderingMode, 0, 36);

    // top right base
    partMatrix = translate(mat4(1.0f), vec3(racketRimWidth / 2, racketRimHeight - 0.05f, 0.0f)) *
                 rotate(mat4(1.0f), radians(135.0f), vec3(0.0f, 0.0f, 1.0f)) *
                 translate(mat4(1.0f), vec3((racketRimWidth / 4) / 2, 0.0f, 0.0f)) *
                 scale(mat4(1.0f), vec3(racketRimWidth / 4, racketSize, racketSize));
    worldMatrix = groupMatrix * partMatrix;
    colorShader.setWorldMatrix(worldMatrix);
    glBindVertexArray(this->racketBodyAlt.getVertexBufferObject());
    glDrawArrays(renderingMode, 0, 36);

    // racket strings
    const float verticalStringCount = racketRimWidth / 10;
    const float horizontalStringCount = racketRimHeight / 10;
    const float racketStringSize = 0.05f;

    for (int i = 0; i <= 10; i++) {
        float height = i > 2 && i < 8 ? racketRimHeight + 0.7f : racketRimHeight;

        partMatrix =
                translate(mat4(1.0f),
                          vec3(-(racketRimWidth / 2) + i * verticalStringCount, racketRimHeight / 2, 0.0f)) *
                scale(mat4(1.0f), vec3(racketStringSize, height, racketStringSize));

        worldMatrix = groupMatrix * partMatrix;
        colorShader.setWorldMatrix(worldMatrix);
        glBindVertexArray(this->racketStrings.getVertexBufferObject());
        glDrawArrays(renderingMode, 0, 36);
    }
    for (int i = 0; i <= 10; i++) {
        partMatrix =
                translate(mat4(1.0f),
                          vec3(0.0f, i * horizontalStringCount, 0.0f)) *
                scale(mat4(1.0f), vec3(racketRimWidth, racketStringSize, racketStringSize));

        worldMatrix = groupMatrix * partMatrix;
        colorShader.setWorldMatrix(worldMatrix);
        glBindVertexArray(this->racketStrings.getVertexBufferObject());
        glDrawArrays(renderingMode, 0, 36);
    }

    this->racketHierarchyModelMatrix = groupMatrix;
}

//
// Arm with racket
//

const vec3 COLOR_ARM = vec3(0.75f, 0.63f, 0.46f);

const float armSize = 0.5f;
const float armLength = 4.0f;

float modelInitialAngle = -50.0f;
float upperArmAngle = -modelInitialAngle;

TennisRacketModelFernando::TennisRacketModelFernando(const vec3 &position) : TennisRacketModel(position) {
    this->racket = RacketFernando();
    this->arm = Cube(COLOR_ARM);
}

void TennisRacketModelFernando::animate(float lastFrameTime, float dt) {
    upperArmAngle += 35 * cos(lastFrameTime - 10) * dt;
}

void TennisRacketModelFernando::draw(mat4 hierarchyModelMatrix, ShaderProgram colorShader, GLuint renderingMode) {
    // lower arm
    mat4 partMatrix = translate(mat4(1.0f), vec3(0.0f, armLength / 2, 0.0f)) *
                      scale(mat4(1.0f), vec3(armSize, armLength, armSize));

    mat4 groupMatrix = hierarchyModelMatrix *
                       rotate(mat4(1.0f), radians(this->getModelRotationZAxis() - upperArmAngle),
                              vec3(0.0f, 0.0f, 1.0f)) *
                       rotate(mat4(1.0f), radians(this->getModelRotationYAxis()), vec3(0.0f, 1.0f, 0.0f)) *
                       rotate(mat4(1.0f), radians(this->getModelRotationXAxis()), vec3(1.0f, 0.0f, 0.0f));
    mat4 worldMatrix = groupMatrix * partMatrix;
    colorShader.setWorldMatrix(worldMatrix);
    glBindVertexArray(this->arm.getVertexBufferObject());
    glDrawArrays(renderingMode, 0, 36);

    // upper arm
    partMatrix = translate(mat4(1.0f), vec3(0.0f, armLength / 2, 0.0f)) *
                 scale(mat4(1.0f), vec3(armSize, armLength, armSize));
    groupMatrix = groupMatrix *
                  translate(mat4(1.0f), vec3(0.0f, armLength, 0.0f)) *
                  rotate(mat4(1.0f), radians(this->getModelLowerarmRotationZAxis() + upperArmAngle),
                         vec3(0.0f, 0.0f, 1.0f)) *
                  rotate(mat4(1.0f), radians(this->getModelLowerarmRotationYAxis()), vec3(0.0f, 1.0f, 0.0f)) *
                  rotate(mat4(1.0f), radians(this->getModelLowerarmRotationXAxis()), vec3(1.0f, 0.0f, 0.0f));

    worldMatrix = groupMatrix * partMatrix;
    colorShader.setWorldMatrix(worldMatrix);
    glBindVertexArray(this->arm.getVertexBufferObject());
    glDrawArrays(renderingMode, 0, 36);

    float handSize = 1.0f;

    // hand
    partMatrix = translate(mat4(1.0f), vec3(0.0f, handSize / 2, 0.0f)) *
                 scale(mat4(1.0f), vec3(handSize, handSize, handSize));
    groupMatrix = groupMatrix *
                  translate(mat4(1.0f), vec3(0.0f, armLength, 0.0f)) *
                  rotate(mat4(1.0f), radians(this->getModelHandRotationZAxis()), vec3(0.0f, 0.0f, 1.0f)) *
                  rotate(mat4(1.0f), radians(this->getModelHandRotationYAxis()), vec3(0.0f, 1.0f, 0.0f)) *
                  rotate(mat4(1.0f), radians(this->getModelHandRotationXAxis()), vec3(1.0f, 0.0f, 0.0f));
    worldMatrix = groupMatrix * partMatrix;
    colorShader.setWorldMatrix(worldMatrix);
    glBindVertexArray(this->arm.getVertexBufferObject());
    glDrawArrays(renderingMode, 0, 36);

    // draw racket
    mat4 racketMatrix = groupMatrix * translate(mat4(1.0f), vec3(0.0f, handSize, 0.0f));
    racket.draw(racketMatrix, colorShader, renderingMode);
}

mat4 TennisRacketModelFernando::getRacketHierarchyModelMatrix() {
    return this->racket.racketHierarchyModelMatrix;
}