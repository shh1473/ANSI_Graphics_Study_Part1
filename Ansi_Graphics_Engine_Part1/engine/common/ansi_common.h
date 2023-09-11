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

#include <iostream>			// Input/Output Stream	- �ٿ뵵
#include <fstream>			// File Stream			- ���̴� �ε�
#include <sstream>			// String Stream		- ���̴� �Ľ�
#include <string>			// String				- ���ڿ� ���� ���
#include <chrono>			// Chrono				- ������ �� �ð� ����
#include <typeindex>		// Type Index			- ������Ʈ Ÿ�� �к�
#include <algorithm>		// Algorithm			- �˰��� ���� ���
#include <functional>		// Functional			- �Լ� ��ü
#include <random>			// Random				- ���� ����
#include <vector>			// Vector				- ���� �迭
#include <unordered_map>	// Unordered Map		- �ؽ� ���̺�

/* ================================================== */
/*                        TYPE                        */
/* ================================================== */

/* ���Ϸ� �� ȸ�� ���� */
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

/* OpenGL �Լ� ���� �� ������ �˻��ϴ� �Լ�
* @param filePath - ������ �߻��� ���� ���
* @param lineNumber - ������ �߻��� ���� ��ȣ
* @returns ������ ���� ��� true
*/
bool CheckGLError(const char * filePath, int lineNumber);

/* GLFW �Լ� ���� �� ������ �˻��ϴ� �Լ�
* @param filePath - ������ �߻��� ���� ���
* @param lineNumber - ������ �߻��� ���� ��ȣ
* @returns ������ ���� ��� true
*/
bool CheckGLFWError(const char * filePath, int lineNumber);

/* ================================================== */
/*                   MISC FUNCTION                    */
/* ================================================== */

/* ���Ϸ� ���� ���ʹϾ����� ��ȯ�ϴ� �Լ�
* @param rotation - ���Ϸ� ��
* @param order - ���Ϸ� �� ȸ�� ����
* @returns ���ʹϾ�
*/
glm::quat EulerToQuat(const glm::vec3 & rotation, EulerOrder order);

/* ================================================== */
/*                       PRINT                        */
/* ================================================== */

/* ���ڿ��� ����ϴ� ��ũ�� �Լ�
* @param - str - ����� ���ڿ�
*/
#define PRINT(str) std::cout << (str) << std::endl;

/* ���ڿ��� �ش� ����, ���� ������ ����ϴ� ��ũ�� �Լ�
* @param - str - ����� ���ڿ�
*/
#define PRINT_FL(str) std::cout << (str) << ", (FILE: " << (__FILE__) << "), (LINE: " << (__LINE__) << ")" << std::endl;

/* ================================================== */
/*                       DELETE                       */
/* ================================================== */

/* �޸� ���� �� nullptr ���� �����ϴ� ��ũ�� �Լ�
* @param ptr - ������
*/
#define SAFE_DELETE(ptr) if (ptr) { delete (ptr); (ptr) = nullptr; }

/* �޸� �迭 ���� �� nullptr ���� �����ϴ� ��ũ�� �Լ�
* @param ptrs - ������ �迭
*/
#define SAFE_DELETE_ARRAY(ptrs) if (ptrs) { delete[] (ptrs); (ptrs) = nullptr; }

/* ================================================== */
/*                       CHECK                        */
/* ================================================== */

/* ǥ������ false�� ��� false ���� ��ȯ�ϴ� ��ũ�� �Լ�
* @param exp - ǥ����
*/
#define CHECK_RF(exp) if (!(exp)) { return false; }

/* ǥ������ false�� ��� nullptr ���� ��ȯ�ϴ� ��ũ�� �Լ�
* @param exp - ǥ����
*/
#define CHECK_RN(exp) if (!(exp)) { return nullptr; }

/* ǥ������ false�� ��� ���ڿ��� �ش� ����, ���� ������ ����ϴ� ��ũ�� �Լ�
* @param exp - ǥ����
* @param str - ����� ���ڿ�
*/
#define CHECK_PRINT(exp, str) if (!(exp)) { PRINT(str); }

/* ǥ������ false�� ��� ���ڿ��� �ش� ����, ���� ������ ����ϰ� false ���� ��ȯ�ϴ� ��ũ�� �Լ�
* @param exp - ǥ����
*/
#define CHECK_PRINT_RF(exp, str) if (!(exp)) { PRINT(str); return false; }

/* ǥ������ false�� ��� ���ڿ��� �ش� ����, ���� ������ ����ϰ� nullptr ���� ��ȯ�ϴ� ��ũ�� �Լ�
* @param exp - ǥ����
*/
#define CHECK_PRINT_RN(exp, str) if (!(exp)) { PRINT(str); return nullptr; }

/* ================================================== */
/*                      GL CHECK                      */
/* ================================================== */

/* OpenGL �Լ����� ������ �߻��ϸ� ���� �޽����� �ش� ����, ���� ������ ����ϴ� ��ũ�� �Լ�
* @param glFunc - OpenGL �Լ�
*/
#define GL_CHECK(glFunc) (glFunc); CheckGLError(__FILE__, __LINE__);

/* OpenGL �Լ����� ������ �߻��ϸ� ���� �޽����� �ش� ����, ���� ������ ����ϰ� false ���� ��ȯ�ϴ� ��ũ�� �Լ�
* @param glFunc - OpenGL �Լ�
*/
#define GL_CHECK_RF(glFunc) (glFunc); CHECK_RF(CheckGLError(__FILE__, __LINE__));

/* OpenGL �Լ����� ������ �߻��ϸ� ���� �޽����� �ش� ����, ���� ������ ����ϰ� nullptr ���� ��ȯ�ϴ� ��ũ�� �Լ�
* @param glFunc - OpenGL �Լ�
*/
#define GL_CHECK_RN(glFunc) (glFunc); CHECK_RN(CheckGLError(__FILE__, __LINE__));

/* ================================================== */
/*                     GLFW CHECK                     */
/* ================================================== */

/* GLFW �Լ����� ������ �߻��ϸ� ���� �޽����� �ش� ����, ���� ������ ����ϰ� false ���� ��ȯ�ϴ� ��ũ�� �Լ�
* @param glfwFunc - GLFW �Լ�
*/
#define GLFW_CHECK(glfwFunc) (glfwFunc); CHECK_RF(CheckGLFWError(__FILE__, __LINE__));
