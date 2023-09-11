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
		/* === �����׸�Ʈ ���̴� === */
		CHECK_RF(SetUniform1i("u_radius", m_radius));

		return PostEffectMaterial::OnUpdateUniforms();
	}

}
