#ifndef PA2_TEXTUREDCOLOREDVERTEX_H
#define PA2_TEXTUREDCOLOREDVERTEX_H

#include <glm/glm.hpp>

using namespace glm;

class TexturedColoredVertex {
private:
    vec3 position;
    vec3 color;
    vec3 normal;
    vec2 uv;
public:
    TexturedColoredVertex();

    TexturedColoredVertex(vec3 position, vec3 color, vec3 normal, vec2 uv);
};

#endif //PA2_TEXTUREDCOLOREDVERTEX_H