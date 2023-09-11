#include "ansi_shader_executor.h"

namespace ansi
{

	/* 생성자 */
	ShaderExecutor::ShaderExecutor()
		: m_defaultMaterial(new Material(0))
		, m_isEnableDepthWrite(m_defaultMaterial->GetIsEnableDepthWrite())
	{

	}

	/* 소멸자 */
	ShaderExecutor::~ShaderExecutor()
	{
		SAFE_DELETE(m_defaultMaterial);
	}

	/* OpenGL 컨텍스트의 셰이더 관련 상태를 적용하는 함수 */
	bool ShaderExecutor::Apply(Material * material)
	{
		/* 셰이더 관련 상태 설정 */
		m_shaderId.Set(material->GetShaderId());
		for (unsigned i{ 0 }; i < MaxTextureCount; ++i)
		{
			m_textureIds.Set(i, material->GetTextureId(i));
			m_textureTypes.Set(i, static_cast<unsigned>(material->GetTextureType(i)));
		}
		m_isEnableDepthTest.Set(material->GetIsEnableDepthTest());
		m_isEnableDepthWrite = material->GetIsEnableDepthWrite();
		m_depthFunc.Set(material->GetDepthFunc());
		m_fillMode.Set(material->GetFillMode());
		m_cullMode.Set(material->GetCullMode());
		m_frontFace.Set(material->GetFrontFace());

		/* 셰이더 ID가 변경되었을 경우 적용 */
		if (m_shaderId.Check())
		{
			GL_CHECK(glUseProgram(m_shaderId.Get()));
			m_shaderId.Reset();
		}

		/* 텍스처 ID 또는 종류가 변경되었을 경우 적용 */
		if (m_textureIds.Check() || m_textureTypes.Check())
		{
			for (int i{ 0 }; i < MaxTextureCount; ++i)
			{
				GL_CHECK(glActiveTexture(GL_TEXTURE0 + i));
				GL_CHECK(glBindTexture(m_textureTypes.Get(i), m_textureIds.Get(i)));
			}
			m_textureIds.Reset();
			m_textureTypes.Reset();
		}

		/* 깊이 쓰기 여부 적용 (프레임버퍼의 깊이 초기화에서 깊이 쓰기를 강제로 켜므로, 상태 검사를 하지 않고 항상 적용) */
		GL_CHECK(glDepthMask(m_isEnableDepthWrite ? GL_TRUE : GL_FALSE));

		/* 깊이 테스트 활성화 여부가 변경되었을 경우 적용 */
		if (m_isEnableDepthTest.Check())
		{
			if (m_isEnableDepthTest.Get()) { GL_CHECK(glEnable(GL_DEPTH_TEST)); }
			else { GL_CHECK(glDisable(GL_DEPTH_TEST)); }
			m_isEnableDepthTest.Reset();
		}

		/* 깊이 비교 함수가 변경되었을 경우 적용 */
		if (m_depthFunc.Check())
		{
			GL_CHECK(glDepthFunc(static_cast<unsigned>(m_depthFunc.Get())));
			m_depthFunc.Reset();
		}

		/* 삼각형 채우기 모드가 변경되었을 경우 적용 */
		if (m_fillMode.Check())
		{
			GL_CHECK(glPolygonMode(GL_FRONT_AND_BACK, static_cast<unsigned>(m_fillMode.Get())));
			m_fillMode.Reset();
		}

		/* 삼각형 컬링 모드가 변경되었을 경우 적용 */
		if (m_cullMode.Check())
		{
			if (m_cullMode.Get() == CullMode::None)
			{
				GL_CHECK(glDisable(GL_CULL_FACE));
			}
			else
			{
				GL_CHECK(glEnable(GL_CULL_FACE));
				GL_CHECK(glCullFace(static_cast<unsigned>(m_cullMode.Get())));
			}
			m_cullMode.Reset();
		}

		/* 삼각형 앞면 판정 방향이 변경되었을 경우 적용 */
		if (m_frontFace.Check())
		{
			GL_CHECK(glFrontFace(static_cast<unsigned>(m_frontFace.Get())));
			m_frontFace.Reset();
		}

		/* 유니폼 업데이트 */
		CHECK_RF(material->OnUpdateUniforms());

		return true;
	}

	/* OpenGL 컨텍스트의 출력 관련 상태를 초기화하는 함수 */
	bool ShaderExecutor::Reset()
	{
		return Apply(m_defaultMaterial);
	}

}
