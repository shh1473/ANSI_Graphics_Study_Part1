#pragma once

#include <ansi_graphics_engine.h>

namespace example
{

	class AllInOneMaterial : public ansi::Material
	{
	public:
		explicit AllInOneMaterial(unsigned shaderId,
			ansi::HSAmbientLight * ambientLight,
			ansi::DirectionalLight * directionalLight);

		bool OnUpdateUniforms() override;

		void SetDiffuseMap(unsigned textureId) { SetTextureId(1, textureId); }
		void SetNormalMap(unsigned textureId) { SetTextureId(2, textureId); }

	private:
		ansi::HSAmbientLight * m_ambientLight;
		ansi::DirectionalLight * m_directionalLight;

	};

}
