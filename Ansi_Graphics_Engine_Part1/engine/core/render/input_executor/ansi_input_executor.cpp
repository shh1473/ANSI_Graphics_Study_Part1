#include "ansi_input_executor.h"

namespace ansi
{

	/* ������ */
	InputExecutor::InputExecutor()
		: m_defaultParam(new InputParam())
		, m_vertexCount(0)
		, m_indexCount(0)
		, m_primitiveTopology(m_defaultParam->GetPrimitiveTopology())
	{

	}

	/* �Ҹ��� */
	InputExecutor::~InputExecutor()
	{
		SAFE_DELETE(m_defaultParam);
	}

	/* OpenGL ���ؽ�Ʈ�� �Է� ���� ���¸� �����ϴ� �Լ� */
	bool InputExecutor::Apply(InputParam * param)
	{
		/* �Է� ���� ���� ���� */
		m_vertexArrayId.Set(param->GetVertexArrayId());
		m_indexBufferId.Set(param->GetIndexBufferId());
		m_vertexCount = param->GetVertexCount();
		m_indexCount = param->GetIndexCount();
		m_primitiveTopology = param->GetPrimitiveTopology();

		/* ���ؽ� �迭 ID�� ����Ǿ��� ��� ���� */
		if (m_vertexArrayId.Check())
		{
			GL_CHECK_RF(glBindVertexArray(m_vertexArrayId.Get()));
			m_vertexArrayId.Reset();
		}

		/* �ε��� ���� ID�� ����Ǿ��� ��� ���� */
		if (m_indexBufferId.Check())
		{
			GL_CHECK_RF(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId.Get()));
			m_indexBufferId.Reset();
		}

		return true;
	}

	/* OpenGL ���ؽ�Ʈ�� �Է� ���� ���¸� �ʱ�ȭ�ϴ� �Լ�*/
	bool InputExecutor::Reset()
	{
		/* �⺻ ���� ���� ���� */
		return Apply(m_defaultParam);
	}

}
