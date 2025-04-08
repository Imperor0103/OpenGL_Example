# cmake_minimum_required(VERSION 3.14)
cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME OpenGL_Example)
set(CMAKE_CXX_STANDARD 17) 

# 생성할 윈도우 세팅(이름, 크기)
set(WINDOW_NAME "OpenGL Example")
set(WINDOW_WIDTH 960)
set(WINDOW_HEIGHT 540)


project(${PROJECT_NAME})

# MSVC일 경우 소스 파일을 UTF-8로 컴파일
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_executable(${PROJECT_NAME} src/main.cpp) 
#  src/main.cpp을 컴파일해서 PROJECT_NAME이름의 실행파일을 만들어라

include(Dependency.cmake)

# 우리 프로젝트에 include / lib 관련 옵션 추가
target_include_directories(${PROJECT_NAME} PUBLIC ${DEP_INCLUDE_DIR})   # DEP_INSTALL_DIR 디렉터리를 include로 포함해야, 그 안에 있는 spdlog.h를 사용할 수 있다
# target은 프로젝트 이름 OpenGL_Practice으로 만든 실행파일

target_link_directories(${PROJECT_NAME} PUBLIC ${DEP_LIB_DIR})  # DEP_INSTALL_DIR 디렉터리를 link해야 그 안에 있는 spdlog.lib를 사용할 수 있다
# link의 과정: 그 라이브러리 안에 들어있는 binary 코드들(컴파일 된 코드 뭉치) 실행파일에 copy해서 옮긴다

target_link_libraries(${PROJECT_NAME} PUBLIC ${DEP_LIBS})   # 실제로 사용할 라이브러리 파일(spdlogd)을 지정하는 명령어 (확장자 lib는 제거)

# target_compile_definitions을 사용하면 아래의 코드를 main.cpp에서 define 매크로를 사용하지 않아도 된다
#define WINDOW_NAME "OpenGL Practice!"
#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 540
target_compile_definitions(${PROJECT_NAME} PUBLIC #  PROJECT_NAME: 프로젝트 이름
WINDOW_NAME="${WINDOW_NAME}"
WINDOW_WIDTH=${WINDOW_WIDTH}
WINDOW_HEIGHT=${WINDOW_HEIGHT}
)

# Dependency들이 먼저 build 될 수 있게 관계 설정
add_dependencies(${PROJECT_NAME} ${DEP_LIST})   # ${PROJECT_NAME}이 build 되기 전에 ${DEP_LIST}에 있는 Dependency들이 먼저 build 되어야 한다는 명령어
# 위의 명령어를 빠뜨리면 lib들이 install 되지 않은 상태에서 compile이 진행되어 오류가 발생할 수 있다

