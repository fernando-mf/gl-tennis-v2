#version 330 core

in vec2 vertexUV;
in vec3 pos;
in vec3 normal;
in vec3 eyeDir;
in vec3 lightDir;
in vec3 vertexColor;
in vec4 posLightSpace;

uniform vec3 lightPos;
uniform sampler2D textureSampler;
uniform bool texturedEnabled = false;
uniform sampler2D shadowMap;

out vec3 FragColor;

float calculateShadow()
{
    vec3 projCoords = posLightSpace.xyz / posLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    float currentDepth = projCoords.z;
    vec3 lightDir = normalize(lightPos - pos);
    float bias = max(0.0000005 * (1.0 - dot(normal, lightDir)), 0.00005);
    float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;
    return shadow;
}

void main() {
    vec3 lightColor = vec3(1,1,1);
    float lightPower = 50.0f;

    vec4 textureColor = vec4(vertexColor, 1.0f);
    if (texturedEnabled) {
        textureColor = texture(textureSampler, vertexUV);
    }
    vec3 diffuseColor = textureColor.xyz;
    vec3 specularColor = vec3(0.3,0.3,0.3);
    vec3 ambientColor = vec3(0.5,0.5,0.5) * textureColor.xyz;

    float dist = length(lightPos - pos);
    vec3 n = normalize(normal);
    vec3 l = normalize(lightDir);

    float cosTheta = clamp(dot(n, l), 0, 1);

    vec3 E = normalize(eyeDir);
    vec3 R = reflect(-l, n);

    float cosAlpha = clamp(dot(E, R), 0, 1);

    vec3 finalColor =
    ambientColor +
    diffuseColor * lightColor * lightPower * cosTheta / (1 + dist * 0.5 + dist * dist * 0.05) +
    specularColor * lightColor * lightPower * pow(cosAlpha, 5) / (1 + dist * 0.5 + dist * dist * 0.05);

    float shadow = calculateShadow();

    FragColor = finalColor * (1.0 - shadow);
}