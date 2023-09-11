#pragma once

#include "input_param/ansi_input_param.h"
#include "utility/state_checker/ansi_state_checker.h"

namespace ansi
{

	/* 입력 실행기 클래스 */
	class InputExecutor
	{
	public:
		/* 생성자 */
		explicit InputExecutor();
		/* 소멸자 */
		~InputExecutor();

		/* OpenGL 컨텍스트의 입력 관련 상태를 적용하는 함수
		* @param param - 입력 관련 상태 집합
		*/
		bool Apply(InputParam * param);
		/* OpenGL 컨텍스트의 입력 관련 상태를 초기화하는 함수 */
		bool Reset();

		/* Getter - 버텍스 개수 */
		unsigned GetVertexCount() const { return m_vertexCount; }
		/* Getter - 인덱스 개수 */
		unsigned GetIndexCount() const { return m_indexCount; }
		/* Getter - 기본 도형 종류 */
		PrimitiveTopology GetPrimitiveTopology() const { return m_primitiveTopology; }

	private:
		/* 기본 상태 집합 */
		InputParam * m_defaultParam;
		/* 버텍스 개수 */
		unsigned m_vertexCount;
		/* 인덱스 개수 */
		unsigned m_indexCount;
		/* 기본 도형 종류 */
		PrimitiveTopology m_primitiveTopology;
		/* 버텍스 배열 ID (상태 검사) */
		StateChecker<unsigned> m_vertexArrayId;
		/* 인덱스 버퍼 ID (상태 검사) */
		StateChecker<unsigned> m_indexBufferId;

	};

}
