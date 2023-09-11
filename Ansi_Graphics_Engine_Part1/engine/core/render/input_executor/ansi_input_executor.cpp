#include "ansi_input_executor.h"

namespace ansi
{

	/* 생성자 */
	InputExecutor::InputExecutor()
		: m_defaultParam(new InputParam())
		, m_vertexCount(0)
		, m_indexCount(0)
		, m_primitiveTopology(m_defaultParam->GetPrimitiveTopology())
	{

	}

	/* 소멸자 */
	InputExecutor::~InputExecutor()
	{
		SAFE_DELETE(m_defaultParam);
	}

	/* OpenGL 컨텍스트의 입력 관련 상태를 적용하는 함수 */
	bool InputExecutor::Apply(InputParam * param)
	{
		/* 입력 관련 상태 설정 */
		m_vertexArrayId.Set(param->GetVertexArrayId());
		m_indexBufferId.Set(param->GetIndexBufferId());
		m_vertexCount = param->GetVertexCount();
		m_indexCount = param->GetIndexCount();
		m_primitiveTopology = param->GetPrimitiveTopology();

		/* 버텍스 배열 ID가 변경되었을 경우 적용 */
		if (m_vertexArrayId.Check())
		{
			GL_CHECK_RF(glBindVertexArray(m_vertexArrayId.Get()));
			m_vertexArrayId.Reset();
		}

		/* 인덱스 버퍼 ID가 변경되었을 경우 적용 */
		if (m_indexBufferId.Check())
		{
			GL_CHECK_RF(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId.Get()));
			m_indexBufferId.Reset();
		}

		return true;
	}

	/* OpenGL 컨텍스트의 입력 관련 상태를 초기화하는 함수*/
	bool InputExecutor::Reset()
	{
		/* 기본 상태 집합 적용 */
		return Apply(m_defaultParam);
	}

}
