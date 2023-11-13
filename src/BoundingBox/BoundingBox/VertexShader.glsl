#version 330 core

in vec3 position;

uniform mat4 transformationMatrix; // model matrix
uniform mat4 viewMatrix; // view matrix
uniform mat4 projectionMatrix; // projection matrix

uniform vec3 viewPosition;

void main(void){

    gl_Position = projectionMatrix * viewMatrix * transformationMatrix * vec4(position, 1.0);
}