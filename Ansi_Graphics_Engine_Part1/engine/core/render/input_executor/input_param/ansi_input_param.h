#pragma once

#include "common/ansi_common.h"
#include "common/ansi_common_render.h"

namespace ansi
{

	/* ���� ���� */
	class InputElements;

	/* �Է� ���� ���� ���� Ŭ���� */
	class InputParam
	{
	public:
		/* ������ */
		explicit InputParam();

		/* Setter - ���ؽ� �迭 ID, �ε��� ���� ID, ���ؽ� ����, �ε��� ���� */
		void SetInputElements(InputElements * inputElements);
		/* Setter - �⺻ ���� ���� */
		void SetPrimitiveTopology(PrimitiveTopology primitiveTopology) { m_primitiveTopology = primitiveTopology; }

		/* Getter - ���ؽ� �迭 ID */
		unsigned GetVertexArrayId() const { return m_vertexArrayId; }
		/* Getter - �ε��� ���� ID */
		unsigned GetIndexBufferId() const { return m_indexBufferId; }
		/* Getter - ���ؽ� ���� */
		unsigned GetVertexCount() const { return m_vertexCount; }
		/* Getter - �ε��� ���� */
		unsigned GetIndexCount() const { return m_indexCount; }
		/* Getter - �⺻ ���� ���� */
		PrimitiveTopology GetPrimitiveTopology() const { return m_primitiveTopology; }

	private:
		/* ���ؽ� �迭 ID */
		unsigned m_vertexArrayId;
		/* �ε��� ���� ID */
		unsigned m_indexBufferId;
		/* ���ؽ� ���� */
		unsigned m_vertexCount;
		/* �ε��� ���� */
		unsigned m_indexCount;
		/* �⺻ ���� ���� */
		PrimitiveTopology m_primitiveTopology;

	};

}
