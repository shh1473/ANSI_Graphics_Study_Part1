#include "ansi_output_executor.h"

namespace ansi
{

	/* ������ */
	OutputExecutor::OutputExecutor()
		: m_defaultParam(new OutputParam())
	{

	}

	/* �Ҹ��� */
	OutputExecutor::~OutputExecutor()
	{
		SAFE_DELETE(m_defaultParam);
	}

	/* OpenGL ���ؽ�Ʈ�� ��� ���� ���¸� �����ϴ� �Լ� */
	bool OutputExecutor::Apply(OutputParam * param, bool isClearFramebuffer)
	{
		/* ��� ���� ���� ���� */
		m_clearDepth.Set(param->GetClearDepth());
		m_clearColor.Set(param->GetClearColor());
		m_viewport.Set(param->GetViewport());
		m_framebufferId.Set(param->GetFramebufferId());

		/* ���� �ʱ�ȭ ���� ����Ǿ��� ��� ���� */
		if (m_clearDepth.Check())
		{
			GL_CHECK(glClearDepthf(m_clearDepth.Get()));
			m_clearDepth.Reset();
		}

		/* ���� �ʱ�ȭ ���� ����Ǿ��� ��� ���� */
		if (m_clearColor.Check())
		{
			GL_CHECK(glClearColor(m_clearColor.Get().r, m_clearColor.Get().g, m_clearColor.Get().b, m_clearColor.Get().a));
			m_clearColor.Reset();
		}

		/* ����Ʈ ������ ����Ǿ��� ��� ���� */
		if (m_viewport.Check())
		{
			GL_CHECK(glViewport(m_viewport.Get().x, m_viewport.Get().y, m_viewport.Get().z, m_viewport.Get().w));
			m_viewport.Reset();
		}

		/* �����ӹ��� ID�� ����Ǿ��� ��� ���� */
		if (m_framebufferId.Check())
		{
			GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferId.Get()));
			m_framebufferId.Reset();
		}

		if (isClearFramebuffer)
		{
			/* ���� ���� ��� */
			GL_CHECK_RF(glDepthMask(true));
			/* �����ӹ����� ����, ���� �ʱ�ȭ */
			GL_CHECK_RF(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		}

		return true;
	}

	/* OpenGL ���ؽ�Ʈ�� ��� ���� ���¸� �ʱ�ȭ�ϴ� �Լ�*/
	bool OutputExecutor::Reset()
	{
		/* �⺻ ���� ���� ���� */
		return Apply(m_defaultParam);
	}

}
