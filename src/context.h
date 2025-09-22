// 리팩터링
// main에서 GLFW / OpenGL Context / GLAD 초기화
// 셋을 분리한다

#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include "common.h"
#include "shader.h"
#include "program.h"
#include "buffer.h"
#include "vertex_layout.h"

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

    VertexLayoutUPtr m_vertexLayout; // 정점 배열 객체
        
    // vertex, index buffer의 int32 데이터를 UPtr로 변경
    BufferUPtr m_vertexBuffer;
    BufferUPtr m_indexBuffer;
};


#endif // __CONTEXT_H__