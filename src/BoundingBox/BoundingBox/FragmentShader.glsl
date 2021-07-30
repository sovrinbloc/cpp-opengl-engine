#version 330 core

in vec2 fragmentCoords;

out vec4 out_Color;
uniform vec3 pickingColor;

void main(void){

    out_Color = vec4(pickingColor, 1.0f);
}