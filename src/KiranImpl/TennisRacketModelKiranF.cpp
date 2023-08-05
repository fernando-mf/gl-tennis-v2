#include <vector>
#include "TennisRacketModelKiranF.h"
#include "../TennisRacketModel.h"
#include "../Cube.h"



std::vector<glm::vec3> generateSphereVertices(float radius, int stacks, int slices) {
    std::vector<glm::vec3> vertices;

    for (int i = 0; i <= stacks; ++i) {
        float phi = glm::pi<float>() * static_cast<float>(i) / static_cast<float>(stacks);
        float sinPhi = std::sin(phi);
        float cosPhi = std::cos(phi);

        for (int j = 0; j <= slices; ++j) {
            float theta = 2.0f * glm::pi<float>() * static_cast<float>(j) / static_cast<float>(slices);
            float sinTheta = std::sin(theta);
            float cosTheta = std::cos(theta);

            float x = cosTheta * sinPhi;
            float y = cosPhi;
            float z = sinTheta * sinPhi;

            vertices.push_back(glm::vec3(radius * x, radius * y, radius * z));
        }
    }

    return vertices;
}
std::vector<unsigned int> generateSphereIndices(int stacks, int slices) {
    std::vector<unsigned int> indices;

    for (int i = 0; i < stacks; ++i) {
        for (int j = 0; j < slices; ++j) {
            int p1 = i * (slices + 1) + j;
            int p2 = p1 + 1;
            int p3 = (i + 1) * (slices + 1) + j;
            int p4 = p3 + 1;

            // First triangle of the quad
            indices.push_back(p1);
            indices.push_back(p3);
            indices.push_back(p2);

            // Second triangle of the quad
            indices.push_back(p2);
            indices.push_back(p3);
            indices.push_back(p4);
        }
    }

    return indices;
}
std::vector<glm::vec3> generateSphereNormals(float radius, int stacks, int slices) {
    std::vector<glm::vec3> normals;

    for (int i = 0; i <= stacks; ++i) {
        float phi = glm::pi<float>() * static_cast<float>(i) / static_cast<float>(stacks);
        float sinPhi = std::sin(phi);
        float cosPhi = std::cos(phi);

        for (int j = 0; j <= slices; ++j) {
            float theta = 2.0f * glm::pi<float>() * static_cast<float>(j) / static_cast<float>(slices);
            float sinTheta = std::sin(theta);
            float cosTheta = std::cos(theta);

            float x = cosTheta * sinPhi;
            float y = cosPhi;
            float z = sinTheta * sinPhi;

            glm::vec3 normal = glm::normalize(glm::vec3(x, y, z)); // Calculate the normal vector
            normals.push_back(normal);
        }
    }

    return normals;
}
std::vector<glm::vec2> generateSphereUVs(int stacks, int slices) {
    std::vector<glm::vec2> uvs;

    for (int i = 0; i <= stacks; ++i) {
        float v = static_cast<float>(i) / static_cast<float>(stacks);

        for (int j = 0; j <= slices; ++j) {
            float u = static_cast<float>(j) / static_cast<float>(slices);

            uvs.push_back(glm::vec2(u, v));
        }
    }

    return uvs;
}
int createVaoSphere(std::vector<glm::vec3> sphereVertices, std::vector<unsigned int> sphereIndices, std::vector<glm::vec3> sphereNormals, std::vector<glm::vec2> uvs)
{
    std::vector<glm::vec3> colors(sphereIndices.size(), vec3(0.0f, 0.4f, 0.0f));

    // Create a vertex array
    GLuint vertexArrayObject;
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    // Upload Vertex Positions Buffer to the GPU
    GLuint vertexPositionBuffer;
    glGenBuffers(1, &vertexPositionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexPositionBuffer);
    glBufferData(GL_ARRAY_BUFFER, sphereVertices.size() * sizeof(glm::vec3), sphereVertices.data(), GL_STATIC_DRAW);

    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphereIndices.size() * sizeof(unsigned int), &sphereIndices[0], GL_STATIC_DRAW);

    // Set vertex position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);

    // Upload Vertex Colors Buffer to the GPU
    GLuint vertexColorBuffer;
    glGenBuffers(1, &vertexColorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexColorBuffer);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);

    // Set vertex color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

    // Upload Vertex Colors Buffer to the GPU
    GLuint vertexNormalBuffer;
    glGenBuffers(1, &vertexNormalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexNormalBuffer);
    glBufferData(GL_ARRAY_BUFFER, sphereVertices.size() * sizeof(glm::vec3), sphereVertices.data(), GL_STATIC_DRAW);

    // Set vertex color attribute
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(2);

    // Upload Vertex UV Buffer to the GPU
    GLuint vertexUVBuffer;
    glGenBuffers(1, &vertexUVBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexUVBuffer);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), uvs.data(), GL_STATIC_DRAW);

    // Set vertex color attribute
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(3);

    return vertexArrayObject;
}


