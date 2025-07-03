// 리팩터링
// main에서 GLFW / OpenGL Context / GLAD 초기화
// 셋을 분리한다

#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include "common.h"
#include "shader.h"
#include "program.h"

CLASS_PTR(Context)
class Context 
{
public:
    static ContextUPtr Create();
    void Render();    
private:
    Context() {}
    bool Init();
    ProgramUPtr m_program;  // 만들 프로그램 저장

    uint32_t m_vertexArrayObject; // 정점 배열 객체(Vertex Array Object, VAO)
    uint32_t m_vertexBuffer;    // 정점 데이터를 저장할 버퍼
};


#endif // __CONTEXT_H__