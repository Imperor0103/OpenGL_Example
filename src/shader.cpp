#include "shader.h"

ShaderUPtr Shader::CreateFromFile(const std::string& filename, GLenum shaderType) 
{
    auto shader = std::unique_ptr<Shader>(new Shader());  // ShaderUPtr
    if (!shader->LoadFile(filename, shaderType))
        return nullptr;
    return std::move(shader); // transfer ownership
}

Shader::~Shader() 
{
    // 클래스가 소멸되기 전에 m_shader가 0이 아니면 오브젝트가 만들어져 있다는 것이므로 OpenGL shader object ID를 삭제한다
    if (m_shader != 0) 
    {
        glDeleteShader(m_shader); // OpenGL shader object ID를 삭제한다        
    }
}

bool Shader::LoadFile(const std::string& filename, GLenum shaderType) 
{
    auto result = LoadTextFile(filename); // optional을 리턴
    if (!result.has_value())
        return false;

    auto& code = result.value(); // auto&로 받으면, result가 가진 string이 길더라도 주소만 가져오니까 메모리 복사가 일어나지 않는다            
    const char* codePtr = code.c_str();
    int32_t codeLength = (int32_t)code.length();

    // create and compile shader
    m_shader = glCreateShader(shaderType); // 생성된 shader의 핸들 번호를 m_shader에 저장한다
    glShaderSource(m_shader, 1, (const GLchar* const*)&codePtr, &codeLength); // 여러 shader code를 넣을 수 있다, 2번째 매개변수는 shader code의 개수 
    glCompileShader(m_shader); // shader code를 컴파일한다

    // check compile error
    int success = 0;
    glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success);   // iv(integer vector(포인터))로 컴파일 상태를 int*로 &success에 가져온다(컴파일 성공여부 확인)
    if (!success) 
    {
        char infoLog[1024]; // 버퍼의 크기
        glGetShaderInfoLog(m_shader, 1024, nullptr, infoLog); // infoLog에 컴파일 에러 메시지를 가져온다
        SPDLOG_ERROR("failed to compile shader: \"{}\"", filename);
        SPDLOG_ERROR("reason: {}", infoLog);
        return false;
    }
    return true;
}