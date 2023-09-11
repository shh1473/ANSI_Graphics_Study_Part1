#pragma once

#include "common/ansi_common.h"
#include "common/ansi_common_render.h"

namespace ansi
{

	/* ��� ���� ���� ���� Ŭ���� */
	class OutputParam
	{
	public:
		/* ������ */
		explicit OutputParam();

		/* Setter - ���� �ʱ�ȭ �� */
		void SetClearDepth(float clearDepth) { m_clearDepth = clearDepth; }
		/* Setter - ���� �ʱ�ȭ �� */
		void SetClearColor(const glm::vec4 & clearColor) { m_clearColor = clearColor; }
		/* Setter - ����Ʈ ���� */
		void SetViewport(const glm::ivec4 & viewport) { m_viewport = viewport; }
		/* Setter - ����Ʈ ������ X ��� */
		void SetViewportX(int x) { m_viewport.x = x; }
		/* Setter - ����Ʈ ������ Y ��� */
		void SetViewportY(int y) { m_viewport.y = y; }
		/* Setter - ����Ʈ ������ Z ��� */
		void SetViewportZ(int z) { m_viewport.z = z; }
		/* Setter - ����Ʈ ������ W ��� */
		void SetViewportW(int w) { m_viewport.w = w; }
		/* Setter - �����ӹ��� ID */
		void SetFramebufferId(unsigned framebufferId) { m_framebufferId = framebufferId; }

		/* Getter - ���� �ʱ�ȭ �� */
		float GetClearDepth() const { return m_clearDepth; }
		/* Getter - ���� �ʱ�ȭ �� */
		const glm::vec4 & GetClearColor() const { return m_clearColor; }
		/* Getter - ����Ʈ ���� */
		const glm::ivec4 & GetViewport() const { return m_viewport; }
		/* Getter - �����ӹ��� ID */
		unsigned GetFramebufferId() const { return m_framebufferId; }

	private:
		/* ���� �ʱ�ȭ �� */
		float m_clearDepth;
		/* ���� �ʱ�ȭ �� */
		glm::vec4 m_clearColor;
		/* ����Ʈ ���� */
		glm::ivec4 m_viewport;
		/* �����ӹ��� ID */
		unsigned m_framebufferId;

	};

}
