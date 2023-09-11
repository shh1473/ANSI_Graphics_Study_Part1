#pragma once

#include "common/ansi_common.h"

namespace ansi
{

	/* 입력 요소 클래스 */
	class InputElements
	{
	public:
		/* 생성자
		* @param vertexArrayId - 버텍스 배열 ID
		* @param indexBufferId - 인덱스 버퍼 ID
		* @param vertexCount - 버텍스 개수
		* @param indexCount - 인덱스 개수
		*/
		explicit InputElements(unsigned vertexArrayId, unsigned indexBufferId, unsigned vertexCount, unsigned indexCount);
		/* 소멸자 */
		virtual ~InputElements();

		/* Getter - 버텍스 배열 ID */
		unsigned GetVertexArrayId() const { return m_vertexArrayId; }
		/* Getter - 인덱스 버퍼 ID */
		unsigned GetIndexBufferId() const { return m_indexBufferId; }
		/* Getter - 버텍스 개수 */
		unsigned GetVertexCount() const { return m_vertexCount; }
		/* Getter - 인덱스 개수 */
		unsigned GetIndexCount() const { return m_indexCount; }

	private:
		/* 버텍스 배열 ID */
		unsigned m_vertexArrayId;
		/* 인덱스 버퍼 ID */
		unsigned m_indexBufferId;
		/* 버텍스 개수 */
		unsigned m_vertexCount;
		/* 인덱스 개수 */
		unsigned m_indexCount;

	};

}