TennisRacketModelKiranF::TennisRacketModelKiranF(const vec3 &position) : TennisRacketModel(position) {
    Cube cubeArm = Cube(vec3(238.0f/255.0f, 199.0f/255.0f, 149.0f/255.0f));
    Cube cubeRacketFrameRed =  Cube(vec3(163.0f/255.0f, 0.0f, 0.0f));
    Cube cubeRacketFrameGrey =  Cube(vec3(164.0f/255.0f, 164.0f/255.0f, 164.0f/255.0f));
    Cube cubeRacketString = Cube(vec3(36.0f/255.0f, 156.0f/255.0f, 0.0f));

    //sphere time
    float radius = 1.0f;
    int stacks = 20;
    int slices = 20;
    std::vector<glm::vec3> sphereVertices = generateSphereVertices(radius, stacks, slices);
    sphereIndices = generateSphereIndices(stacks, slices);
    std::vector<glm::vec3> sphereNormals = generateSphereNormals(radius, stacks, slices);
    std::vector<glm::vec2> uvs = generateSphereUVs(stacks, slices);

    vaoArm = cubeArm.getVertexBufferObject();
    vaoRacketFrameRed = cubeRacketFrameRed.getVertexBufferObject();
    vaoRacketFrameGrey = cubeRacketFrameGrey.getVertexBufferObject();
    vaoRacketString = cubeRacketString.getVertexBufferObject();
    vaoSphere = createVaoSphere(sphereVertices, sphereIndices, sphereNormals, uvs);
}

