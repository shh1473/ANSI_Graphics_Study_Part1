#include "ansi_post_effect_material.h"

namespace ansi
{

	PostEffectMaterial::PostEffectMaterial(unsigned shaderId, unsigned srcTextureId)
		: Material(shaderId)
	{
		SetIsEnableDepthTest(false);
		SetIsEnableDepthWrite(false);

		SetTextureId(0, srcTextureId);
	}

	/* 매 프레임마다 호출되는 유니폼 업데이트 함수 */
	bool PostEffectMaterial::OnUpdateUniforms()
	{
		/* === 프래그먼트 셰이더 === */
		CHECK_RF(SetUniform1i("u_srcTexture", 0));

		return true;
	}

}
