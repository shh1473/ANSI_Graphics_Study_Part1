#include "luminance_extraction_material.h"

namespace example
{

	LuminanceExtractionMaterial::LuminanceExtractionMaterial(unsigned shaderId, unsigned srcTextureId)
		: PostEffectMaterial(shaderId, srcTextureId)
		, m_threshold(1.0f)
	{

	}

	bool LuminanceExtractionMaterial::OnUpdateUniforms()
	{
		/* === 프래그먼트 셰이더 === */
		CHECK_RF(SetUniform1f("u_threshold", m_threshold));

		return PostEffectMaterial::OnUpdateUniforms();
	}

}
