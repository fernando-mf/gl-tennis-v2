#ifndef PA2_SPHERE_H
#define PA2_SPHERE_H

#include <GL/glew.h>
#include <glm/glm.hpp>

using namespace glm;

class Sphere {
private:
    GLuint vertexBufferObject;
    unsigned int verticesNum;

    struct Vertex {
        vec3 position;
        vec3 normal;
        vec3 color;
    };
public:
    Sphere(vec3 colorVec);

    unsigned int getVerticesNum();

    GLuint getVertexBufferObject();
};

#endif //PA2_SPHERE_H