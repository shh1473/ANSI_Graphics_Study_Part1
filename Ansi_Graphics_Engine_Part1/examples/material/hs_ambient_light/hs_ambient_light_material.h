#pragma once

#include <ansi_graphics_engine.h>

namespace example
{

	class HSAmbientLightMaterial : public ansi::Material
	{
	public:
		explicit HSAmbientLightMaterial(unsigned shaderId, ansi::HSAmbientLight * light);

		bool OnUpdateUniforms() override;

		void SetDiffuseMap(unsigned textureId) { SetTextureId(0, textureId); }

	private:
		ansi::HSAmbientLight * m_light;

	};

}
