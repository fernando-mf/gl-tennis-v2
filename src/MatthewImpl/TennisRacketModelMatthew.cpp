#include "TennisRacketModelMatthew.h"
#include "../TennisRacketModel.h"
#include "../Cube.h"
#include "SphereMatthew.h"

TennisRacketModelMatthew::TennisRacketModelMatthew(const vec3 &position) : TennisRacketModel(position) {
    Cube upperArmArray = Cube(vec3(0.961f, 0.961f, 0.863f));
    Cube racketArray =  Cube(vec3(1.0f, 0.0f, 0.0f));

    upperArmAO = upperArmArray.getVertexBufferObject();
    racketAO = racketArray.getVertexBufferObject();
}

void TennisRacketModelMatthew::draw(mat4 hierarchyModelMatrix, ShaderProgram shaderProgram, GLuint renderingMode) {

    mat4 worldMatrix;
    mat4 groupMatrix = hierarchyModelMatrix;

        //generate sphere
    unsigned int indexCounter;
    int matthewSphereVAO = createSphereObject(&indexCounter);

    // set up texture for tennis ball
//    shaderProgram.setWorldMatrix(worldMatrix);
//    glActiveTexture(GL_TEXTURE1);
//    GLuint textureLocation = glGetUniformLocation(shaderProgram.id, "textureSampler");
//    glBindTexture(GL_TEXTURE_2D, 0);
//    glUniform1i(textureLocation, 1);

    glBindVertexArray(matthewSphereVAO);
    mat4 partMatrix = translate(mat4(1.0f), vec3(1.0f, 7.0f, -2.0f)) *
                        scale(mat4(1.0f), vec3(1.0f, 1.0f, 1.0f));
    worldMatrix = groupMatrix * partMatrix;
    shaderProgram.setWorldMatrix(worldMatrix);
    glDrawElements(GL_TRIANGLE_STRIP, indexCounter, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // upper arm
    glBindVertexArray(upperArmAO);
    partMatrix = translate(mat4(1.0f), vec3(0.0f, 1.5f, 0.0f)) * 
                        rotate(mat4(1.0f), radians(45.0f), vec3(0.0f, 0.0f, 1.0f)) * 
                        scale(mat4(1.0f), vec3(3.0f, 0.5f, 0.5f));
    worldMatrix = groupMatrix * partMatrix;
    shaderProgram.setWorldMatrix(worldMatrix);
    glDrawArrays(renderingMode, 0, 36);

    //lower arm
    glBindVertexArray(upperArmAO);
    partMatrix = translate(mat4(1.0f), vec3(0.0f, 1.5f,  0.0f)) * 
                    scale(mat4(1.0f), vec3(0.5f, 3.0f, 0.5f));
    groupMatrix = groupMatrix * translate(mat4(1.0f), vec3(1.0f, 2.37f, 0.0f)) * 
                    rotate(mat4(1.0f), radians(this->getModelLowerarmRotationZAxis()), vec3(0.0f, 0.0f, 1.0f)) * 
                    rotate(mat4(1.0f), radians(this->getModelLowerarmRotationYAxis()), vec3(0.0f, 1.0f, 0.0f)) * 
                    rotate(mat4(1.0f), radians(this->getModelLowerarmRotationXAxis()), vec3(1.0f, 0.0f, 0.0f));
    worldMatrix = groupMatrix * partMatrix;
    shaderProgram.setWorldMatrix(worldMatrix);
    glDrawArrays(renderingMode, 0, 36);

    // racket bottom
    glBindVertexArray(racketAO);
    partMatrix = translate(mat4(1.0f), vec3(0.0f, 2.9f, 0.0f)) * 
                    scale(mat4(1.0f), vec3(2.6f, 0.55f, 0.55f));
    worldMatrix = groupMatrix * partMatrix;
    shaderProgram.setWorldMatrix(worldMatrix);
    glDrawArrays(renderingMode, 0, 36);

    // racket left
    glBindVertexArray(racketAO);
    partMatrix = translate(mat4(1.0f), vec3(-1.3f, 4.5, 0.0f)) * 
                    scale(mat4(1.0f), vec3(0.55f, 2.9f, 0.55f));
    worldMatrix = groupMatrix * partMatrix;
    shaderProgram.setWorldMatrix(worldMatrix);
    glDrawArrays(renderingMode, 0, 36);

    // racket right
    glBindVertexArray(racketAO);
    partMatrix = translate(mat4(1.0f), vec3(1.3f, 4.5f, 0.0f)) * 
                        scale(mat4(1.0f), vec3(0.55f, 2.9f, 0.55f));
    worldMatrix = groupMatrix * partMatrix;
    shaderProgram.setWorldMatrix(worldMatrix);
    glDrawArrays(renderingMode, 0, 36);

    // racket top
    glBindVertexArray(racketAO);
    partMatrix = translate(mat4(1.0f), vec3(0.0f, 6.2f, 0.0f)) * 
                    scale(mat4(1.0f), vec3(2.6f, 0.55f, 0.55f));
    worldMatrix = groupMatrix * partMatrix;
    shaderProgram.setWorldMatrix(worldMatrix);
    glDrawArrays(renderingMode, 0, 36);
}