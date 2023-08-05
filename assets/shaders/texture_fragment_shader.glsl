#version 330 core
uniform vec3 lightPos;
in vec2 vertexUV;
uniform sampler2D textureSampler;
in vec3 pos;
in vec3 normal;
in vec3 eyeDir;
in vec3 lightDir;
out vec3 FragColor;

void main() {
    vec3 lightColor = vec3(1,1,1);
    float lightPower = 50.0f;

    vec4 textureColor = texture(textureSampler, vertexUV);
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

    FragColor =
    ambientColor +
    diffuseColor * lightColor * lightPower * cosTheta / (1 + dist * 0.5 + dist * dist * 0.05) +
    specularColor * lightColor * lightPower * pow(cosAlpha, 5) / (1 + dist * 0.5 + dist * dist * 0.05);
}