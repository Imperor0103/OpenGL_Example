// This is a simple vertex shader written in GLSL (OpenGL Shading Language).
#version 330 core   // 330 core version
layout (location = 0) in vec3 aPos;

// shader 또한 main 함수를 반드시 가지고 있어야 한다.
// 모든 vertex마다 main 함수가 호출된다.
void main() 
{
    gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
}

