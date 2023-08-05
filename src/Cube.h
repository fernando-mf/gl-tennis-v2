#ifndef PA1_CUBE_H
#define PA1_CUBE_H

#include <GL/glew.h>
#include <glm/glm.hpp>

using namespace glm;

class Cube {
private:
    GLuint vertexBufferObject;
public:
    Cube();

    Cube(vec3 colorVec);

    GLuint getVertexBufferObject();
};

#endif //PA1_CUBE_H