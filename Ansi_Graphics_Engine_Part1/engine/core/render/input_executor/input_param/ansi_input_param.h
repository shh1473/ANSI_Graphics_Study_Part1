#pragma once

#include "common/ansi_common.h"
#include "common/ansi_common_render.h"

namespace ansi
{

	/* 전방 선언 */
	class InputElements;

	/* 입력 관련 상태 집합 클래스 */
	class InputParam
	{
	public:
		/* 생성자 */
		explicit InputParam();

		/* Setter - 버텍스 배열 ID, 인덱스 버퍼 ID, 버텍스 개수, 인덱스 개수 */
		void SetInputElements(InputElements * inputElements);
		/* Setter - 기본 도형 종류 */
		void SetPrimitiveTopology(PrimitiveTopology primitiveTopology) { m_primitiveTopology = primitiveTopology; }

		/* Getter - 버텍스 배열 ID */
		unsigned GetVertexArrayId() const { return m_vertexArrayId; }
		/* Getter - 인덱스 버퍼 ID */
		unsigned GetIndexBufferId() const { return m_indexBufferId; }
		/* Getter - 버텍스 개수 */
		unsigned GetVertexCount() const { return m_vertexCount; }
		/* Getter - 인덱스 개수 */
		unsigned GetIndexCount() const { return m_indexCount; }
		/* Getter - 기본 도형 종류 */
		PrimitiveTopology GetPrimitiveTopology() const { return m_primitiveTopology; }

	private:
		/* 버텍스 배열 ID */
		unsigned m_vertexArrayId;
		/* 인덱스 버퍼 ID */
		unsigned m_indexBufferId;
		/* 버텍스 개수 */
		unsigned m_vertexCount;
		/* 인덱스 개수 */
		unsigned m_indexCount;
		/* 기본 도형 종류 */
		PrimitiveTopology m_primitiveTopology;

	};

}
