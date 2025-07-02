#include "common.h"
#include "shader.h" 
#include "program.h"

#include <spdlog/spdlog.h>
#include <glad/glad.h> // glad 라이브러리 헤더파일
#include <GLFW/glfw3.h>


// 윈도우의 크기가 변경될때마다 호출되는 콜백함수
void OnFramebufferSizeChange(GLFWwindow* window, int width, int height) 
{
    SPDLOG_INFO("framebuffer size changed: ({} x {})", width, height);
    glViewport(0, 0, width, height);
}

// 키보드 입력을 처리하는 콜백함수
void OnKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
    SPDLOG_INFO("key: {}, scancode: {}, action: {}, mods: {}{}{}",
        key, scancode,
        action == GLFW_PRESS ? "Pressed" :
        action == GLFW_RELEASE ? "Released" :
        action == GLFW_REPEAT ? "Repeat" : "Unknown",
        mods & GLFW_MOD_CONTROL ? "C" : "-",
        mods & GLFW_MOD_SHIFT ? "S" : "-",
        mods & GLFW_MOD_ALT ? "A" : "-");
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) 
    {
        glfwSetWindowShouldClose(window, true);
    }
}


int main(int argc, const char **argv[]) 
{
    // 시작을 알리는 로그
    SPDLOG_INFO("Start program");


    // glfw 라이브러리 초기화, 실패하면 에러 출력후 종료
    SPDLOG_INFO("Initialize glfw");
    if (!glfwInit())    // glfwInit()는 glfw 라이브러리를 초기화하는 함수
    {
        const char* description = nullptr;
        glfwGetError(&description); // glfwGetError()는 마지막 에러를 가져오는 함수
        SPDLOG_ERROR("failed to initialize glfw: {}", description); // {}는 타입을 자동으로 변환해주는 spdlog의 포맷팅 기능
        return -1;
    } 

    // 윈도우 context 버전의 힌트를 준다(윈도우 생성 이전에 해야한다)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw 윈도우 생성, 실패하면 에러 출력후 종료
    SPDLOG_INFO("Create glfw window");
    // glfwCreateWindow()는 윈도우를 생성하는 함수, 첫번째 인자는 너비, 두번째 인자는 높이, 세번째 인자는 윈도우 이름
    auto window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME,
        nullptr, nullptr);
    if (!window) 
    {
      SPDLOG_ERROR("failed to create glfw window");
      glfwTerminate();
      return -1;
    }
	glfwMakeContextCurrent(window);
    // glfwMakeContextCurrent()는 생성한 윈도우를 현재 context로 설정하는 함수


    // glad를 활용한 OpenGL 함수 로딩
    // 윈도우 context 생성 이후에 호출해야한다
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        SPDLOG_ERROR("failed to initialize glad");
        glfwTerminate();
        return -1;
    }

    /// GLLoader 호출 이후에 OpenGL 함수를 쓸 수 있다

    auto glVersion = glGetString(GL_VERSION);
    // SPDLOG_INFO("OpenGL context version: {}", glVersion);
    SPDLOG_INFO("OpenGL context version: {}", reinterpret_cast<const char*>(glVersion));    // glVersion의 타입은 const GLubyte* → 즉, const unsigned char*
    // reinterpret_cast는 포인터 타입을 변환하는 함수, const GLubyte*를 const char*로 변환
    // fmt::format() (spdlog 내부에서 사용)은 void*나 char*만 안전하게 포맷 가능하고,    
    // unsigned char*이나 GLubyte*는 **"non-void pointer"**로 간주돼서 static_assert로 막음.    
    // 즉, spdlog가 포인터 타입을 문자열로 인식 못 하고, 포인터 주소를 출력하려다 금지 먹은 거야.
    // 예전에는 void*도 가능했지만, 이제는 안된다

    ShaderPtr vertShader = Shader::CreateFromFile("./shader/simple.vs", GL_VERTEX_SHADER);
    ShaderPtr fragShader = Shader::CreateFromFile("./shader/simple.fs", GL_FRAGMENT_SHADER);
    SPDLOG_INFO("vertex shader id: {}", vertShader->Get());   // vertexShader의 ID는 1
    SPDLOG_INFO("fragment shader id: {}", fragShader->Get());   // fragmentShader의 ID는 2

    auto program = Program::Create({fragShader, vertShader});
    SPDLOG_INFO("program id: {}", program->Get());


    OnFramebufferSizeChange(window, WINDOW_WIDTH, WINDOW_HEIGHT);   // 처음 생성될 때는 콜백이 호출하지 않으므로, 직접 명시적으로 호출한다
    glfwSetFramebufferSizeCallback(window, OnFramebufferSizeChange); // 윈도우의 크기가 변경될때마다 호출되는 콜백함수 등록
    glfwSetKeyCallback(window, OnKeyEvent); // 키보드 입력받을 때마다 호출되는 콜백함수 등록


    // glfw 루프 실행, 윈도우 close 버튼을 누르면 정상 종료
    SPDLOG_INFO("Start main loop");
    // glfwWindowShouldClose()는 윈도우가 닫히는지 확인하는 함수, true면 닫힘
    while (!glfwWindowShouldClose(window)) 
    {
        // glfwPollEvents()는 이벤트를 처리하는 함수, 윈도우가 닫히면 true를 반환
        // 60Hz로 이벤트를 처리(1/60초마다 이벤트를 1번 처리)
        // 이벤트 내용: 윈도우 크기가 변경되거나, 마우스 입력, 키보드 입력을 받는 경우 등
        glfwPollEvents(); 

        // 윈도우를 파란색으로 변경
        glClearColor(0.1f, 0.2f, 0.3f, 0.0f);   // glClearColor()는 윈도우의 배경색을 설정하는 함수, RGBA값을 0.0f ~ 1.0f로 설정
        glClear(GL_COLOR_BUFFER_BIT);   // glClear()는 윈도우를 glClearColor에서 정한 색깔로 지우는 함수, GL_COLOR_BUFFER_BIT는 색상 버퍼를 지우는 플래그
        glfwSwapBuffers(window); // glfwSwapBuffers()는 윈도우의 버퍼를 교체하는 함수, 즉 화면을 업데이트하는 함수
    }
    // glfwTerminate()는 glfw 라이브러리를 종료하는 함수, 윈도우가 닫히면 호출
    glfwTerminate();    

    return 0;
   }