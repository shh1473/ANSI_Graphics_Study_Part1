#pragma once

#include "common/ansi_common.h"

namespace ansi
{

	/* .shader 파일 로더 클래스 */
	class ShaderLoader
	{
	public:
		/* .shader 파일을 불러오는 함수
		* @param filePath - 파일 경로
		* @param shaderId - 생성된 셰이더 ID
		*/
		static bool Load(const std::string & filePath, unsigned & shaderId);

	private:
		/* 셰이더 단계 */
		enum class ShaderStage
		{
			/* 버텍스 */
			Vertex,
			/* 프래그먼트 */
			Fragment,
			/* 셰이더 단계 개수 */
			length,
		};

	private:
		/* 생성자 (사용하지 않음) */
		explicit ShaderLoader() = delete;

		/* 셰이더 파일을 파싱하는 함수
		* @param filePath - 파일 경로
		* @param sources - 파싱된 코드 배열 (셰이더 단계당 한 개)
		*/
		static bool ParseShader(const std::string & filePath, std::vector<std::string> & sources);
		/* 파싱된 코드를 컴파일하는 함수
		* @param stage - 셰이더 단계
		* @param filePath - 파일 경로
		* @param source - 파싱된 코드
		* @param shaderId - 생성된 셰이더 ID
		*/
		static bool CompileShader(unsigned stage, const std::string & filePath, const std::string & source, unsigned & shaderId);

	};

}
