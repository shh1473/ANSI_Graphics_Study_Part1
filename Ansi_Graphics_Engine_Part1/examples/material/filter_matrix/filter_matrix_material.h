#pragma once

#include <ansi_graphics_engine.h>

namespace example
{

	class FilterMatrixMaterial : public ansi::PostEffectMaterial
	{
	public:
		explicit FilterMatrixMaterial(unsigned shaderId, unsigned srcTextureId);

		bool OnUpdateUniforms() override;

		void SetIsEnableGrayscale(bool isEnable) { m_isEnableGrayscale = isEnable; }
		void SetIsEnableInvert(bool isEnable) { m_isEnableInvert = isEnable; }
		void SetBrightness(float brightness) { m_brightness = brightness; }

	private:
		bool m_isEnableGrayscale;
		bool m_isEnableInvert;
		float m_brightness;

	};

}
