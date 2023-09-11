#pragma once

#include <ansi_graphics_engine.h>

namespace example
{

	class TextureMaterial : public ansi::Material
	{
	public:
		explicit TextureMaterial(unsigned shaderId);

		bool OnUpdateUniforms() override;

		void SetTextureScale(float textureScale) { m_textureScale = textureScale; }
		void SetDiffuseMap(unsigned textureId) { SetTextureId(0, textureId); }

	private:
		float m_textureScale;

	};

}
