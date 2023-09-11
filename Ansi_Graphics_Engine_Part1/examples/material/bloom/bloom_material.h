#pragma once

#include <ansi_graphics_engine.h>

namespace example
{

	class BloomMaterial : public ansi::PostEffectMaterial
	{
	public:
		explicit BloomMaterial(unsigned shaderId, unsigned srcTextureId, unsigned luminanceTextureId);

		bool OnUpdateUniforms() override;

	};

}
