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
    // 정점 데이터
    float vertices[] = {
        // first triangle
        0.5f, 0.5f, 0.0f, // top right
        0.5f, -0.5f, 0.0f, // bottom right
        -0.5f, 0.5f, 0.0f, // top left
        // second triangle
        0.5f, -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f // top left
    };

    // VAO는 Vertex Buffer를 만들기 전에 생성한다
    glGenVertexArrays(1, &m_vertexArrayObject); // glGenVertexArrays()는 OpenGL에서 정점 배열 객체(Vertex Array Object, VAO)를 생성하는 함수
    glBindVertexArray(m_vertexArrayObject); // glBindVertexArray()는 VAO를 바인딩하여 m_vertexArrayObject를 사용할 수 있도록 설정하는 함수

    glGenBuffers(1, &m_vertexBuffer);   // glGenBuffers()는 OpenGL에서 버퍼 객체를 생성하는 함수
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);  // glBindBuffer()는 버퍼를 바인딩하여 m_vertexBuffer를 사용할 수 있도록 설정하는 함수
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 18, vertices, GL_STATIC_DRAW); 
    // glBufferData()는 버퍼에 데이터를 복사하는 함수
    // vertices에 있는 정점 데이터를 GL_ARRAY_BUFFER에 복사, sizeof(float) * 9는 버퍼의 크기, GL_STATIC_DRAW는 버퍼의 사용 용도를 나타냄

    // Vertex Buffer의 속성을 설정
    glEnableVertexAttribArray(0);   // glEnableVertexAttribArray()는 정점 속성 배열을 활성화하는 함수, 0은 속성 인덱스
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);  // 0번 attribute에 3개의 float를 사용, GL_FALSE는 정규화(normalize)하지 않음, sizeof(float) * 3만큼 건너뛰어야 다음 stride, 0은 버퍼의 시작 위치

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

    return true;
}

void Context::Render() 
{
    // 색상버퍼 초기화
    glClear(GL_COLOR_BUFFER_BIT);

    // 그림 그리는 함수
    // glUseProgram()은 OpenGL 프로그램을 사용하는 함수, m_program->Get()으로 OpenGL program object ID를 가져와서 사용
    glUseProgram(m_program->Get());
    // glDrawArrays(GL_POINTS, 0, 1); // 점 하나 출력
    // glDrawArrays(GL_TRIANGLES, 0, 3); // 삼각형 출력
    glDrawArrays(GL_TRIANGLES, 0, 6); // 삼각형 2개 출력
}
