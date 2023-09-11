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

	/* �� �����Ӹ��� ȣ��Ǵ� ������ ������Ʈ �Լ� */
	bool PostEffectMaterial::OnUpdateUniforms()
	{
		/* === �����׸�Ʈ ���̴� === */
		CHECK_RF(SetUniform1i("u_srcTexture", 0));

		return true;
	}

}
