// Simple fragment shader that outputs a solid red color
// This shader is written in GLSL version 330 core
#version 330 core
out vec4 fragColor;

void main() 
{
    fragColor = vec4(1.0, 0.0, 0.0, 1.0);
}