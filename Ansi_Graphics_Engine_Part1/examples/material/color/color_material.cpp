#include "color_material.h"

namespace example
{

	ColorMaterial::ColorMaterial(unsigned shaderId)
		: Material(shaderId)
	{

	}

	bool ColorMaterial::OnUpdateUniforms()
	{
		/* === 버텍스 셰이더 === */
		CHECK_RF(SetUniform4x4f("u_MVP", ansi::Core::GetRender()->GetCurrentCamera()->GetViewProjMatrix() * GetTransform()->GetWorldMatrix()));

		/* === 프래그먼트 셰이더 === */
		CHECK_RF(SetUniform4f("u_diffuseColor", GetDiffuseColor()));

		return true;
	}

}
