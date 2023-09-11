#pragma once

#include <ansi_graphics_engine.h>

namespace example
{

	class GaussianBlurMaterial : public ansi::PostEffectMaterial
	{
	public:
		explicit GaussianBlurMaterial(unsigned shaderId, unsigned srcTextureId);

		bool OnUpdateUniforms() override;

		void SetRadius(int radius) { m_radius = radius; }

	private:
		int m_radius;

	};

}
