//
// COMP 371 Programming Assignment 2
// By Jonathan Hubermann #40125401
//

#include <iostream>
#include <list>
#include <random>

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler
#include <GLFW/glfw3.h> // cross-platform interface for creating a graphical context, initializing OpenGL and binding inputs

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // include this to create transformation matrices
#include <glm/common.hpp>

#include "ShaderProgram.h"
#include "Texture.h"
#include "Cube.h"
#include "TennisRacketModel.h"
#include "JonathanImpl/TennisRacketModelJonathan.h"
#include "JonathanImpl/TennisBallModel.h"
#include "MatthewImpl/TennisRacketModelMatthew.h"
#include "KiranImpl/TennisRacketModelKiranF.h"
#include "FernandoImpl/TennisRacketModelFernando.h"
#include "FernandoImpl/TennisBallFernando.h"

using namespace glm;
using namespace std;

int main(int argc, char*argv[]) {
    /* SETUP */
    // Initialize GLFW and OpenGL version
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Make sure Double Buffering support is enabled
    glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);

    // Create Window and rendering context using GLFW, resolution is 1024x768
    int windowWidth = 1024;
    int windowHeight = 768;
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Comp371 - Assignment2", NULL, NULL);
    if (window == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to create GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Other OpenGL states to set once
    // Enable Backface culling
    glEnable(GL_CULL_FACE);

    // Enable Depth Test
    glEnable(GL_DEPTH_TEST);

    // Turquoise background color
    glClearColor(43.0f/255.0f, 77.0f/255.0f, 76.0f/255.0f, 1.0f);

    /* TEXTURES */
    bool isTexturesEnabled = true;
    Texture groundTexture = Texture("./assets/textures/red_clay.jpg");

    /* SHADERS */
    // Instantiate shader programs
    ShaderProgram defaultShaderProgram = ShaderProgram("./assets/shaders/texture_vertex_shader.glsl", "./assets/shaders/texture_fragment_shader.glsl");
    defaultShaderProgram.initializeTextures();

    vec3 lightPos(0.0f, 30.0f, -7.5f);
    GLuint lightLocation = glGetUniformLocation(defaultShaderProgram.id, "lightPos");
    glUniform3fv(lightLocation, 1, &lightPos[0]);

    /* CAMERA */
    // Camera parameters for view transform
    vec3 cameraPosition(0.0f, 15.0f, 30.0f);
    vec3 cameraLookAt(0.0f, 0.0f, -1.0f);
    vec3 cameraUp(0.0f, 1.0f, 0.0f);

    // Other camera parameters
    float cameraHorizontalAngle = 90.0f;
    float cameraVerticalAngle = 0.0f;

    float cameraPanRate = 20.0f;
    float cameraTiltRate = 20.0f;
    float cameraZoomRate = 0.5f;

    /* VIEW SETUP */
    // Set initial view matrix
    // eye, center, up
    mat4 viewMatrix = lookAt(cameraPosition, cameraPosition + cameraLookAt, cameraUp);
    defaultShaderProgram.setViewMatrix(viewMatrix);

    /* VERTEX ARRAY OBJECT GEOMETRIES */
    Cube cubeGround = Cube(vec3(1.0f, 1.0f, 0.0f));
    Cube cubeXAxis = Cube(vec3(1.0f, 0.0f, 0.0f));
    Cube cubeYAxis = Cube(vec3(0.0f, 1.0f, 0.0f));
    Cube cubeZAxis = Cube(vec3(0.0f, 0.0f, 1.0f));
    Cube cubeNetPost = Cube(vec3(26.0f/255.0f, 97.0f/255.0f, 50.0f/255.0f));
    Cube cubeNetTop = Cube(vec3(255.0f, 255.0f, 255.0f));
    Cube cubeNetTwine = Cube(vec3(0.0f, 0.0f, 0.0f));

    // Define and upload cube geometry to the GPU
    GLuint vaoGround = cubeGround.getVertexBufferObject();
    GLuint vaoXAxis = cubeXAxis.getVertexBufferObject();
    GLuint vaoYAxis = cubeYAxis.getVertexBufferObject();
    GLuint vaoZAxis = cubeZAxis.getVertexBufferObject();
    GLuint vaoNetPost = cubeNetPost.getVertexBufferObject();
    GLuint vaoNetTop = cubeNetTop.getVertexBufferObject();
    GLuint vaoNetTwine = cubeNetTwine.getVertexBufferObject();

    /* TIMING */
    // For frame time
    float lastFrameTime = glfwGetTime();

    /* MOUSE CURSOR */
    double lastMousePosX, lastMousePosY;
    glfwGetCursorPos(window, &lastMousePosX, &lastMousePosY);

    /* WORLD CONTROL VARIABLES */
    float worldRotationXAxis = 0.0f; // default X-rotation of 0
    float worldRotationYAxis = 0.0f; // default Y-rotation of 0
    float worldRotationZAxis = 0.0f; // default Z-rotation of 0
    float worldRotationRate = 15.0f;

    /* TENNIS RACKET MODEL INSTANTIATION */
    vector<TennisRacketModel*> models;
    // Jonathan
    models.push_back(new TennisRacketModelJonathan(vec3(-12.0f, 8.0f, 0.0f)));
    TennisBallModel tennisBallJonathan = TennisBallModel();
    // Matthew
    models.push_back(new TennisRacketModelMatthew(vec3(-4.0f, 8.0f, 0.0f)));
    // Fernando
    models.push_back(new TennisRacketModelFernando(vec3(4.0f, 8.0f, 0.0f)));
    TennisBallFernando tennisBallFernando = TennisBallFernando();
    // Kiran
    models.push_back(new TennisRacketModelKiranF(vec3(12.0f, 8.0f, 0.0f)));

    int modelSelection = 1;

    float controlTimer = 0.0f;

    /* CAMERA CONTROL VARIABLES */
    float fieldOfView = 60.0f / 360.0f * 2 * M_PI; // default field of view of 60 deg
    float minimumFieldOfView = 5.0f / 360.0f * 2 * M_PI;
    float maximumFieldOfView = 110.0f / 360.0f * 2 * M_PI;
    GLuint renderingMode = GL_TRIANGLES; // default model rendering mode of GL_TRIANGLES

    // Entering Main Loop
    while(!glfwWindowShouldClose(window)) {

        /* TIMING */
        // Frame time calculation
        float dt = glfwGetTime() - lastFrameTime;
        lastFrameTime += dt;

        /* RESET */
        // Each frame, reset color of each pixel to glClearColor and clear Depth Buffer Bit as well
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /* PROJECTION SETUP */
        // Update the current window's dimensions
        glfwGetWindowSize(window, &windowWidth, &windowHeight);
        // Set the projection matrix for shader here since it is dependent on user input
        // FoV (deg), aspect ratio, near and far (near>0)
        mat4 projectionMatrix = perspective(fieldOfView, (float) windowWidth / (float) windowHeight, 0.01f, 100.0f);
        defaultShaderProgram.setProjectionMatrix(projectionMatrix);

        /* HIERARCHICAL MODELLING */
        // This is the base/foundation matrix for the world
        mat4 worldMatrix = rotate(mat4(1.0f), radians(worldRotationZAxis), vec3(0.0f, 0.0f, 1.0f)) * rotate(mat4(1.0f), radians(worldRotationYAxis), vec3(0.0f, 1.0f, 0.0f)) * rotate(mat4(1.0f), radians(worldRotationXAxis), vec3(1.0f, 0.0f, 0.0f));

        // Model and draw 78x36 ground
        glBindVertexArray(vaoGround);
        defaultShaderProgram.useTextures();
        groundTexture.use();
        mat4 groundWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.0f)) * scale(mat4(1.0f), vec3(36.0f, 0.02f, 78.0f));
        groundWorldMatrix = worldMatrix * groundWorldMatrix;
        defaultShaderProgram.setWorldMatrix(groundWorldMatrix);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        defaultShaderProgram.useColors();

        // Model and draw coordinate axes
        mat4 axisWorldMatrix;

        glBindVertexArray(vaoXAxis);
        axisWorldMatrix = translate(mat4(1.0f), vec3(2.5f, 0.0f, 0.0f)) * scale(mat4(1.0f), vec3(5.0f, 0.1f, 0.1f));
        axisWorldMatrix = worldMatrix * axisWorldMatrix;
        defaultShaderProgram.setWorldMatrix(axisWorldMatrix);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(vaoYAxis);
        axisWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 2.5f, 0.0f)) * scale(mat4(1.0f), vec3(0.1f, 5.0f, 0.1f));
        axisWorldMatrix = worldMatrix * axisWorldMatrix;
        defaultShaderProgram.setWorldMatrix(axisWorldMatrix);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(vaoZAxis);
        axisWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 0.0f, 2.5f)) * scale(mat4(1.0f), vec3(0.1f, 0.1f, 5.0f));
        axisWorldMatrix = worldMatrix * axisWorldMatrix;
        defaultShaderProgram.setWorldMatrix(axisWorldMatrix);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Model and draw tennis net
        // Tennis net posts
        mat4 netPostModelMatrix;

        glBindVertexArray(vaoNetPost);
        netPostModelMatrix = translate(mat4(1.0f), vec3(-16.0f, 3.0f, 0.0f)) * scale(mat4(1.0f), vec3(1.0f, 6.0f, 1.0f));
        netPostModelMatrix = worldMatrix * netPostModelMatrix;
        defaultShaderProgram.setWorldMatrix(netPostModelMatrix);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(vaoNetPost);
        netPostModelMatrix = translate(mat4(1.0f), vec3(16.0f, 3.0f, 0.0f)) * scale(mat4(1.0f), vec3(1.0f, 6.0f, 1.0f));
        netPostModelMatrix = worldMatrix * netPostModelMatrix;
        defaultShaderProgram.setWorldMatrix(netPostModelMatrix);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Tennis net top
        glBindVertexArray(vaoNetTop);
        mat4 netTopModelMatrix = translate(mat4(1.0f), vec3(0.0f, -0.35f + 6.0f, 0.0f)) * scale(mat4(1.0f), vec3(32.0f - 2.0f * 0.5f, 0.7f, 0.3f));
        netTopModelMatrix = worldMatrix * netTopModelMatrix;
        defaultShaderProgram.setWorldMatrix(netTopModelMatrix);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Tennis net twine
        glBindVertexArray(vaoNetTwine);
        mat4 netTwineModelMatrix;

        for (int i=0; i<13; ++i) {
            netTwineModelMatrix = translate(mat4(1.0f), vec3(0.0f, 0.2f + i * 0.4f, 0.0f)) * scale(mat4(1.0f), vec3(32.0f - 2.0f * 0.5f, 0.04f, 0.04f));
            netTwineModelMatrix = worldMatrix * netTwineModelMatrix;
            defaultShaderProgram.setWorldMatrix(netTwineModelMatrix);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        for (int i=0; i<77; ++i) {
            netTwineModelMatrix = translate(mat4(1.0f), vec3(-16.0f + 0.5f + 0.2f + i * 0.4f, (6.0f - 0.7f - 0.1f) / 2, 0.0f)) * scale(mat4(1.0f), vec3(0.04f, 6.0f - 0.7f - 2.0f * 0.2f - 0.1f, 0.04f));
            netTwineModelMatrix = worldMatrix * netTwineModelMatrix;
            defaultShaderProgram.setWorldMatrix(netTwineModelMatrix);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        /* INDIVIDUAL MODELS AND DRAWING */
        // Create hierarchy matrices, one for each model
        mat4 hierarchyModelMatrix[4];
        for (int i=0; i<4; ++i) {
            hierarchyModelMatrix[i] = translate(mat4(1.0f), models.at(i)->getModelPosition()) * rotate(mat4(1.0f), radians(models.at(i)->getModelRotationZAxis()), vec3(0.0f, 0.0f, 1.0f)) * rotate(mat4(1.0f), radians(models.at(i)->getModelRotationYAxis()), vec3(0.0f, 1.0f, 0.0f)) * rotate(mat4(1.0f), radians(models.at(i)->getModelRotationXAxis()), vec3(1.0f, 0.0f, 0.0f)) * scale(mat4(1.0f), models.at(i)->getModelScale());
            hierarchyModelMatrix[i] = worldMatrix * hierarchyModelMatrix[i];
        }

        // Draw each individual member's tennis racket + ball model
        // Jonathan
        models.at(0)->draw(hierarchyModelMatrix[0], defaultShaderProgram, renderingMode);
        tennisBallJonathan.draw(hierarchyModelMatrix[0], defaultShaderProgram, renderingMode);
        // Matthew
        models.at(1)->draw(hierarchyModelMatrix[1], defaultShaderProgram, renderingMode);
        // Fernando
        models.at(2)->draw(hierarchyModelMatrix[2], defaultShaderProgram, renderingMode);
        tennisBallFernando.draw(hierarchyModelMatrix[2], defaultShaderProgram, renderingMode);
        // Kiran
        models.at(3)->draw(hierarchyModelMatrix[3], defaultShaderProgram, renderingMode);

        // End Frame
        glfwSwapBuffers(window);
        glfwPollEvents();

        /* USER INPUT */
        bool isShiftPressed = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS;
        bool isControlPressed = glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS;

        // Exits the program
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        // Controls the current model selected
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
            modelSelection = 0;
        }
        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
            modelSelection = 1;
        }
        if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
            modelSelection = 2;
        }
        if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
            modelSelection = 3;
        }

        // Re-positions model at a random location on the grid
        // Acknowledgment that the PRNG was based on online examples for true random number generation in C++
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            if (glfwGetTime() - controlTimer >= 0.1f) {
                random_device rd;
                mt19937 gen(rd());
                uniform_int_distribution<> distr(-50, 50);
                models.at(modelSelection)->setModelPosition(vec3(distr(gen), 0.0f, distr(gen)));
                controlTimer = glfwGetTime();
            }
        }

        // Incrementally scales the model up (larger)
        float modelScaleDelta = models.at(modelSelection)->getModelScaleRate() * dt;
        if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
            models.at(modelSelection)->setModelScale(models.at(modelSelection)->getModelScale() + vec3(modelScaleDelta, modelScaleDelta, modelScaleDelta));
        }
        // Incrementally scales the model down (smaller)
        if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
            models.at(modelSelection)->setModelScale(models.at(modelSelection)->getModelScale() - vec3(modelScaleDelta, modelScaleDelta, modelScaleDelta));
        }

        // Controls the model position and rotation
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            if (isShiftPressed) {
                // Displaces the whole model negatively along the X-axis
                float modelDisplacement = -1 * models.at(modelSelection)->getModelDisplacementRate() * dt;
                models.at(modelSelection)->setModelPosition(models.at(modelSelection)->getModelPosition() + vec3(modelDisplacement, 0.0f, 0.0f));
            } else if (isControlPressed) {
                // Rotates the lower arm in the model negatively around the Y-axis
                float modelLowerarmRotationDelta = -1 * models.at(modelSelection)->getModelRotationRate() * dt;
                models.at(modelSelection)->setModelLowerarmRotationYAxis(models.at(modelSelection)->getModelLowerarmRotationYAxis() + modelLowerarmRotationDelta);
            } else if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
                // Rotates the hand in the model negatively around the Y-axis
                float modelHandRotationDelta = -1 * models.at(modelSelection)->getModelRotationRate() * dt;
                models.at(modelSelection)->setModelHandRotationYAxis(models.at(modelSelection)->getModelHandRotationYAxis() + modelHandRotationDelta);
            } else {
                // Rotates the whole model negatively around the Y-axis
                float modelRotationDelta = -1 * models.at(modelSelection)->getModelRotationRate() * dt;
                models.at(modelSelection)->setModelRotationYAxis(models.at(modelSelection)->getModelRotationYAxis() + modelRotationDelta);
            }
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            if (isShiftPressed) {
                // Displaces the whole model positively along the X-axis
                float modelDisplacement = 1 * models.at(modelSelection)->getModelDisplacementRate() * dt;
                models.at(modelSelection)->setModelPosition(models.at(modelSelection)->getModelPosition() + vec3(modelDisplacement, 0.0f, 0.0f));
            } else if (isControlPressed) {
                // Rotates the lower arm in the model positively around the Y-axis
                float modelLowerarmRotationDelta = 1 * models.at(modelSelection)->getModelRotationRate() * dt;
                models.at(modelSelection)->setModelLowerarmRotationYAxis(models.at(modelSelection)->getModelLowerarmRotationYAxis() + modelLowerarmRotationDelta);
                // Rotates the hand in the model positively around the Y-axis
            } else if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
                float modelHandRotationDelta = 1 * models.at(modelSelection)->getModelRotationRate() * dt;
                models.at(modelSelection)->setModelHandRotationYAxis(models.at(modelSelection)->getModelHandRotationYAxis() + modelHandRotationDelta);
            } else {
                // Rotates the whole model positively around the Y-axis
                float modelRotationDelta = 1 * models.at(modelSelection)->getModelRotationRate() * dt;
                models.at(modelSelection)->setModelRotationYAxis(models.at(modelSelection)->getModelRotationYAxis() + modelRotationDelta);
            }
        }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            if (isShiftPressed) {
                // Displaces the whole model positively along the Y-axis
                float modelDisplacement = 1 * models.at(modelSelection)->getModelDisplacementRate() * dt;
                models.at(modelSelection)->setModelPosition(models.at(modelSelection)->getModelPosition() + vec3(0.0f, modelDisplacement, 0.0f));
            } else if (isControlPressed) {
                // Rotates the lower arm in the model negatively around the X-axis
                float modelLowerarmRotationDelta = -1 * models.at(modelSelection)->getModelRotationRate() * dt;
                models.at(modelSelection)->setModelLowerarmRotationXAxis(models.at(modelSelection)->getModelLowerarmRotationXAxis() + modelLowerarmRotationDelta);
            } else if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
                // Rotates the hand in the model negatively around the X-axis
                float modelHandRotationDelta = -1 * models.at(modelSelection)->getModelRotationRate() * dt;
                models.at(modelSelection)->setModelHandRotationXAxis(models.at(modelSelection)->getModelHandRotationXAxis() + modelHandRotationDelta);
            } else {
                // Rotates the whole model negatively around the X-axis
                float modelRotationDelta = -1 * models.at(modelSelection)->getModelRotationRate() * dt;
                models.at(modelSelection)->setModelRotationXAxis(models.at(modelSelection)->getModelRotationXAxis() + modelRotationDelta);
            }
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            if (isShiftPressed) {
                // Displaces the whole model negatively along the Y-axis
                float modelDisplacement = -1 * models.at(modelSelection)->getModelDisplacementRate() * dt;
                models.at(modelSelection)->setModelPosition(models.at(modelSelection)->getModelPosition() + vec3(0.0f, modelDisplacement, 0.0f));
            } else if (isControlPressed) {
                // Rotates the lower arm in the model positively around the X-axis
                float modelLowerarmRotationDelta = 1 * models.at(modelSelection)->getModelRotationRate() * dt;
                models.at(modelSelection)->setModelLowerarmRotationXAxis(models.at(modelSelection)->getModelLowerarmRotationXAxis() + modelLowerarmRotationDelta);
            } else if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
                // Rotates the hand in the model positively around the X-axis
                float modelHandRotationDelta = 1 * models.at(modelSelection)->getModelRotationRate() * dt;
                models.at(modelSelection)->setModelHandRotationXAxis(models.at(modelSelection)->getModelHandRotationXAxis() + modelHandRotationDelta);
            } else {
                // Rotates the whole model positively around the X-axis
                float modelRotationDelta = 1 * models.at(modelSelection)->getModelRotationRate() * dt;
                models.at(modelSelection)->setModelRotationXAxis(models.at(modelSelection)->getModelRotationXAxis() + modelRotationDelta);
            }
        }
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
            if (isShiftPressed) {
                // Displaces the whole model positively along the Z-axis
                float modelDisplacement = 1 * models.at(modelSelection)->getModelDisplacementRate() * dt;
                models.at(modelSelection)->setModelPosition(models.at(modelSelection)->getModelPosition() + vec3(0.0f, 0.0f, modelDisplacement));
            } else if (isControlPressed) {
                // Rotates the lower arm in the model positively around the Z-axis
                float modelLowerarmRotationDelta = 1 * models.at(modelSelection)->getModelRotationRate() * dt;
                models.at(modelSelection)->setModelLowerarmRotationZAxis(models.at(modelSelection)->getModelLowerarmRotationZAxis() + modelLowerarmRotationDelta);
            } else if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
                // Rotates the hand in the model positively around the Z-axis
                float modelHandRotationDelta = 1 * models.at(modelSelection)->getModelRotationRate() * dt;
                models.at(modelSelection)->setModelHandRotationZAxis(models.at(modelSelection)->getModelHandRotationZAxis() + modelHandRotationDelta);
            } else {
                // Rotates the whole model positively around the Z-axis
                float modelRotationDelta = 1 * models.at(modelSelection)->getModelRotationRate() * dt;
                models.at(modelSelection)->setModelRotationZAxis(models.at(modelSelection)->getModelRotationZAxis() + modelRotationDelta);
            }
        }
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
            if (isShiftPressed) {
                // Displaces the whole model negatively along the Z-axis
                float modelDisplacement = -1 * models.at(modelSelection)->getModelDisplacementRate() * dt;
                models.at(modelSelection)->setModelPosition(models.at(modelSelection)->getModelPosition() + vec3(0.0f, 0.0f, modelDisplacement));
            } else if (isControlPressed) {
                // Rotates the lower arm in the model negatively around the Z-axis
                float modelLowerarmRotationDelta = -1 * models.at(modelSelection)->getModelRotationRate() * dt;
                models.at(modelSelection)->setModelLowerarmRotationZAxis(models.at(modelSelection)->getModelLowerarmRotationZAxis() + modelLowerarmRotationDelta);
            } else if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
                // Rotates the hand in the model negatively around the Z-axis
                float modelHandRotationDelta = -1 * models.at(modelSelection)->getModelRotationRate() * dt;
                models.at(modelSelection)->setModelHandRotationZAxis(models.at(modelSelection)->getModelHandRotationZAxis() + modelHandRotationDelta);
            } else {
                // Rotates the whole model negatively around the Z-axis
                float modelRotationDelta = -1 * models.at(modelSelection)->getModelRotationRate() * dt;
                models.at(modelSelection)->setModelRotationZAxis(models.at(modelSelection)->getModelRotationZAxis() + modelRotationDelta);
            }
        }

        // Resets the model position and rotation to default
        if (glfwGetKey(window, GLFW_KEY_END) == GLFW_PRESS) {
            models.at(0)->setModelPosition(vec3(-12.0f, 8.0f, 0.0f));
            models.at(1)->setModelPosition(vec3(-4.0f, 8.0f, 0.0f));
            models.at(2)->setModelPosition(vec3(4.0f, 8.0f, 0.0f));
            models.at(3)->setModelPosition(vec3(12.0f, 8.0f, 0.0f));
            for (int n=0; n<4; ++n) {
                models.at(n)->setModelRotationZAxis(0.0f);
                models.at(n)->setModelRotationYAxis(0.0f);
                models.at(n)->setModelRotationXAxis(0.0f);
                models.at(n)->setModelLowerarmRotationZAxis(0.0f);
                models.at(n)->setModelLowerarmRotationYAxis(0.0f);
                models.at(n)->setModelLowerarmRotationXAxis(0.0f);
                models.at(n)->setModelHandRotationZAxis(0.0f);
                models.at(n)->setModelHandRotationYAxis(0.0f);
                models.at(n)->setModelHandRotationXAxis(0.0f);
            }
        }

        // Controls the world rotation
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            if (isShiftPressed) {
                float worldRotationDelta = 1 * worldRotationRate * dt;
                worldRotationZAxis += worldRotationDelta;
            } else {
                float worldRotationDelta = -1 * worldRotationRate * dt;
                worldRotationXAxis += worldRotationDelta;
            }
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            if (isShiftPressed) {
                float worldRotationDelta = -1 * worldRotationRate * dt;
                worldRotationZAxis += worldRotationDelta;
            } else {
                float worldRotationDelta = 1 * worldRotationRate * dt;
                worldRotationXAxis += worldRotationDelta;
            }
        }
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            float worldRotationDelta = -1 * worldRotationRate * dt;
            worldRotationYAxis += worldRotationDelta;
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            float worldRotationDelta = 1 * worldRotationRate * dt;
            worldRotationYAxis += worldRotationDelta;
        }
        // Resets the world rotation to default
        if (glfwGetKey(window, GLFW_KEY_HOME) == GLFW_PRESS) {
            worldRotationZAxis = 0.0f;
            worldRotationYAxis = 0.0f;
            worldRotationXAxis = 0.0f;
        }

        // Controls the rendering mode
        if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
            renderingMode = GL_POINTS;
        }
        if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
            renderingMode = GL_LINES;
        }
        if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
            renderingMode = GL_TRIANGLES;
        }

        // Controls the enabling of textures
        if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
            if (glfwGetTime() - controlTimer >= 0.1f) {
                isTexturesEnabled = !isTexturesEnabled;
                if (isTexturesEnabled) {
                    defaultShaderProgram.enableTextures();
                } else {
                    defaultShaderProgram.disableTextures();
                }
                controlTimer = glfwGetTime();
            }
        }

        // Declare and store the current mouse position
        double mousePosX, mousePosY;
        glfwGetCursorPos(window, &mousePosX, &mousePosY);

        // Calculate mouse x- and y-position delta
        double dx = mousePosX - lastMousePosX;
        double dy = mousePosY - lastMousePosY;

        // Set the last mouse position as the current mouse position
        lastMousePosX = mousePosX;
        lastMousePosY = mousePosY;

        // Apply angular delta and convert to spherical coordinates
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
            cameraHorizontalAngle += -1 * cameraPanRate * dt * dx;
        }
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
            cameraVerticalAngle += -1 * cameraTiltRate * dt * dy;
        }
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            fieldOfView += cameraZoomRate * dt * dy;
            fieldOfView = std::max(minimumFieldOfView, std::min(maximumFieldOfView, fieldOfView));
        }

        // Clamp vertical angle to [-85, 85] degrees
        cameraVerticalAngle = std::max(-85.0f, std::min(85.0f, cameraVerticalAngle));
        if (cameraHorizontalAngle > 360)
        {
            cameraHorizontalAngle -= 360;
        }
        else if (cameraHorizontalAngle < -360)
        {
            cameraHorizontalAngle += 360;
        }

        float theta = radians(cameraHorizontalAngle);
        float phi = radians(cameraVerticalAngle);

        cameraLookAt = vec3(cosf(phi)*cosf(theta), sinf(phi), -cosf(phi)*sinf(theta));

        mat4 viewMatrix = lookAt(cameraPosition, cameraPosition + cameraLookAt, cameraUp);
        defaultShaderProgram.setViewMatrix(viewMatrix);

        // Resets the camera view to default
        if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
            cameraHorizontalAngle = 90.0f;
            cameraVerticalAngle = 0.0f;
            fieldOfView = 60.0f / 360.0f * 2 * M_PI;
        }
    }

    // Shutdown GLFW
    glfwTerminate();

    return 0;
}