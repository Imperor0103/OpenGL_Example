# 외부 파일을 추가하는 부분을 분리했다

# ExternalProject 관련 명령어 셋 추가
include(ExternalProject) 

# Dependency 관련 변수 설정
set(DEP_INSTALL_DIR ${PROJECT_BINARY_DIR}/install)  # Dependency 설치 경로 (빌드 디렉토리의 install 폴더)
set(DEP_INCLUDE_DIR ${DEP_INSTALL_DIR}/include) # Dependency include 경로 (install 폴더의 include 폴더)
set(DEP_LIB_DIR ${DEP_INSTALL_DIR}/lib) # Dependency lib 경로 (install 폴더의 lib 폴더)

# spdlog: fast logger library
# 주소에서 git clone을 통해 소스를 다운받고, CMake를 통해 빌드하여 설치하는 ExternalProject_Add 명령어
# DEP_INSTALL_DIR에 설치되며, DEP_INCLUDE_DIR과 DEP_LIB_DIR에 include와 lib 경로를 설정한다.
ExternalProject_Add(
    dep_spdlog  # Dependency 이름
    GIT_REPOSITORY "https://github.com/gabime/spdlog.git" # git repository 주소
    GIT_TAG "v1.x"  # git tag (버전) 설정
    GIT_SHALLOW 1   # shallow clone (최신 버전만 clone), 1은 true, 0은 false
    UPDATE_COMMAND ""   # git repository 업데이트 명령어 (비워두면 git pull)
    PATCH_COMMAND ""    # git repository 패치 명령어 (비워두면 없음)

    #CMAKE_ARGS: CMake 명령어를 통해 빌드할 때 사용할 옵션들   
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR}    # CMake 설치 경로(DEP_INSTALL_DIR에 저장된 변수 가져와서 사용) 설정
    
    TEST_COMMAND ""   # 테스트 명령어 (비워두면 없음)
)
# Dependency 리스트 및 라이브러리 파일 리스트 추가
set(DEP_LIST ${DEP_LIST} dep_spdlog)
set(DEP_LIBS ${DEP_LIBS} spdlog$<$<CONFIG:Debug>:d>)
# $<>: CMake generator expression (조건부 표현식), 빌드 단계에서 실행된다
# CONFIG:Debug: Debug 모드에서만 실행된다
# $<CONFIG:Debug>:d>는 Debug 모드에서만 d가 붙는다. Release 모드에서는 d를 붙이지 않는다
# 결과물: spdlogd.lib
# 위의 결과물이 DEP_LIBS에 저장

# glfw
ExternalProject_Add(
    dep_glfw
    GIT_REPOSITORY "https://github.com/glfw/glfw.git"
    #GIT_TAG "3.3.3" # glfw 버전
    GIT_TAG "3.4" # glfw 최신 버전
    GIT_SHALLOW 1
    UPDATE_COMMAND "" PATCH_COMMAND "" TEST_COMMAND ""
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR}
        -DGLFW_BUILD_EXAMPLES=OFF
        -DGLFW_BUILD_TESTS=OFF
        -DGLFW_BUILD_DOCS=OFF
    )
set(DEP_LIST ${DEP_LIST} dep_glfw)  # DEP_LIST는 CMakeLists.txt에서 링크된 dependency 리스트
set(DEP_LIBS ${DEP_LIBS} glfw3) # DEP_LIST는 CMakeLists.txt에서 링크된 라이브러리 이름

# glad
ExternalProject_Add(
    dep_glad
    GIT_REPOSITORY "https://github.com/Dav1dde/glad"
    GIT_TAG "v0.1.34"
    GIT_SHALLOW 1
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR}
        -DGLAD_INSTALL=ON
    TEST_COMMAND ""
    )
set(DEP_LIST ${DEP_LIST} dep_glad)
set(DEP_LIBS ${DEP_LIBS} glad)