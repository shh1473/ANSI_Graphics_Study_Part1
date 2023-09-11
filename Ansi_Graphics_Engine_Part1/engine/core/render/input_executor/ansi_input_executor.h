#pragma once

#include "input_param/ansi_input_param.h"
#include "utility/state_checker/ansi_state_checker.h"

namespace ansi
{

	/* �Է� ����� Ŭ���� */
	class InputExecutor
	{
	public:
		/* ������ */
		explicit InputExecutor();
		/* �Ҹ��� */
		~InputExecutor();

		/* OpenGL ���ؽ�Ʈ�� �Է� ���� ���¸� �����ϴ� �Լ�
		* @param param - �Է� ���� ���� ����
		*/
		bool Apply(InputParam * param);
		/* OpenGL ���ؽ�Ʈ�� �Է� ���� ���¸� �ʱ�ȭ�ϴ� �Լ� */
		bool Reset();

		/* Getter - ���ؽ� ���� */
		unsigned GetVertexCount() const { return m_vertexCount; }
		/* Getter - �ε��� ���� */
		unsigned GetIndexCount() const { return m_indexCount; }
		/* Getter - �⺻ ���� ���� */
		PrimitiveTopology GetPrimitiveTopology() const { return m_primitiveTopology; }

	private:
		/* �⺻ ���� ���� */
		InputParam * m_defaultParam;
		/* ���ؽ� ���� */
		unsigned m_vertexCount;
		/* �ε��� ���� */
		unsigned m_indexCount;
		/* �⺻ ���� ���� */
		PrimitiveTopology m_primitiveTopology;
		/* ���ؽ� �迭 ID (���� �˻�) */
		StateChecker<unsigned> m_vertexArrayId;
		/* �ε��� ���� ID (���� �˻�) */
		StateChecker<unsigned> m_indexBufferId;

	};

}
