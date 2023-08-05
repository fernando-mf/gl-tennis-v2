#include "TexturedColoredVertex.h"

TexturedColoredVertex::TexturedColoredVertex() {}

TexturedColoredVertex::TexturedColoredVertex(vec3 position, vec3 color, vec3 normal, vec2 uv)
        : position(position), color(color), normal(normal), uv(uv) {}