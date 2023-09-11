#pragma once

#include "common/ansi_common.h"
#include "common/ansi_common_render.h"

namespace ansi
{

	/* 출력 관련 상태 집합 클래스 */
	class OutputParam
	{
	public:
		/* 생성자 */
		explicit OutputParam();

		/* Setter - 깊이 초기화 값 */
		void SetClearDepth(float clearDepth) { m_clearDepth = clearDepth; }
		/* Setter - 색상 초기화 값 */
		void SetClearColor(const glm::vec4 & clearColor) { m_clearColor = clearColor; }
		/* Setter - 뷰포트 영역 */
		void SetViewport(const glm::ivec4 & viewport) { m_viewport = viewport; }
		/* Setter - 뷰포트 영역의 X 요소 */
		void SetViewportX(int x) { m_viewport.x = x; }
		/* Setter - 뷰포트 영역의 Y 요소 */
		void SetViewportY(int y) { m_viewport.y = y; }
		/* Setter - 뷰포트 영역의 Z 요소 */
		void SetViewportZ(int z) { m_viewport.z = z; }
		/* Setter - 뷰포트 영역의 W 요소 */
		void SetViewportW(int w) { m_viewport.w = w; }
		/* Setter - 프레임버퍼 ID */
		void SetFramebufferId(unsigned framebufferId) { m_framebufferId = framebufferId; }

		/* Getter - 깊이 초기화 값 */
		float GetClearDepth() const { return m_clearDepth; }
		/* Getter - 색상 초기화 값 */
		const glm::vec4 & GetClearColor() const { return m_clearColor; }
		/* Getter - 뷰포트 영역 */
		const glm::ivec4 & GetViewport() const { return m_viewport; }
		/* Getter - 프레임버퍼 ID */
		unsigned GetFramebufferId() const { return m_framebufferId; }

	private:
		/* 깊이 초기화 값 */
		float m_clearDepth;
		/* 색상 초기화 값 */
		glm::vec4 m_clearColor;
		/* 뷰포트 영역 */
		glm::ivec4 m_viewport;
		/* 프레임버퍼 ID */
		unsigned m_framebufferId;

	};

}
