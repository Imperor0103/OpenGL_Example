#ifndef __COMMON_H__
#define __COMMON_H__

#include <memory>
#include <string>
#include <optional>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <spdlog/spdlog.h>

// define으로 정의한 매크로 함수
// CLASS_PTR는 매크로 함수 (예시: CLASS_PTR(MyClass) -> MyClass)
// std::unique_ptr 대신 클래스이름UPtr 사용
#define CLASS_PTR(klassName) \
class klassName; \
using klassName ## UPtr = std::unique_ptr<klassName>; \
using klassName ## Ptr = std::shared_ptr<klassName>; \
using klassName ## WPtr = std::weak_ptr<klassName>;
// #define CLASS_PTR(klassName): 클래스 이름을 기반으로 스마트 포인터 타입을 정의하는 매크로
// using을 통해 alias 만든다
// ##는 매크로 치환 연산자로, klassName 뒤에 UPtr, Ptr, WPtr를 붙여서 각각 unique_ptr, shared_ptr, weak_ptr 타입을 정의합니다.  
// \는 줄바꿈을 방지하는 역할을 합니다.
// 사용 예시
// CLASS_PTR(Shader);
// class Shader; \
// using ShaderUPtr = std::unique_ptr<Shader>;  // 타입 앨리어싱 
// using ShaderPtr = std::shared_ptr<Shader>;   // 타입 앨리어싱
// using ShaderWPtr = std::weak_ptr<Shader>;    // 타입 앨리어싱


// optional은 C++17부터 추가된 기능으로, 값이 있을 수도 있고 없을 수도 있는 경우에 사용합니다.
// optional 나오기 전에는 빈 텍스트인 경우에 string*를 리턴받아 사용했지만
// 메모리 누수의 위험이 있고, nullptr 체크를 해야하는 불편함이 있었습니다.
// 따라서, C++17부터는 std::optional을 사용하여 값이 없을 수도 있는 경우를 안전하게 처리할 수 있습니다.
// std::string* LoadTextFile(const std::string& filename);  
// 대신 std::optional<std::string>을 사용하여 파일이 없을 경우에도 안전하게 처리할 수 있습니다.
std::optional<std::string> LoadTextFile(const std::string& filename);

#endif // __COMMON_H__