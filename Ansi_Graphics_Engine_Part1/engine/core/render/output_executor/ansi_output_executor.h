#pragma once

#include "output_param/ansi_output_param.h"
#include "utility/state_checker/ansi_state_checker.h"

namespace ansi
{

	/* 출력 실행기 클래스 */
	class OutputExecutor
	{
	public:
		/* 생성자 */
		explicit OutputExecutor();
		/* 소멸자 */
		~OutputExecutor();

		/* OpenGL 컨텍스트의 출력 관련 상태를 적용하는 함수
		* @param param - 출력 관련 상태 집합
		* @param isClearFramebuffer - 프레임버퍼 내용 초기화 여부 (기본: true)
		*/
		bool Apply(OutputParam * param, bool isClearFramebuffer = true);
		/* OpenGL 컨텍스트의 출력 관련 상태를 초기화하는 함수 */
		bool Reset();

	private:
		/* 기본 상태 집합 */
		OutputParam * m_defaultParam;
		/* 깊이 초기화 값 (상태 검사) */
		StateChecker<float> m_clearDepth;
		/* 색상 초기화 값 (상태 검사) */
		StateChecker<glm::vec4> m_clearColor;
		/* 뷰포트 영역 (상태 검사) */
		StateChecker<glm::ivec4> m_viewport;
		/* 프레임버퍼 ID (상태 검사) */
		StateChecker<unsigned> m_framebufferId;

	};

}
