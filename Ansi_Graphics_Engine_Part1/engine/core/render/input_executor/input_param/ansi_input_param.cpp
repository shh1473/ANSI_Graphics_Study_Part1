#include "ansi_input_param.h"

#include "resource/input_elements/ansi_input_elements.h"

namespace ansi
{

	/* ������ */
	InputParam::InputParam()
		: m_vertexArrayId(0)
		, m_indexBufferId(0)
		, m_vertexCount(0)
		, m_indexCount(0)
		, m_primitiveTopology(PrimitiveTopology::Triangles)
	{

	}

	/* Setter - ���ؽ� �迭 ID, �ε��� ���� ID, ���ؽ� ����, �ε��� ���� */
	void InputParam::SetInputElements(InputElements * inputElements)
	{
		m_vertexArrayId = inputElements->GetVertexArrayId();
		m_indexBufferId = inputElements->GetIndexBufferId();
		m_vertexCount = inputElements->GetVertexCount();
		m_indexCount = inputElements->GetIndexCount();
	}

}
