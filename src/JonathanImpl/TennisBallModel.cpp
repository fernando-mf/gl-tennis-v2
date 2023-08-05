#include "TennisBallModel.h"
#include "Sphere.h"

TennisBallModel::TennisBallModel() {
    Sphere sphereBall = Sphere(vec3(202.0f/255.0f, 231.0f/255.0f, 36.0f/255.0f));

    vaoBall = sphereBall.getVertexBufferObject();
    verticesNum = sphereBall.getVerticesNum();

    ballTexture = Texture("./assets/textures/tennis_ball.png");
}

void TennisBallModel::draw(mat4 hierarchyModelMatrix, ShaderProgram shaderProgram, GLuint renderingMode) {
    // Declare reusable model matrix
    mat4 modelMatrix;

    /* MODEL AND DRAW */
    glBindVertexArray(vaoBall);
    ballTexture.use();
    mat4 tennisballModelMatrix = translate(mat4(1.0f), vec3(0.0f, 11.0f, -2.0f)) * scale(mat4(1.0f), vec3(0.7f, 0.7f, 0.7f));
    modelMatrix = hierarchyModelMatrix * tennisballModelMatrix;
    shaderProgram.setWorldMatrix(modelMatrix);
    switch (renderingMode) {
        case GL_POINTS:
            glDrawArrays(GL_POINTS, 0, verticesNum);
            break;
        case GL_LINES:
            glDrawArrays(GL_LINE_STRIP, 0, verticesNum);
            break;
        case GL_TRIANGLES:
            glDrawArrays(GL_TRIANGLE_STRIP, 0, verticesNum);
            break;
    }
}