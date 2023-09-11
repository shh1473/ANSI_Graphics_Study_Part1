#pragma once

#include <ansi_graphics_engine.h>

namespace example
{

	class LuminanceExtractionMaterial : public ansi::PostEffectMaterial
	{
	public:
		explicit LuminanceExtractionMaterial(unsigned shaderId, unsigned srcTextureId);

		bool OnUpdateUniforms() override;

		void SetThreshold(float threshold) { m_threshold = glm::min(threshold, 0.999f); }

	private:
		float m_threshold;

	};

}
