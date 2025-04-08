#include <spdlog/spdlog.h>
#include <GLFW/glfw3.h>


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

    // glfw 루프 실행, 윈도우 close 버튼을 누르면 정상 종료
    SPDLOG_INFO("Start main loop");
    // glfwWindowShouldClose()는 윈도우가 닫히는지 확인하는 함수, true면 닫힘
    while (!glfwWindowShouldClose(window)) 
    {
        // glfwPollEvents()는 이벤트를 처리하는 함수, 윈도우가 닫히면 true를 반환
        // 60Hz로 이벤트를 처리(1/60초마다 이벤트를 1번 처리)
        glfwPollEvents(); 
    }
    // glfwTerminate()는 glfw 라이브러리를 종료하는 함수, 윈도우가 닫히면 호출
    glfwTerminate();    

    return 0;
}