#include "context.h"

ContextUPtr Context::Create() 
{
    auto context = ContextUPtr(new Context());
    if (!context->Init())
        return nullptr;
    return std::move(context);
}

// Context
bool Context::Init() 
{
    ShaderPtr vertShader = Shader::CreateFromFile("./shader/simple.vs", GL_VERTEX_SHADER);
    ShaderPtr fragShader = Shader::CreateFromFile("./shader/simple.fs", GL_FRAGMENT_SHADER);
    if (!vertShader || !fragShader)
        return false;
    SPDLOG_INFO("vertex shader id: {}", vertShader->Get());
    SPDLOG_INFO("fragment shader id: {}", fragShader->Get());

    m_program = Program::Create({fragShader, vertShader});
    if (!m_program)
        return false;
    SPDLOG_INFO("program id: {}", m_program->Get());

    // 윈도우를 파란색으로 변경
    glClearColor(0.1f, 0.2f, 0.3f, 0.0f);   // glClearColor()는 윈도우의 배경색을 설정하는 함수, RGBA값을 0.0f ~ 1.0f로 설정    

    uint32_t vao = 0;
    glGenVertexArrays(1, &vao); // glGenVertexArrays()는 Vertex Array Object(VAO)를 생성하는 함수
    glBindVertexArray(vao); // glBindVertexArray()는 VAO를 바인딩하는 함수, VAO는 OpenGL에서 버텍스 속성을 저장하는 객체

    return true;
}

void Context::Render() 
{
    // 색상버퍼 초기화
    glClear(GL_COLOR_BUFFER_BIT);

    // 그림 그리는 함수
    // glUseProgram()은 OpenGL 프로그램을 사용하는 함수, m_program->Get()으로 OpenGL program object ID를 가져와서 사용
    glUseProgram(m_program->Get());
    glDrawArrays(GL_POINTS, 0, 1);
}
