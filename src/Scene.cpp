#include "Scene.h"

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include "JonathanImpl/TennisRacketModelJonathan.h"
#include "MatthewImpl/TennisRacketModelMatthew.h"
#include "KiranImpl/TennisRacketModelKiranF.h"
#include "FernandoImpl/TennisRacketModelFernando.h"

using namespace glm;

Scene::Scene() {
    /* VERTEX ARRAY OBJECT GEOMETRIES */
    Cube cubeGround = Cube(vec3(1.0f, 1.0f, 0.0f));
    Cube cubeXAxis = Cube(vec3(1.0f, 0.0f, 0.0f));
    Cube cubeYAxis = Cube(vec3(0.0f, 1.0f, 0.0f));
    Cube cubeZAxis = Cube(vec3(0.0f, 0.0f, 1.0f));
    Cube cubeNetPost = Cube(vec3(26.0f / 255.0f, 97.0f / 255.0f, 50.0f / 255.0f));
    Cube cubeNetTop = Cube(vec3(255.0f, 255.0f, 255.0f));
    Cube cubeNetTwine = Cube(vec3(0.0f, 0.0f, 0.0f));

    // Define and upload cube geometry to the GPU
    vaoGround = cubeGround.getVertexBufferObject();
    vaoXAxis = cubeXAxis.getVertexBufferObject();
    vaoYAxis = cubeYAxis.getVertexBufferObject();
    vaoZAxis = cubeZAxis.getVertexBufferObject();
    vaoNetPost = cubeNetPost.getVertexBufferObject();
    vaoNetTop = cubeNetTop.getVertexBufferObject();
    vaoNetTwine = cubeNetTwine.getVertexBufferObject();

    /* TENNIS RACKET MODEL INSTANTIATION */
    // Jonathan
    models.push_back(new TennisRacketModelJonathan(vec3(-12.0f, 8.0f, 0.0f)));
    tennisBallJonathan = TennisBallModel();
    // Matthew
    models.push_back(new TennisRacketModelMatthew(vec3(-4.0f, 8.0f, 0.0f)));
    // Fernando
    models.push_back(new TennisRacketModelFernando(vec3(4.0f, 8.0f, 0.0f)));
    tennisBallFernando = TennisBallFernando();
    // Kiran
    models.push_back(new TennisRacketModelKiranF(vec3(12.0f, 8.0f, 0.0f)));

    renderingMode = GL_TRIANGLES; // default model rendering mode of GL_TRIANGLES

    groundTexture = Texture("./assets/textures/red_clay.jpg");
}

