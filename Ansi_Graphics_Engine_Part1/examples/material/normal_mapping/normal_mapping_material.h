#pragma once

#include <ansi_graphics_engine.h>

namespace example
{

	class NormalMappingMaterial : public ansi::Material
	{
	public:
		explicit NormalMappingMaterial(unsigned shaderId, ansi::DirectionalLight * light);

		bool OnUpdateUniforms() override;

		void SetDiffuseMap(unsigned textureId) { SetTextureId(0, textureId); }
		void SetNormalMap(unsigned textureId) { SetTextureId(1, textureId); }

	private:
		ansi::DirectionalLight * m_light;

	};

}
