#pragma once

#include "output_param/ansi_output_param.h"
#include "utility/state_checker/ansi_state_checker.h"

namespace ansi
{

	/* ��� ����� Ŭ���� */
	class OutputExecutor
	{
	public:
		/* ������ */
		explicit OutputExecutor();
		/* �Ҹ��� */
		~OutputExecutor();

		/* OpenGL ���ؽ�Ʈ�� ��� ���� ���¸� �����ϴ� �Լ�
		* @param param - ��� ���� ���� ����
		* @param isClearFramebuffer - �����ӹ��� ���� �ʱ�ȭ ���� (�⺻: true)
		*/
		bool Apply(OutputParam * param, bool isClearFramebuffer = true);
		/* OpenGL ���ؽ�Ʈ�� ��� ���� ���¸� �ʱ�ȭ�ϴ� �Լ� */
		bool Reset();

	private:
		/* �⺻ ���� ���� */
		OutputParam * m_defaultParam;
		/* ���� �ʱ�ȭ �� (���� �˻�) */
		StateChecker<float> m_clearDepth;
		/* ���� �ʱ�ȭ �� (���� �˻�) */
		StateChecker<glm::vec4> m_clearColor;
		/* ����Ʈ ���� (���� �˻�) */
		StateChecker<glm::ivec4> m_viewport;
		/* �����ӹ��� ID (���� �˻�) */
		StateChecker<unsigned> m_framebufferId;

	};

}
