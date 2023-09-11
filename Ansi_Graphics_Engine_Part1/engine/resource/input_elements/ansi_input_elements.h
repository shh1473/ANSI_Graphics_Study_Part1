#pragma once

#include "common/ansi_common.h"

namespace ansi
{

	/* �Է� ��� Ŭ���� */
	class InputElements
	{
	public:
		/* ������
		* @param vertexArrayId - ���ؽ� �迭 ID
		* @param indexBufferId - �ε��� ���� ID
		* @param vertexCount - ���ؽ� ����
		* @param indexCount - �ε��� ����
		*/
		explicit InputElements(unsigned vertexArrayId, unsigned indexBufferId, unsigned vertexCount, unsigned indexCount);
		/* �Ҹ��� */
		virtual ~InputElements();

		/* Getter - ���ؽ� �迭 ID */
		unsigned GetVertexArrayId() const { return m_vertexArrayId; }
		/* Getter - �ε��� ���� ID */
		unsigned GetIndexBufferId() const { return m_indexBufferId; }
		/* Getter - ���ؽ� ���� */
		unsigned GetVertexCount() const { return m_vertexCount; }
		/* Getter - �ε��� ���� */
		unsigned GetIndexCount() const { return m_indexCount; }

	private:
		/* ���ؽ� �迭 ID */
		unsigned m_vertexArrayId;
		/* �ε��� ���� ID */
		unsigned m_indexBufferId;
		/* ���ؽ� ���� */
		unsigned m_vertexCount;
		/* �ε��� ���� */
		unsigned m_indexCount;

	};

}
