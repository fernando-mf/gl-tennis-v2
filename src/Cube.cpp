#include "Cube.h"
#include "TexturedColoredVertex.h"

Cube::Cube() {}

Cube::Cube(vec3 colorVec) {
    TexturedColoredVertex vertexArray[] = {  // position, color, normal, uv
            TexturedColoredVertex(vec3(-0.5f, -0.5f, -0.5f), colorVec, vec3(-1.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f)), //left
            TexturedColoredVertex(vec3(-0.5f, -0.5f, 0.5f), colorVec, vec3(-1.0f, 0.0f, 0.0f), vec2(0.0f, 1.0f)),
            TexturedColoredVertex(vec3(-0.5f, 0.5f, 0.5f), colorVec, vec3(-1.0f, 0.0f, 0.0f), vec2(1.0f, 1.0f)),

            TexturedColoredVertex(vec3(-0.5f, -0.5f, -0.5f), colorVec, vec3(-1.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f)),
            TexturedColoredVertex(vec3(-0.5f, 0.5f, 0.5f), colorVec, vec3(-1.0f, 0.0f, 0.0f), vec2(1.0f, 1.0f)),
            TexturedColoredVertex(vec3(-0.5f, 0.5f, -0.5f), colorVec, vec3(-1.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f)),

            TexturedColoredVertex(vec3(0.5f, 0.5f, -0.5f), colorVec, vec3(0.0f, 0.0f, -1.0f), vec2(1.0f, 1.0f)), // far
            TexturedColoredVertex(vec3(-0.5f, -0.5f, -0.5f), colorVec, vec3(0.0f, 0.0f, -1.0f), vec2(0.0f, 0.0f)),
            TexturedColoredVertex(vec3(-0.5f, 0.5f, -0.5f), colorVec, vec3(0.0f, 0.0f, -1.0f), vec2(0.0f, 1.0f)),

            TexturedColoredVertex(vec3(0.5f, 0.5f, -0.5f), colorVec, vec3(0.0f, 0.0f, -1.0f), vec2(1.0f, 1.0f)),
            TexturedColoredVertex(vec3(0.5f, -0.5f, -0.5f), colorVec, vec3(0.0f, 0.0f, -1.0f), vec2(1.0f, 0.0f)),
            TexturedColoredVertex(vec3(-0.5f, -0.5f, -0.5f), colorVec, vec3(0.0f, 0.0f, -1.0f), vec2(0.0f, 0.0f)),

            TexturedColoredVertex(vec3(0.5f, -0.5f, 0.5f), colorVec, vec3(0.0f, -1.0f, 0.0f), vec2(1.0f, 1.0f)), // bottom
            TexturedColoredVertex(vec3(-0.5f, -0.5f, -0.5f), colorVec, vec3(0.0f, -1.0f, 0.0f), vec2(0.0f, 0.0f)),
            TexturedColoredVertex(vec3(0.5f, -0.5f, -0.5f), colorVec, vec3(0.0f, -1.0f, 0.0f), vec2(1.0f, 0.0f)),

            TexturedColoredVertex(vec3(0.5f, -0.5f, 0.5f), colorVec, vec3(0.0f, -1.0f, 0.0f), vec2(1.0f, 1.0f)),
            TexturedColoredVertex(vec3(-0.5f, -0.5f, 0.5f), colorVec, vec3(0.0f, -1.0f, 0.0f), vec2(0.0f, 1.0f)),
            TexturedColoredVertex(vec3(-0.5f, -0.5f, -0.5f), colorVec, vec3(0.0f, -1.0f, 0.0f), vec2(0.0f, 0.0f)),

            TexturedColoredVertex(vec3(-0.5f, 0.5f, 0.5f), colorVec, vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 1.0f)), // near
            TexturedColoredVertex(vec3(-0.5f, -0.5f, 0.5f), colorVec, vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f)),
            TexturedColoredVertex(vec3(0.5f, -0.5f, 0.5f), colorVec, vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 0.0f)),

            TexturedColoredVertex(vec3(0.5f, 0.5f, 0.5f), colorVec, vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 1.0f)),
            TexturedColoredVertex(vec3(-0.5f, 0.5f, 0.5f), colorVec, vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 1.0f)),
            TexturedColoredVertex(vec3(0.5f, -0.5f, 0.5f), colorVec, vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 0.0f)),

            TexturedColoredVertex(vec3(0.5f, 0.5f, 0.5f), colorVec, vec3(1.0f, 0.0f, 0.0f), vec2(1.0f, 1.0f)), // right
            TexturedColoredVertex(vec3(0.5f, -0.5f, -0.5f), colorVec, vec3(1.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f)),
            TexturedColoredVertex(vec3(0.5f, 0.5f, -0.5f), colorVec, vec3(1.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f)),

            TexturedColoredVertex(vec3(0.5f, -0.5f, -0.5f), colorVec, vec3(1.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f)),
            TexturedColoredVertex(vec3(0.5f, 0.5f, 0.5f), colorVec, vec3(1.0f, 0.0f, 0.0f), vec2(1.0f, 1.0f)),
            TexturedColoredVertex(vec3(0.5f, -0.5f, 0.5f), colorVec, vec3(1.0f, 0.0f, 0.0f), vec2(0.0f, 1.0f)),

            TexturedColoredVertex(vec3(0.5f, 0.5f, 0.5f), colorVec, vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 1.0f)), // top
            TexturedColoredVertex(vec3(0.5f, 0.5f, -0.5f), colorVec, vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 0.0f)),
            TexturedColoredVertex(vec3(-0.5f, 0.5f, -0.5f), colorVec, vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 0.0f)),

            TexturedColoredVertex(vec3(0.5f, 0.5f, 0.5f), colorVec, vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 1.0f)),
            TexturedColoredVertex(vec3(-0.5f, 0.5f, -0.5f), colorVec, vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 0.0f)),
            TexturedColoredVertex(vec3(-0.5f, 0.5f, 0.5f), colorVec, vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f))
    };

    // Create a vertex array object
    GLuint vertexArrayObject;
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    // Upload Vertex Buffer to the GPU
    glGenBuffers(1, &this->vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArray), vertexArray, GL_STATIC_DRAW);

    // 0 - position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(TexturedColoredVertex), (void *) 0);
    glEnableVertexAttribArray(0);

    // 1 - color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(TexturedColoredVertex), (void *) sizeof(vec3));
    glEnableVertexAttribArray(1);

    // 2 - normal
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(TexturedColoredVertex), (void *) (2 * sizeof(vec3)));
    glEnableVertexAttribArray(2);

    // 3 - uv
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(TexturedColoredVertex), (void *) (3 * sizeof(vec3)));
    glEnableVertexAttribArray(3);
}

GLuint Cube::getVertexBufferObject() {
    return this->vertexBufferObject;
}