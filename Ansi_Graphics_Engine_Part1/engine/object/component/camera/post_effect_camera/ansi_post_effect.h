#pragma once

#include "ansi_post_effect_material.h"

namespace ansi
{

	class Framebuffer;

	class PostEffect
	{
	public:
		explicit PostEffect(PostEffectMaterial * material);
		~PostEffect();

		bool CreateFramebuffer(float width, float height);

		Framebuffer * GetFramebuffer() const { return m_framebuffer; }
		PostEffectMaterial * GetMaterial() const { return m_material; }

	private:
		Framebuffer * m_framebuffer;
		PostEffectMaterial * m_material;

	};

}
