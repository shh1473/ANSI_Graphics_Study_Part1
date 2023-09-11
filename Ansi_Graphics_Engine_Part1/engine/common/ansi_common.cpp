#include "ansi_common.h"

/* 표현식과 해당 파일, 라인 정보를 조합해 에러 문자열을 생성하는 함수
* @param expression - 표현식
* @param filePath - 파일 경로
* @param lineNumber - 라인 번호
* @returns 조합된 에러 문자열
*/
inline std::string MakeErrorString(const char * expression, const char * filePath, int lineNumber)
{
	return std::string(expression) + " | " + std::string(filePath) + " | " + std::to_string(lineNumber);
}

/* OpenGL 함수 실행 후 에러를 검사하는 함수 */
bool CheckGLError(const char * filePath, int lineNumber)
{
	GLenum error = glGetError();
	if (error == GL_NO_ERROR) { return true; }

	std::string errorString{ "[OpenGL Error] (" + std::to_string(error) + ")" };
	PRINT(MakeErrorString(errorString.c_str(), filePath, lineNumber));

	return false;
}

/* GLFW 함수 실행 후 에러를 검사하는 함수 */
bool CheckGLFWError(const char * filePath, int lineNumber)
{
	const char * errorMessage{ nullptr };
	int error = glfwGetError(&errorMessage);
	if (error == GLFW_NO_ERROR) { return true; }

	std::string errorString{ "[GLFW Error] (" + std::to_string(error) + ", " + errorMessage + ")" };
	PRINT(MakeErrorString(errorString.c_str(), filePath, lineNumber));

	return false;
}

/* 오일러 각을 쿼터니언으로 변환하는 함수 */
glm::quat EulerToQuat(const glm::vec3 & rotation, EulerOrder order)
{
	static glm::vec3 radianRotation(0.0f);
	static glm::quat result(1.0f, 0.0f, 0.0f, 0.0f);

	radianRotation = glm::radians(rotation);
	const float c1 = cosf(radianRotation.x * 0.5f);
	const float c2 = cosf(radianRotation.y * 0.5f);
	const float c3 = cosf(radianRotation.z * 0.5f);
	const float s1 = sinf(radianRotation.x * 0.5f);
	const float s2 = sinf(radianRotation.y * 0.5f);
	const float s3 = sinf(radianRotation.z * 0.5f);

	switch (order)
	{
		case EulerOrder::XYZ:
		{
			result.x = s1 * c2 * c3 + c1 * s2 * s3;
			result.y = c1 * s2 * c3 - s1 * c2 * s3;
			result.z = c1 * c2 * s3 + s1 * s2 * c3;
			result.w = c1 * c2 * c3 - s1 * s2 * s3;
		} break;
		case EulerOrder::YXZ:
		{
			result.x = s1 * c2 * c3 + c1 * s2 * s3;
			result.y = c1 * s2 * c3 - s1 * c2 * s3;
			result.z = c1 * c2 * s3 - s1 * s2 * c3;
			result.w = c1 * c2 * c3 + s1 * s2 * s3;
		} break;
		case EulerOrder::ZXY:
		{
			result.x = s1 * c2 * c3 - c1 * s2 * s3;
			result.y = c1 * s2 * c3 + s1 * c2 * s3;
			result.z = c1 * c2 * s3 + s1 * s2 * c3;
			result.w = c1 * c2 * c3 - s1 * s2 * s3;
		} break;
		case EulerOrder::ZYX:
		{
			result.x = s1 * c2 * c3 - c1 * s2 * s3;
			result.y = c1 * s2 * c3 + s1 * c2 * s3;
			result.z = c1 * c2 * s3 - s1 * s2 * c3;
			result.w = c1 * c2 * c3 + s1 * s2 * s3;
		} break;
		case EulerOrder::YZX:
		{
			result.x = s1 * c2 * c3 + c1 * s2 * s3;
			result.y = c1 * s2 * c3 + s1 * c2 * s3;
			result.z = c1 * c2 * s3 - s1 * s2 * c3;
			result.w = c1 * c2 * c3 - s1 * s2 * s3;
		} break;
		case EulerOrder::XZY:
		{
			result.x = s1 * c2 * c3 - c1 * s2 * s3;
			result.y = c1 * s2 * c3 - s1 * c2 * s3;
			result.z = c1 * c2 * s3 + s1 * s2 * c3;
			result.w = c1 * c2 * c3 + s1 * s2 * s3;
		} break;
	}

	return result;
}
