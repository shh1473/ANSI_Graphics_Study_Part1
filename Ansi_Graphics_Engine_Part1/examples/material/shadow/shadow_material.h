#pragma once

#include <ansi_graphics_engine.h>

namespace example
{

	class ShadowMaterial : public ansi::Material
	{
	public:
		explicit ShadowMaterial(unsigned shaderId, ansi::DirectionalLight * light);

		bool OnUpdateUniforms() override;

	private:
		ansi::DirectionalLight * m_light;

	};

}
