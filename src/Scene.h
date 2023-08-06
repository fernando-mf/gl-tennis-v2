//
// Created by Fernando on 2023-08-05.
//

#ifndef ASSIGNMENT2_SCENE_H
#define ASSIGNMENT2_SCENE_H

#include <list>

#include "ShaderProgram.h"
#include "TennisRacketModel.h"
#include "JonathanImpl/TennisBallModel.h"
#include "FernandoImpl/TennisBallFernando.h"

using namespace std;

class Scene {
private:
    TennisBallModel tennisBallJonathan;
    TennisBallFernando tennisBallFernando;

    GLuint vaoGround;
    GLuint vaoXAxis;
    GLuint vaoYAxis;
    GLuint vaoZAxis;
    GLuint vaoNetPost;
    GLuint vaoNetTop;
    GLuint vaoNetTwine;

    GLuint renderingMode;

    Texture groundTexture;
public:
    vector<TennisRacketModel *> models;

    /* WORLD CONTROL VARIABLES */
    float worldRotationXAxis = 0.0f; // default X-rotation of 0
    float worldRotationYAxis = 0.0f; // default Y-rotation of 0
    float worldRotationZAxis = 0.0f; // default Z-rotation of 0

    Scene();

    void draw(ShaderProgram *shaderProgram);

    void setRenderingMode(GLuint renderingMode);
};


#endif //ASSIGNMENT2_SCENE_H
