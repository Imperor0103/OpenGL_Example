// This is a simple vertex shader written in GLSL (OpenGL Shading Language).
#version 330 core   // 330 core version
layout (location = 0) in vec3 aPos; // VAO의 0번 attribute와 연결되어 vec3 형태로 정점 위치를 입력받는다.

// shader 또한 main 함수를 반드시 가지고 있어야 한다.
// 모든 vertex마다 main 함수가 호출된다.
void main() 
{
    //gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
    gl_Position = vec4(aPos, 1.0); // 정점의 위치 변경    
}