void TennisRacketModelKiranF::draw(mat4 hierarchyModelMatrix, ShaderProgram shaderProgram, GLuint renderMode) {


    //lower arm
    glBindVertexArray(vaoArm);
    //                                                            position                                                        rotation                                                                     scale
    mat4 lowerArm = translate(hierarchyModelMatrix, vec3(0.0f, 0.0f, 0.0f)) * glm::rotate(mat4(1.0f), -.6f, glm::vec3(0.0f, 0.0f, 1.0f)) * scale(mat4(1.0f), vec3(1.0f, 2.0f, 1.0f));
    shaderProgram.setWorldMatrix(lowerArm);
    glDrawArrays(renderMode, 0, 36);

    mat4 upperArm = translate(lowerArm, vec3(0.0f, 1.0f, 0.0f)) * scale(mat4(1.0f), vec3(0.8f, 1.0f, 0.8f));
    shaderProgram.setWorldMatrix(upperArm);
    glDrawArrays(renderMode, 0, 36);

    //upper arm
    glm::mat4 elbowRotation = glm::rotate(mat4(1.0f), .5f + radians(this->getModelLowerarmRotationZAxis()), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 elbowScaling = glm::scale(mat4(1.0f), vec3(0.9f, 1.6f, 0.9f));
    glm::mat4 elbowTranslation = glm::translate(glm::mat4(1.0), vec3(0.1f, 1.2f, 0.0f));
    glm::mat4 elbowTranslation2 = glm::translate(glm::mat4(1.0), vec3(0.0f, .3f, 0.0f));
    mat4 elbow = upperArm * (elbowTranslation2 * elbowRotation * elbowTranslation * elbowScaling);
    shaderProgram.setWorldMatrix(elbow);
    glDrawArrays(renderMode, 0, 36);

    //hand
    mat4 hand = translate(elbow, vec3(-0.05f, .6f, 0.0f)) * glm::rotate(mat4(1.0f), radians(this->getModelHandRotationZAxis()), glm::vec3(0.0f, 0.0f, 1.0f)) * scale(mat4(1.0f), vec3(1.3f, 0.6f, 1.7f));
    shaderProgram.setWorldMatrix(hand);
    glDrawArrays(renderMode, 0, 36);
    //thumb
    mat4 thumb = translate(hand, vec3(-0.3f, .6f, -0.4f)) * glm::rotate(mat4(1.0f), 0.1f + radians(this->getModelLowerarmRotationZAxis()), glm::vec3(0.0f, 1.0f, 0.0f)) * scale(mat4(1.0f), vec3(0.35f, 0.2f, .6f));
    shaderProgram.setWorldMatrix(thumb);
    glDrawArrays(renderMode, 0, 36);
    //fingies
    mat4 indexFinger = translate(hand, vec3(0.5f, .4f, 0.0f)) * glm::rotate(mat4(1.0f), 0.1f + radians(this->getModelLowerarmRotationZAxis()), glm::vec3(0.0f, 1.0f, 0.0f)) * scale(mat4(1.0f), vec3(0.35f, 0.2f, 1.0f));
    shaderProgram.setWorldMatrix(indexFinger);
    glDrawArrays(renderMode, 0, 36);
    mat4 middleFinger = translate(hand, vec3(0.5f, .15f, 0.0f)) * glm::rotate(mat4(1.0f), 0.1f + radians(this->getModelLowerarmRotationZAxis()), glm::vec3(0.0f, 1.0f, 0.0f)) * scale(mat4(1.0f), vec3(0.35f, 0.2f, 1.0f));
    shaderProgram.setWorldMatrix(middleFinger);
    glDrawArrays(renderMode, 0, 36);
    mat4 ringFinger = translate(hand, vec3(0.5f, -0.1f, 0.0f)) * glm::rotate(mat4(1.0f), 0.1f + radians(this->getModelLowerarmRotationZAxis()), glm::vec3(0.0f, 1.0f, 0.0f)) * scale(mat4(1.0f), vec3(0.35f, 0.2f, 1.0f));
    shaderProgram.setWorldMatrix(ringFinger);
    glDrawArrays(renderMode, 0, 36);
    mat4 pinkyFinger = translate(hand, vec3(0.5f, -.35f, 0.0f)) * glm::rotate(mat4(1.0f), 0.1f + radians(this->getModelLowerarmRotationZAxis()), glm::vec3(0.0f, 1.0f, 0.0f)) * scale(mat4(1.0f), vec3(0.35f, 0.2f, 1.0f));
    shaderProgram.setWorldMatrix(pinkyFinger);
    glDrawArrays(renderMode, 0, 36);



    // Model and draw tennis racket
    // Tennis racket red elements
    glBindVertexArray(vaoRacketFrameRed);
    mat4 handle = translate(hand, vec3(0.0f, 1.25f, -0.4f)) * scale(mat4(1.0f), vec3(0.3f, 1.5f, 0.3f));
    shaderProgram.setWorldMatrix(handle);
    glDrawArrays(renderMode, 0, 36);

    mat4 redHorizontal = translate(handle, vec3(-0.0f, .75f, 0.0f)) * glm::rotate(mat4(1.0f), -0.1f, glm::vec3(0.0f, 0.0f, 1.0f)) * scale(mat4(1.0f), vec3(3.0f, 0.15f, 1.0f));
    shaderProgram.setWorldMatrix(redHorizontal);
    glDrawArrays(renderMode, 0, 36);
    mat4 redHorizontal2 = translate(redHorizontal, vec3(0.0f, 12.0f, 0.0f)) * scale(mat4(1.0f), vec3(1.0f, 1.0f, 1.0f));
    shaderProgram.setWorldMatrix(redHorizontal2);
    glDrawArrays(renderMode, 0, 36);

    mat4 redVertical = translate(handle, vec3(4.0f, 1.25f, 0.0f)) * glm::rotate(mat4(1.0f), -0.1f, glm::vec3(0.0f, 0.0f, 1.0f)) * scale(mat4(1.0f), vec3(1.0f, 1.0f, 1.0f));
    shaderProgram.setWorldMatrix(redVertical);
    glDrawArrays(renderMode, 0, 36);
    mat4 redVertical2 = translate(redVertical, vec3(-8.0f, 0.0f, 0.0f)) * scale(mat4(1.0f), vec3(1.0f, 1.0f, 1.0f));
    shaderProgram.setWorldMatrix(redVertical2);
    glDrawArrays(renderMode, 0, 36);

    // Tennis racket grey elements
    glBindVertexArray(vaoRacketFrameGrey);
    mat4 whiteLeftTop = translate(redHorizontal2, vec3(1.0f, -1.5f, 0.0f)) * glm::rotate(mat4(1.0f), 0.3f, glm::vec3(0.0f, 0.0f, 1.0f)) * scale(mat4(1.0f), vec3(0.4f, 3.0f, 1.0f));
    shaderProgram.setWorldMatrix(whiteLeftTop);
    glDrawArrays(renderMode, 0, 36);
    mat4 whiteRightTop = translate(redHorizontal2, vec3(-1.0f, -1.5f, 0.0f)) * glm::rotate(mat4(1.0f), -0.3f, glm::vec3(0.0f, 0.0f, 1.0f)) * scale(mat4(1.0f), vec3(0.4f, 3.0f, 1.0f));
    shaderProgram.setWorldMatrix(whiteRightTop);
    glDrawArrays(renderMode, 0, 36);

    mat4 whiteRightBottom = translate(redHorizontal, vec3(0.7f, 0.2f, 0.0f)) * glm::rotate(mat4(1.0f), -0.3f, glm::vec3(0.0f, 0.0f, 1.0f)) * scale(mat4(1.0f), vec3(0.4f, 5.0f, 1.0f));
    shaderProgram.setWorldMatrix(whiteRightBottom);
    glDrawArrays(renderMode, 0, 36);
    mat4 whiteLeftBottom = translate(redHorizontal, vec3(-0.7f, 0.2f, 0.0f)) * glm::rotate(mat4(1.0f), 0.3f, glm::vec3(0.0f, 0.0f, 1.0f)) * scale(mat4(1.0f), vec3(0.4f, 5.0f, 1.0f));
    shaderProgram.setWorldMatrix(whiteLeftBottom);
    glDrawArrays(renderMode, 0, 36);

    // Tennis racket strings
    glBindVertexArray(vaoRacketString);
    for (int i = 0; i < 7; i++){
        mat4 greenLine = translate(redVertical, vec3(-7.0f + i, 0.0f, 0.0f)) * scale(mat4(1.0f), vec3(0.25f, 1.55f, 0.25f));
        shaderProgram.setWorldMatrix(greenLine);
        glDrawArrays(renderMode, 0, 36);
    }
    for (int i = 0; i < 10; i++){
        mat4 greenLine = translate(redVertical, vec3(-4.0f, -0.6f + (i * 0.14f), 0.0f)) * scale(mat4(1.0f), vec3(6.0f, 0.05f, .25f));
        shaderProgram.setWorldMatrix(greenLine);
        glDrawArrays(renderMode, 0, 36);
    }



    glBindVertexArray(vaoSphere);
    mat4 sphere = translate(hierarchyModelMatrix, vec3(0.0f, 6.5f, 0.0f)) * scale(mat4(1.0f), vec3(0.5f, 0.5f, 0.5f));
    shaderProgram.setWorldMatrix(sphere);
    glDrawElements(renderMode, sphereIndices.size(), GL_UNSIGNED_INT, 0);

}