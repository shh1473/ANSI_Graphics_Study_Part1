#include "ansi_input_elements.h"

namespace ansi
{

	/* ������ */
	InputElements::InputElements(unsigned vertexArrayId, unsigned indexBufferId, unsigned vertexCount, unsigned indexCount) :
		m_vertexArrayId(vertexArrayId),
		m_indexBufferId(indexBufferId),
		m_vertexCount(vertexCount),
		m_indexCount(indexCount)
	{

	}

	/* �Ҹ��� */
	InputElements::~InputElements()
	{
		GL_CHECK(glDeleteVertexArrays(1, &m_vertexArrayId));
	}

}
