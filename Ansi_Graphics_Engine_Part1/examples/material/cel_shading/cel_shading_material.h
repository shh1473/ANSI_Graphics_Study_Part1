#pragma once

#include <ansi_graphics_engine.h>

namespace example
{

	class CelShadingMaterial : public ansi::Material
	{
	public:
		explicit CelShadingMaterial(unsigned shaderId, ansi::DirectionalLight * light);

		bool OnUpdateUniforms() override;

		void SetCelLevel(float celLevel) { m_celLevel = celLevel; }

	private:
		float m_celLevel;
		ansi::DirectionalLight * m_light;

	};

}
