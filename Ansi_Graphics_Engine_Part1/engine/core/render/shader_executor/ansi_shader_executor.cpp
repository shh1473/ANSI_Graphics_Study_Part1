#include "ansi_shader_executor.h"

namespace ansi
{

	/* ������ */
	ShaderExecutor::ShaderExecutor()
		: m_defaultMaterial(new Material(0))
		, m_isEnableDepthWrite(m_defaultMaterial->GetIsEnableDepthWrite())
	{

	}

	/* �Ҹ��� */
	ShaderExecutor::~ShaderExecutor()
	{
		SAFE_DELETE(m_defaultMaterial);
	}

	/* OpenGL ���ؽ�Ʈ�� ���̴� ���� ���¸� �����ϴ� �Լ� */
	bool ShaderExecutor::Apply(Material * material)
	{
		/* ���̴� ���� ���� ���� */
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

		/* ���̴� ID�� ����Ǿ��� ��� ���� */
		if (m_shaderId.Check())
		{
			GL_CHECK(glUseProgram(m_shaderId.Get()));
			m_shaderId.Reset();
		}

		/* �ؽ�ó ID �Ǵ� ������ ����Ǿ��� ��� ���� */
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

		/* ���� ���� ���� ���� (�����ӹ����� ���� �ʱ�ȭ���� ���� ���⸦ ������ �ѹǷ�, ���� �˻縦 ���� �ʰ� �׻� ����) */
		GL_CHECK(glDepthMask(m_isEnableDepthWrite ? GL_TRUE : GL_FALSE));

		/* ���� �׽�Ʈ Ȱ��ȭ ���ΰ� ����Ǿ��� ��� ���� */
		if (m_isEnableDepthTest.Check())
		{
			if (m_isEnableDepthTest.Get()) { GL_CHECK(glEnable(GL_DEPTH_TEST)); }
			else { GL_CHECK(glDisable(GL_DEPTH_TEST)); }
			m_isEnableDepthTest.Reset();
		}

		/* ���� �� �Լ��� ����Ǿ��� ��� ���� */
		if (m_depthFunc.Check())
		{
			GL_CHECK(glDepthFunc(static_cast<unsigned>(m_depthFunc.Get())));
			m_depthFunc.Reset();
		}

		/* �ﰢ�� ä��� ��尡 ����Ǿ��� ��� ���� */
		if (m_fillMode.Check())
		{
			GL_CHECK(glPolygonMode(GL_FRONT_AND_BACK, static_cast<unsigned>(m_fillMode.Get())));
			m_fillMode.Reset();
		}

		/* �ﰢ�� �ø� ��尡 ����Ǿ��� ��� ���� */
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

		/* �ﰢ�� �ո� ���� ������ ����Ǿ��� ��� ���� */
		if (m_frontFace.Check())
		{
			GL_CHECK(glFrontFace(static_cast<unsigned>(m_frontFace.Get())));
			m_frontFace.Reset();
		}

		/* ������ ������Ʈ */
		CHECK_RF(material->OnUpdateUniforms());

		return true;
	}

	/* OpenGL ���ؽ�Ʈ�� ��� ���� ���¸� �ʱ�ȭ�ϴ� �Լ� */
	bool ShaderExecutor::Reset()
	{
		return Apply(m_defaultMaterial);
	}

}
