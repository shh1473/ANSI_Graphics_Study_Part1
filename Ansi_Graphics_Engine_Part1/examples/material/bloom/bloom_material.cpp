#include "bloom_material.h"

namespace example
{

	BloomMaterial::BloomMaterial(unsigned shaderId, unsigned srcTextureId, unsigned luminanceTextureId)
		: PostEffectMaterial(shaderId, srcTextureId)
	{
		SetTextureId(1, luminanceTextureId);
	}

	bool BloomMaterial::OnUpdateUniforms()
	{
		/* === Fragment === */
		CHECK_RF(SetUniform1i("u_luminanceTexture", 1));

		return PostEffectMaterial::OnUpdateUniforms();
	}

}
