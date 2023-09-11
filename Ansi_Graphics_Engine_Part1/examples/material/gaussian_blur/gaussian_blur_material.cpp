#include "gaussian_blur_material.h"

namespace example
{

	GaussianBlurMaterial::GaussianBlurMaterial(unsigned shaderId, unsigned srcTextureId)
		: PostEffectMaterial(shaderId, srcTextureId)
		, m_radius(1)
	{

	}

	bool GaussianBlurMaterial::OnUpdateUniforms()
	{
		/* === 프래그먼트 셰이더 === */
		CHECK_RF(SetUniform1i("u_radius", m_radius));

		return PostEffectMaterial::OnUpdateUniforms();
	}

}
