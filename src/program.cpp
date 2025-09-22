#include "program.h"

ProgramUPtr Program::Create(const std::vector<ShaderPtr>& shaders) 
{
    auto program = ProgramUPtr(new Program());  // ProgramUPtr은 std::unique_ptr<Program>
    if (!program->Link(shaders))
        return nullptr;
    return std::move(program);
}

Program::~Program() 
{
    if (m_program) 
    {
        glDeleteProgram(m_program);
    }
}

bool Program::Link(const std::vector<ShaderPtr>& shaders) 
{
    m_program = glCreateProgram();  // OpenGL program object ID를 생성한다
    for (auto& shader: shaders) // c++11부터 사용하는 문법
        glAttachShader(m_program, shader->Get());   // ShaderPtr이므로 Get()으로 OpenGL shader object ID를 가져와서 세팅 
    glLinkProgram(m_program);

    int success = 0;
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if (!success) 
    {
        char infoLog[1024];
        glGetProgramInfoLog(m_program, 1024, nullptr, infoLog);
        SPDLOG_ERROR("failed to link program: {}", infoLog);
        return false;
    }
    return true;
}

void Program::Use() const
{
    glUseProgram(m_program);
}