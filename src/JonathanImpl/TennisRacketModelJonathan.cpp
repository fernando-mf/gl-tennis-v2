#include "TennisRacketModelJonathan.h"
#include "../TennisRacketModel.h"
#include "../Cube.h"

TennisRacketModelJonathan::TennisRacketModelJonathan(const vec3 &position) : TennisRacketModel(position) {
    Cube cubeArm = Cube(vec3(238.0f/255.0f, 199.0f/255.0f, 149.0f/255.0f));
    Cube cubeRacketFrameRed =  Cube(vec3(163.0f/255.0f, 0.0f, 0.0f));
    Cube cubeRacketFrameGrey =  Cube(vec3(164.0f/255.0f, 164.0f/255.0f, 164.0f/255.0f));
    Cube cubeRacketString = Cube(vec3(36.0f/255.0f, 156.0f/255.0f, 0.0f));

    vaoArm = cubeArm.getVertexBufferObject();
    vaoRacketFrameRed = cubeRacketFrameRed.getVertexBufferObject();
    vaoRacketFrameGrey = cubeRacketFrameGrey.getVertexBufferObject();
    vaoRacketString = cubeRacketString.getVertexBufferObject();
}

void TennisRacketModelJonathan::draw(mat4 hierarchyModelMatrix, ShaderProgram shaderProgram, GLuint renderingMode) {
    // Declare reusable model matrix
    mat4 modelMatrix;

    /* MODEL AND DRAW */
    // Model and draw upper arm
    glBindVertexArray(vaoArm);
    mat4 upperarmModelMatrix = translate(mat4(1.0f), vec3(0.0f, 1.5f, 0.0f)) * rotate(mat4(1.0f), radians(45.0f), vec3(0.0f, 0.0f, 1.0f)) * scale(mat4(1.0f), vec3(3.0f, 0.5f, 0.5f));
    modelMatrix = hierarchyModelMatrix * upperarmModelMatrix;
    shaderProgram.setWorldMatrix(modelMatrix);
    glDrawArrays(renderingMode, 0, 36);

    // Model and draw lower arm
    glBindVertexArray(vaoArm);
    mat4 lowerarmModelMatrix = translate(mat4(1.0f), vec3(0.0f, 1.5f,  0.0f)) * scale(mat4(1.0f), vec3(0.5f, 3.0f, 0.5f));
    hierarchyModelMatrix = hierarchyModelMatrix * translate(mat4(1.0f), vec3(1.0f, 2.37f, 0.0f)) * rotate(mat4(1.0f), radians(this->getModelLowerarmRotationZAxis()), vec3(0.0f, 0.0f, 1.0f)) * rotate(mat4(1.0f), radians(this->getModelLowerarmRotationYAxis()), vec3(0.0f, 1.0f, 0.0f)) * rotate(mat4(1.0f), radians(this->getModelLowerarmRotationXAxis()), vec3(1.0f, 0.0f, 0.0f));
    modelMatrix = hierarchyModelMatrix * lowerarmModelMatrix;
    shaderProgram.setWorldMatrix(modelMatrix);
    glDrawArrays(renderingMode, 0, 36);

    // Model and draw hand
    glBindVertexArray(vaoArm);
    mat4 handModelMatrix = translate(mat4(1.0f), vec3(0.0f, 0.5f,  0.0f)) * scale(mat4(1.0f), vec3(1.0f, 1.0f, 0.7f));
    hierarchyModelMatrix = hierarchyModelMatrix * translate(mat4(1.0f), vec3(0.0f, 3.0f, 0.0f)) * rotate(mat4(1.0f), radians(this->getModelHandRotationZAxis()), vec3(0.0f, 0.0f, 1.0f)) * rotate(mat4(1.0f), radians(this->getModelHandRotationYAxis()), vec3(0.0f, 1.0f, 0.0f)) * rotate(mat4(1.0f), radians(this->getModelHandRotationXAxis()), vec3(1.0f, 0.0f, 0.0f));
    modelMatrix = hierarchyModelMatrix * handModelMatrix;
    shaderProgram.setWorldMatrix(modelMatrix);
    glDrawArrays(renderingMode, 0, 36);

    // Model and draw tennis racket
    // Tennis racket handle
    glBindVertexArray(vaoRacketFrameRed);
    mat4 racketHandleModelMatrix = translate(mat4(1.0f), vec3(0.0f, 1.25f, 0.0f)) * scale(mat4(1.0f), vec3(0.3f, 2.5f, 0.3f));
    hierarchyModelMatrix = hierarchyModelMatrix * translate(mat4(1.0f), vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = hierarchyModelMatrix * racketHandleModelMatrix;
    shaderProgram.setWorldMatrix(modelMatrix);
    glDrawArrays(renderingMode, 0, 36);

    // Tennis racket bottom-left
    glBindVertexArray(vaoRacketFrameGrey);
    mat4 racketBottomLeftModelMatrix = translate(mat4(1.0f), vec3((-1.5f + 0.3f) * cos(45.0f), 2.8f, 0.0f)) * rotate(mat4(1.0f), radians(45.0f), vec3(0.0f, 0.0f, 1.0f)) * scale(mat4(1.0f), vec3(0.2f, 1.5f, 0.2f));
    modelMatrix = hierarchyModelMatrix * racketBottomLeftModelMatrix;
    shaderProgram.setWorldMatrix(modelMatrix);
    glDrawArrays(renderingMode, 0, 36);

    // Tennis racket bottom-right
    glBindVertexArray(vaoRacketFrameGrey);
    mat4 racketBottomRightModelMatrix = translate(mat4(1.0f), vec3((1.5f - 0.3f) * cos(45.0f), 2.8f, 0.0f)) * rotate(mat4(1.0f), radians(-45.0f), vec3(0.0f, 0.0f, 1.0f)) * scale(mat4(1.0f), vec3(0.2f, 1.5f, 0.2f));
    modelMatrix = hierarchyModelMatrix * racketBottomRightModelMatrix;
    shaderProgram.setWorldMatrix(modelMatrix);
    glDrawArrays(renderingMode, 0, 36);

    // Tennis racket bottom-brace
    glBindVertexArray(vaoRacketFrameRed);
    mat4 racketBottomBraceModelMatrix = translate(mat4(1.0f), vec3(0.0f, 2.9f, 0.0f)) * scale(mat4(1.0f), vec3(1.3f, 0.15f, 0.15f));
    modelMatrix = hierarchyModelMatrix * racketBottomBraceModelMatrix;
    shaderProgram.setWorldMatrix(modelMatrix);
    glDrawArrays(renderingMode, 0, 36);

    // Tennis racket left
    glBindVertexArray(vaoRacketFrameRed);
    mat4 racketLeftModelMatrix = translate(mat4(1.0f), vec3(-1.5f * cos(45.0f) - 0.3f, 2.8f + 1.7f, 0.0f)) * scale(mat4(1.0f), vec3(0.2f, 2.5f, 0.2f));
    modelMatrix = hierarchyModelMatrix * racketLeftModelMatrix;
    shaderProgram.setWorldMatrix(modelMatrix);
    glDrawArrays(renderingMode, 0, 36);

    // Tennis racket right
    glBindVertexArray(vaoRacketFrameRed);
    mat4 racketRightModelMatrix = translate(mat4(1.0f), vec3(1.5f * cos(45.0f) + 0.3f, 2.8f + 1.7f, 0.0f)) * scale(mat4(1.0f), vec3(0.2f, 2.5f, 0.2f));
    modelMatrix = hierarchyModelMatrix * racketRightModelMatrix;
    shaderProgram.setWorldMatrix(modelMatrix);
    glDrawArrays(renderingMode, 0, 36);

    // Tennis racket top left lower
    glBindVertexArray(vaoRacketFrameGrey);
    mat4 racketTopLeftLowerModelMatrix = translate(mat4(1.0f), vec3(-1.0f, 2.8f + 1.7f + 1.35f, 0.0f)) * rotate(mat4(1.0f), radians(-40.0f), vec3(0.0f, 0.0f, 1.0f)) * scale(mat4(1.0f), vec3(0.2f, 0.4f, 0.2f));
    modelMatrix = hierarchyModelMatrix * racketTopLeftLowerModelMatrix;
    shaderProgram.setWorldMatrix(modelMatrix);
    glDrawArrays(renderingMode, 0, 36);

    // Tennis racket top right lower
    glBindVertexArray(vaoRacketFrameGrey);
    mat4 racketTopRightLowerModelMatrix = translate(mat4(1.0f), vec3(1.0f, 2.8f + 1.7f + 1.35f, 0.0f)) * rotate(mat4(1.0f), radians(40.0f), vec3(0.0f, 0.0f, 1.0f)) * scale(mat4(1.0f), vec3(0.2f, 0.4f, 0.2f));
    modelMatrix = hierarchyModelMatrix * racketTopRightLowerModelMatrix;
    shaderProgram.setWorldMatrix(modelMatrix);
    glDrawArrays(renderingMode, 0, 36);

    // Tennis racket top left upper
    glBindVertexArray(vaoRacketFrameRed);
    mat4 racketTopLeftUpperModelMatrix = translate(mat4(1.0f), vec3(-0.7f, 2.8f + 1.7f + 1.35f + 0.25f, 0.0f)) * rotate(mat4(1.0f), radians(-65.0f), vec3(0.0f, 0.0f, 1.0f)) * scale(mat4(1.0f), vec3(0.2f, 0.4f, 0.2f));
    modelMatrix = hierarchyModelMatrix * racketTopLeftUpperModelMatrix;
    shaderProgram.setWorldMatrix(modelMatrix);
    glDrawArrays(renderingMode, 0, 36);

    // Tennis racket top right upper
    glBindVertexArray(vaoRacketFrameRed);
    mat4 racketTopRightUpperModelMatrix = translate(mat4(1.0f), vec3(0.7f, 2.8f + 1.7f + 1.35f + 0.25f, 0.0f)) * rotate(mat4(1.0f), radians(65.0f), vec3(0.0f, 0.0f, 1.0f)) * scale(mat4(1.0f), vec3(0.2f, 0.4f, 0.2f));
    modelMatrix = hierarchyModelMatrix * racketTopRightUpperModelMatrix;
    shaderProgram.setWorldMatrix(modelMatrix);
    glDrawArrays(renderingMode, 0, 36);

    // Tennis racket top
    glBindVertexArray(vaoRacketFrameGrey);
    mat4 racketTopModelMatrix = translate(mat4(1.0f), vec3(0.0f, 2.8f + 1.7f + 1.35f + 0.25f + 0.1f, 0.0f)) * scale(mat4(1.0f), vec3(1.1f, 0.2f, 0.2f));
    modelMatrix = hierarchyModelMatrix * racketTopModelMatrix;
    shaderProgram.setWorldMatrix(modelMatrix);
    glDrawArrays(renderingMode, 0, 36);

    // Tennis racket strings
    glBindVertexArray(vaoRacketString);
    mat4 racketStringMatrix;
    for (int i=0; i<7; ++i) {
        racketStringMatrix = translate(mat4(1.0f), vec3(-0.8f + i * 0.27f, 3.0f + 1.55f, 0.0f)) * scale(mat4(1.0f), vec3(0.06f, 3.2f, 0.06f));
        modelMatrix = hierarchyModelMatrix * racketStringMatrix;
        shaderProgram.setWorldMatrix(modelMatrix);
        glDrawArrays(renderingMode, 0, 36);
    }
    for (int i=0; i<11; ++i) {
        racketStringMatrix = translate(mat4(1.0f), vec3(0.0f, -1.4f + i * 0.27f + 3.0f + 1.55f, 0.0f)) * scale(mat4(1.0f), vec3(2.2f, 0.06f, 0.06f));
        modelMatrix = hierarchyModelMatrix * racketStringMatrix;
        shaderProgram.setWorldMatrix(modelMatrix);
        glDrawArrays(renderingMode, 0, 36);
    }
}