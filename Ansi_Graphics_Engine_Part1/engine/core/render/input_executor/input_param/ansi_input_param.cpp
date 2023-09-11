#include "ansi_input_param.h"

#include "resource/input_elements/ansi_input_elements.h"

namespace ansi
{

	/* 생성자 */
	InputParam::InputParam()
		: m_vertexArrayId(0)
		, m_indexBufferId(0)
		, m_vertexCount(0)
		, m_indexCount(0)
		, m_primitiveTopology(PrimitiveTopology::Triangles)
	{

	}

	/* Setter - 버텍스 배열 ID, 인덱스 버퍼 ID, 버텍스 개수, 인덱스 개수 */
	void InputParam::SetInputElements(InputElements * inputElements)
	{
		m_vertexArrayId = inputElements->GetVertexArrayId();
		m_indexBufferId = inputElements->GetIndexBufferId();
		m_vertexCount = inputElements->GetVertexCount();
		m_indexCount = inputElements->GetIndexCount();
	}

}
