#pragma once

/* PROJECT INFO
* 
* >====< GENERAL >====<
* Name: A.N.S.I Graphics Engine Part 1
* Creator: Suhyeon Han
* Created: 2023.09.01
* IDE: Visual Studio 2022 (C++ and OpenGL)
* 
* >====< LICENSE >====<
* MIT License
* Copyright (c) 2023 Suhyeon Han
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
* 
*/

/* ================================================== */
/*                     DEPENDENCY                     */
/* ================================================== */

/* GLEW - OpenGL Extension Wrangler Library */
#include <gl/glew.h>

/* GLFW - Graphics Library Framework */
#include <glfw/glfw3.h>

/* GLM - OpenGL Mathematics */
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

/* IMGUI - GUI Interface */
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

/* TINY OBJ LOADER - OBJ File Loader */
#include <tiny_obj_loader.h>

/* VLD - Visual Leak Detector */
#ifdef _DEBUG
#include <vld.h>
#endif

/* ================================================== */
/*                    C++ STANDARD                    */
/* ================================================== */

#include <iostream>			// Input/Output Stream	- 다용도
#include <fstream>			// File Stream			- 셰이더 로드
#include <sstream>			// String Stream		- 셰이더 파싱
#include <string>			// String				- 문자열 관련 기능
#include <chrono>			// Chrono				- 프레임 간 시간 측정
#include <typeindex>		// Type Index			- 컴포넌트 타입 분별
#include <algorithm>		// Algorithm			- 알고리즘 관련 기능
#include <functional>		// Functional			- 함수 객체
#include <random>			// Random				- 난수 생성
#include <vector>			// Vector				- 동적 배열
#include <unordered_map>	// Unordered Map		- 해시 테이블

/* ================================================== */
/*                        TYPE                        */
/* ================================================== */

/* 오일러 각 회전 순서 */
enum class EulerOrder { XYZ, XZY, YXZ, YZX, ZXY, ZYX };

/* ================================================== */
/*                      CONSTANT                      */
/* ================================================== */

/* PI */
constexpr float PI{ 3.1415927f };
/* PI * 2 */
constexpr float PI2{ 6.2831853f };

/* ================================================== */
/*                ERROR CHECK FUNTION                 */
/* ================================================== */

/* OpenGL 함수 실행 후 에러를 검사하는 함수
* @param filePath - 에러가 발생한 파일 경로
* @param lineNumber - 에러가 발생한 라인 번호
* @returns 에러가 없을 경우 true
*/
bool CheckGLError(const char * filePath, int lineNumber);

/* GLFW 함수 실행 후 에러를 검사하는 함수
* @param filePath - 에러가 발생한 파일 경로
* @param lineNumber - 에러가 발생한 라인 번호
* @returns 에러가 없을 경우 true
*/
bool CheckGLFWError(const char * filePath, int lineNumber);

/* ================================================== */
/*                   MISC FUNCTION                    */
/* ================================================== */

/* 오일러 각을 쿼터니언으로 변환하는 함수
* @param rotation - 오일러 각
* @param order - 오일러 각 회전 순서
* @returns 쿼터니언
*/
glm::quat EulerToQuat(const glm::vec3 & rotation, EulerOrder order);

/* ================================================== */
/*                       PRINT                        */
/* ================================================== */

/* 문자열을 출력하는 매크로 함수
* @param - str - 출력할 문자열
*/
#define PRINT(str) std::cout << (str) << std::endl;

/* 문자열과 해당 파일, 라인 정보를 출력하는 매크로 함수
* @param - str - 출력할 문자열
*/
#define PRINT_FL(str) std::cout << (str) << ", (FILE: " << (__FILE__) << "), (LINE: " << (__LINE__) << ")" << std::endl;

/* ================================================== */
/*                       DELETE                       */
/* ================================================== */

/* 메모리 해제 후 nullptr 값을 대입하는 매크로 함수
* @param ptr - 포인터
*/
#define SAFE_DELETE(ptr) if (ptr) { delete (ptr); (ptr) = nullptr; }

/* 메모리 배열 해제 후 nullptr 값을 대입하는 매크로 함수
* @param ptrs - 포인터 배열
*/
#define SAFE_DELETE_ARRAY(ptrs) if (ptrs) { delete[] (ptrs); (ptrs) = nullptr; }

/* ================================================== */
/*                       CHECK                        */
/* ================================================== */

/* 표현식이 false일 경우 false 값을 반환하는 매크로 함수
* @param exp - 표현식
*/
#define CHECK_RF(exp) if (!(exp)) { return false; }

/* 표현식이 false일 경우 nullptr 값을 반환하는 매크로 함수
* @param exp - 표현식
*/
#define CHECK_RN(exp) if (!(exp)) { return nullptr; }

/* 표현식이 false일 경우 문자열과 해당 파일, 라인 정보를 출력하는 매크로 함수
* @param exp - 표현식
* @param str - 출력할 문자열
*/
#define CHECK_PRINT(exp, str) if (!(exp)) { PRINT(str); }

/* 표현식이 false일 경우 문자열과 해당 파일, 라인 정보를 출력하고 false 값을 반환하는 매크로 함수
* @param exp - 표현식
*/
#define CHECK_PRINT_RF(exp, str) if (!(exp)) { PRINT(str); return false; }

/* 표현식이 false일 경우 문자열과 해당 파일, 라인 정보를 출력하고 nullptr 값을 반환하는 매크로 함수
* @param exp - 표현식
*/
#define CHECK_PRINT_RN(exp, str) if (!(exp)) { PRINT(str); return nullptr; }

/* ================================================== */
/*                      GL CHECK                      */
/* ================================================== */

/* OpenGL 함수에서 에러가 발생하면 에러 메시지와 해당 파일, 라인 정보를 출력하는 매크로 함수
* @param glFunc - OpenGL 함수
*/
#define GL_CHECK(glFunc) (glFunc); CheckGLError(__FILE__, __LINE__);

/* OpenGL 함수에서 에러가 발생하면 에러 메시지와 해당 파일, 라인 정보를 출력하고 false 값을 반환하는 매크로 함수
* @param glFunc - OpenGL 함수
*/
#define GL_CHECK_RF(glFunc) (glFunc); CHECK_RF(CheckGLError(__FILE__, __LINE__));

/* OpenGL 함수에서 에러가 발생하면 에러 메시지와 해당 파일, 라인 정보를 출력하고 nullptr 값을 반환하는 매크로 함수
* @param glFunc - OpenGL 함수
*/
#define GL_CHECK_RN(glFunc) (glFunc); CHECK_RN(CheckGLError(__FILE__, __LINE__));

/* ================================================== */
/*                     GLFW CHECK                     */
/* ================================================== */

/* GLFW 함수에서 에러가 발생하면 에러 메시지와 해당 파일, 라인 정보를 출력하고 false 값을 반환하는 매크로 함수
* @param glfwFunc - GLFW 함수
*/
#define GLFW_CHECK(glfwFunc) (glfwFunc); CHECK_RF(CheckGLFWError(__FILE__, __LINE__));