void Scene::draw(ShaderProgram shaderProgram) {
    /* HIERARCHICAL MODELLING */
    // This is the base/foundation matrix for the world
    mat4 worldMatrix = rotate(mat4(1.0f), radians(worldRotationZAxis), vec3(0.0f, 0.0f, 1.0f)) *
                       rotate(mat4(1.0f), radians(worldRotationYAxis), vec3(0.0f, 1.0f, 0.0f)) *
                       rotate(mat4(1.0f), radians(worldRotationXAxis), vec3(1.0f, 0.0f, 0.0f));

    // Model and draw 78x36 ground
    glBindVertexArray(vaoGround);
    shaderProgram.useTextures();
    groundTexture.use();
    mat4 groundWorldMatrix =
            translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.0f)) * scale(mat4(1.0f), vec3(36.0f, 0.02f, 78.0f));
    groundWorldMatrix = worldMatrix * groundWorldMatrix;
    shaderProgram.setWorldMatrix(groundWorldMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    shaderProgram.useColors();

    // Model and draw coordinate axes
    mat4 axisWorldMatrix;

    glBindVertexArray(vaoXAxis);
    axisWorldMatrix = translate(mat4(1.0f), vec3(2.5f, 0.0f, 0.0f)) * scale(mat4(1.0f), vec3(5.0f, 0.1f, 0.1f));
    axisWorldMatrix = worldMatrix * axisWorldMatrix;
    shaderProgram.setWorldMatrix(axisWorldMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(vaoYAxis);
    axisWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 2.5f, 0.0f)) * scale(mat4(1.0f), vec3(0.1f, 5.0f, 0.1f));
    axisWorldMatrix = worldMatrix * axisWorldMatrix;
    shaderProgram.setWorldMatrix(axisWorldMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(vaoZAxis);
    axisWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 0.0f, 2.5f)) * scale(mat4(1.0f), vec3(0.1f, 0.1f, 5.0f));
    axisWorldMatrix = worldMatrix * axisWorldMatrix;
    shaderProgram.setWorldMatrix(axisWorldMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Model and draw tennis net
    // Tennis net posts
    mat4 netPostModelMatrix;

    glBindVertexArray(vaoNetPost);
    netPostModelMatrix = translate(mat4(1.0f), vec3(-16.0f, 3.0f, 0.0f)) * scale(mat4(1.0f), vec3(1.0f, 6.0f, 1.0f));
    netPostModelMatrix = worldMatrix * netPostModelMatrix;
    shaderProgram.setWorldMatrix(netPostModelMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(vaoNetPost);
    netPostModelMatrix = translate(mat4(1.0f), vec3(16.0f, 3.0f, 0.0f)) * scale(mat4(1.0f), vec3(1.0f, 6.0f, 1.0f));
    netPostModelMatrix = worldMatrix * netPostModelMatrix;
    shaderProgram.setWorldMatrix(netPostModelMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Tennis net top
    glBindVertexArray(vaoNetTop);
    mat4 netTopModelMatrix = translate(mat4(1.0f), vec3(0.0f, -0.35f + 6.0f, 0.0f)) *
                             scale(mat4(1.0f), vec3(32.0f - 2.0f * 0.5f, 0.7f, 0.3f));
    netTopModelMatrix = worldMatrix * netTopModelMatrix;
    shaderProgram.setWorldMatrix(netTopModelMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Tennis net twine
    glBindVertexArray(vaoNetTwine);
    mat4 netTwineModelMatrix;

    for (int i = 0; i < 13; ++i) {
        netTwineModelMatrix = translate(mat4(1.0f), vec3(0.0f, 0.2f + i * 0.4f, 0.0f)) *
                              scale(mat4(1.0f), vec3(32.0f - 2.0f * 0.5f, 0.04f, 0.04f));
        netTwineModelMatrix = worldMatrix * netTwineModelMatrix;
        shaderProgram.setWorldMatrix(netTwineModelMatrix);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    for (int i = 0; i < 77; ++i) {
        netTwineModelMatrix =
                translate(mat4(1.0f), vec3(-16.0f + 0.5f + 0.2f + i * 0.4f, (6.0f - 0.7f - 0.1f) / 2, 0.0f)) *
                scale(mat4(1.0f), vec3(0.04f, 6.0f - 0.7f - 2.0f * 0.2f - 0.1f, 0.04f));
        netTwineModelMatrix = worldMatrix * netTwineModelMatrix;
        shaderProgram.setWorldMatrix(netTwineModelMatrix);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    /* INDIVIDUAL MODELS AND DRAWING */
    // Create hierarchy matrices, one for each model
    mat4 hierarchyModelMatrix[4];
    for (int i = 0; i < 4; ++i) {
        hierarchyModelMatrix[i] = translate(mat4(1.0f), models.at(i)->getModelPosition()) *
                                  rotate(mat4(1.0f), radians(models.at(i)->getModelRotationZAxis()),
                                         vec3(0.0f, 0.0f, 1.0f)) *
                                  rotate(mat4(1.0f), radians(models.at(i)->getModelRotationYAxis()),
                                         vec3(0.0f, 1.0f, 0.0f)) *
                                  rotate(mat4(1.0f), radians(models.at(i)->getModelRotationXAxis()),
                                         vec3(1.0f, 0.0f, 0.0f)) * scale(mat4(1.0f), models.at(i)->getModelScale());
        hierarchyModelMatrix[i] = worldMatrix * hierarchyModelMatrix[i];
    }

    // Draw each individual member's tennis racket + ball model
    // Jonathan
    models.at(0)->draw(hierarchyModelMatrix[0], shaderProgram, renderingMode);
    tennisBallJonathan.draw(hierarchyModelMatrix[0], shaderProgram, renderingMode);
    // Matthew
    models.at(1)->draw(hierarchyModelMatrix[1], shaderProgram, renderingMode);
    // Fernando
    models.at(2)->draw(hierarchyModelMatrix[2], shaderProgram, renderingMode);
    tennisBallFernando.draw(hierarchyModelMatrix[2], shaderProgram, renderingMode);
    // Kiran
    models.at(3)->draw(hierarchyModelMatrix[3], shaderProgram, renderingMode);

    glBindVertexArray(0);
}

void Scene::setRenderingMode(GLuint renderingMode) {
    this->renderingMode = renderingMode;
}