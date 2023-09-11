#include "filter_matrix_material.h"

namespace example
{

	FilterMatrixMaterial::FilterMatrixMaterial(unsigned shaderId, unsigned srcTextureId)
		: PostEffectMaterial(shaderId, srcTextureId)
		, m_isEnableGrayscale(false)
		, m_isEnableInvert(false)
		, m_brightness(1.0f)
	{

	}

	bool FilterMatrixMaterial::OnUpdateUniforms()
	{
		/* === 프래그먼트 셰이더 === */
		glm::mat4 filterMatrix(m_brightness);

		if (m_isEnableGrayscale)
		{
			filterMatrix = glm::mat4(
				0.299f, 0.299f, 0.299f, 0.0f,
				0.587f, 0.587f, 0.587f, 0.0f,
				0.114f, 0.114f, 0.114f, 0.0f,
				0.000f, 0.000f, 0.000f, 1.0f) * filterMatrix;
		}

		if (m_isEnableInvert)
		{
			filterMatrix = glm::mat4(
				-1.0f,  0.0f,  0.0f, 0.0f,
				 0.0f, -1.0f,  0.0f, 0.0f,
				 0.0f,  0.0f, -1.0f, 0.0f,
				 1.0f,  1.0f,  1.0f, 1.0f) * filterMatrix;
		}

		CHECK_RF(SetUniform4x4f("u_filterMatrix", filterMatrix));

		return PostEffectMaterial::OnUpdateUniforms();
	}

}
