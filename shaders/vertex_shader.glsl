#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoords;

out vec2 pass_textureCoords;

uniform mat4 transformationMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 lightPosition;
void main()
{
    pass_textureCoords = textureCoords;
    gl_Position = projectionMatrix * viewMatrix * transformationMatrix * vec4(position, 1.0);
}
