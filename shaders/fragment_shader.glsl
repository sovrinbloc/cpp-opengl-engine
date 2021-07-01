#version 330 core
out vec4 FragColor;
in vec3 Position;
void main()
{
    FragColor = vec4(0.0f + Position.x, 1.0f + Position.y, 1.0f + Position.z, 1.0f);
}