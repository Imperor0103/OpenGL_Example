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
    // 정점 데이터(vertex buffer)
    float vertices[] = {
        // 사각형을 이루는 4개의 정점만 추가
        0.5f, 0.5f, 0.0f, // top right(0번)
        0.5f, -0.5f, 0.0f, // bottom right(1번)
        -0.5f, -0.5f, 0.0f, // bottom left(2번)
        -0.5f, 0.5f, 0.0f, // top left(3번)
    };
    // index buffer
    uint32_t indices[] = { // note that we start from 0!
        // 정점의 인덱스(0~3)를 이용 삼각형을 만든다
        0, 1, 3, // first triangle
        1, 2, 3, // second triangle
    };

    // VAO는 Vertex Buffer를 만들기 전에 생성한다
    glGenVertexArrays(1, &m_vertexArrayObject); // glGenVertexArrays()는 OpenGL에서 정점 배열 객체(Vertex Array Object, VAO)를 생성하는 함수
    glBindVertexArray(m_vertexArrayObject); // glBindVertexArray()는 VAO를 바인딩하여 m_vertexArrayObject를 사용할 수 있도록 설정하는 함수

    // vertex buffer 설정
    m_vertexBuffer = Buffer::CreateWithData(GL_ARRAY_BUFFER, GL_STATIC_DRAW, vertices, sizeof(vertices));   // sizeof(vertices) = sizeof(float) * 12
        
    // Vertex Buffer의 속성을 설정
    glEnableVertexAttribArray(0);   // glEnableVertexAttribArray()는 정점 속성 배열을 활성화하는 함수, 0은 속성 인덱스
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);  // 0번 attribute에 3개의 float를 사용, GL_FALSE는 정규화(normalize)하지 않음, sizeof(float) * 3만큼 건너뛰어야 다음 stride, 0은 버퍼의 시작 위치
    
    // index buffer 설정
    m_indexBuffer = Buffer::CreateWithData(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, indices, sizeof(indices));  // sizeof(indices) = sizeof(uint32_t) * 6
    
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

    m_program->Use(); // 프로그램 사용   
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // index buffer를 사용하여 삼각형 2개 출력
}
