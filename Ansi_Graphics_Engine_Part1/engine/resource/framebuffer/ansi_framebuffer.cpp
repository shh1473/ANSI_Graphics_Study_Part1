#include "ansi_framebuffer.h"

#include "resource/texture/ansi_texture.h"

namespace ansi
{

	/* ������ */
	Framebuffer::Framebuffer()
		: m_id(0)
		, m_flag(0)
		, m_colorTexture(nullptr)
		, m_depthTexture(nullptr)
	{

	}

	/* �Ҹ��� */
	Framebuffer::~Framebuffer()
	{
		SAFE_DELETE(m_colorTexture);
		SAFE_DELETE(m_depthTexture);
		GL_CHECK(glDeleteFramebuffers(1, &m_id));
	}

	/* �ʱ�ȭ �Լ� */
	bool Framebuffer::Initialize(float width, float height, unsigned flag)
	{
		m_flag = flag;

		/* ù �ʱ�ȭ�� ���, ���� �����ӹ��� ���� */
		if (m_id == 0) { GL_CHECK_RF(glGenFramebuffers(1, &m_id)); }
		/* �� ��° �̻��� �ʱ�ȭ�� ���, ������ ���� ���ۿ� ���� ���۸� ����� */
		else
		{
			SAFE_DELETE(m_colorTexture);
			SAFE_DELETE(m_depthTexture);
		}

		GL_CHECK_RF(glBindFramebuffer(GL_FRAMEBUFFER, m_id));

		if (m_flag & FB_COLOR)
		{
			/* ���� �ؽ�ó ���� (32��Ʈ ��ȣ ���� ����) */
			unsigned colorTextureId{ 0 };
			GL_CHECK_RF(glGenTextures(1, &colorTextureId));
			GL_CHECK_RF(glBindTexture(GL_TEXTURE_2D, colorTextureId));
			GL_CHECK_RF(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
				static_cast<int>(width), static_cast<int>(height), 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr));

			/* ���� �ؽ�ó �Ӽ� ���� */
			GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
			GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
			GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
			GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

			/* ���� �����ӹ��ۿ� ���� */
			GL_CHECK(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTextureId, 0));

			/* �ؽ�ó �ڿ� ��ü�� �߰� */
			m_colorTexture = new Texture(colorTextureId, static_cast<unsigned>(width), static_cast<unsigned>(height));
		}
		else { GL_CHECK(glDrawBuffer(GL_NONE)); }

		if (m_flag & FB_DEPTH)
		{
			/* ���� �ؽ�ó ���� (16��Ʈ �ε��Ҽ���) */
			unsigned depthTextureId{ 0 };
			GL_CHECK(glGenTextures(1, &depthTextureId));
			GL_CHECK(glBindTexture(GL_TEXTURE_2D, depthTextureId));
			GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16,
				static_cast<int>(width), static_cast<int>(height), 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr));

			/* ���� �ؽ�ó �Ӽ� ���� */
			float borderColor[]{ 1.0f, 1.0f, 1.0f, 1.0f };
			GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
			GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
			GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
			GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));
			GL_CHECK(glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor));

			/* ���� �����ӹ��ۿ� ���� */
			GL_CHECK(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTextureId, 0));

			/* �ؽ�ó �ڿ� ��ü�� �߰� */
			m_depthTexture = new Texture(depthTextureId, static_cast<unsigned>(width), static_cast<unsigned>(height));
		}

		/* �����ӹ��� ��ȿ�� Ȯ�� */
		CHECK_RF(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
		GL_CHECK(glBindFramebuffer(GL_FRAMEBUFFER, 0));

		return true;
	}

	/* ũ�⸦ ������Ʈ�ϴ� �Լ� */
	bool Framebuffer::UpdateSize(float width, float height)
	{
		return Initialize(width, height, m_flag);
	}

	unsigned Framebuffer::GetColorTextureId() const
	{
		return m_colorTexture->GetId();
	}

	unsigned Framebuffer::GetDepthTextureId() const
	{
		return m_depthTexture->GetId();
	}

}
