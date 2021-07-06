#version 330 core
struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoords;
layout (location = 2) in vec3 normal;

out vec2 pass_textureCoords;
out vec3 surfaceNormal;
out vec3 toLightVector;
out vec4 worldPosition;
out float visibility;

uniform mat4 transformationMatrix; // model matrix
uniform mat4 viewMatrix; // view matrix
uniform mat4 projectionMatrix; // projection matrix

uniform float useFakeLighting;

const float density = 0.00035;
const float gradient = 5.0;


void main()
{
    worldPosition = transformationMatrix * vec4(position, 1.0);
    vec4 positionRelativeToCam = viewMatrix * worldPosition;
    gl_Position = projectionMatrix * positionRelativeToCam;
    pass_textureCoords = textureCoords;

    vec3 actualNormal = normal;
    if (useFakeLighting > 0.5) {
        actualNormal = vec3(0.0, 1, 0.0);
    }

    surfaceNormal = (transformationMatrix * vec4(normal, 0.0)).xyz;
    toLightVector = light.position - worldPosition.xyz;

    float distance = length(positionRelativeToCam.xyz);
    visibility = exp(-pow((distance * density), gradient));
    visibility = clamp(visibility, 0.0, 1.0);
}
