#pragma once

#include <ansi_graphics_engine.h>

namespace example
{

	class DirectionalLightMaterial : public ansi::Material
	{
	public:
		explicit DirectionalLightMaterial(unsigned shaderId, ansi::DirectionalLight * light);

		bool OnUpdateUniforms() override;

		void SetDiffuseMap(unsigned textureId) { SetTextureId(0, textureId); }

	private:
		ansi::DirectionalLight * m_light;

	};

}
