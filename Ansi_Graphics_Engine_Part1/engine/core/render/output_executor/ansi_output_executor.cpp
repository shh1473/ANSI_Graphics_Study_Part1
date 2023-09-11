#include "ansi_output_executor.h"

namespace ansi
{

	/* 생성자 */
	OutputExecutor::OutputExecutor()
		: m_defaultParam(new OutputParam())
	{

	}

	/* 소멸자 */
	OutputExecutor::~OutputExecutor()
	{
		SAFE_DELETE(m_defaultParam);
	}

	/* OpenGL 컨텍스트의 출력 관련 상태를 적용하는 함수 */
	bool OutputExecutor::Apply(OutputParam * param, bool isClearFramebuffer)
	{
		/* 출력 관련 상태 설정 */
		m_clearDepth.Set(param->GetClearDepth());
		m_clearColor.Set(param->GetClearColor());
		m_viewport.Set(param->GetViewport());
		m_framebufferId.Set(param->GetFramebufferId());

		/* 깊이 초기화 값이 변경되었을 경우 적용 */
		if (m_clearDepth.Check())
		{
			GL_CHECK(glClearDepthf(m_clearDepth.Get()));
			m_clearDepth.Reset();
		}

		/* 색상 초기화 값이 변경되었을 경우 적용 */
		if (m_clearColor.Check())
		{
			GL_CHECK(glClearColor(m_clearColor.Get().r, m_clearColor.Get().g, m_clearColor.Get().b, m_clearColor.Get().a));
			m_clearColor.Reset();
		}

		/* 뷰포트 영역이 변경되었을 경우 적용 */
		if (m_viewport.Check())
		{
			GL_CHECK(glViewport(m_viewport.Get().x, m_viewport.Get().y, m_viewport.Get().z, m_viewport.Get().w));
			m_viewport.Reset();
		}

		/* 프레임버퍼 ID가 변경되었을 경우 적용 */
		if (m_framebufferId.Check())
		{
			GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferId.Get()));
			m_framebufferId.Reset();
		}

		if (isClearFramebuffer)
		{
			/* 깊이 쓰기 허용 */
			GL_CHECK_RF(glDepthMask(true));
			/* 프레임버퍼의 깊이, 색상 초기화 */
			GL_CHECK_RF(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		}

		return true;
	}

	/* OpenGL 컨텍스트의 출력 관련 상태를 초기화하는 함수*/
	bool OutputExecutor::Reset()
	{
		/* 기본 상태 집합 적용 */
		return Apply(m_defaultParam);
	}

}
