#include "ansi_post_effect.h"

#include "resource/framebuffer/ansi_framebuffer.h"
#include "resource/texture/ansi_texture.h"

namespace ansi
{

	PostEffect::PostEffect(PostEffectMaterial * material)
		: m_framebuffer(nullptr)
		, m_material(material)
	{

	}

	PostEffect::~PostEffect()
	{
		SAFE_DELETE(m_framebuffer);
		SAFE_DELETE(m_material);
	}

	bool PostEffect::CreateFramebuffer(float width, float height)
	{
		/* 전용 프레임버퍼 생성 */
		m_framebuffer = new Framebuffer();
		m_framebuffer->Initialize(width, height, FB_COLOR);

		return true;
	}

}
