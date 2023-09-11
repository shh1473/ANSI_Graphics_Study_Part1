#include "color_material.h"

namespace example
{

	ColorMaterial::ColorMaterial(unsigned shaderId)
		: Material(shaderId)
	{

	}

	bool ColorMaterial::OnUpdateUniforms()
	{
		/* === ���ؽ� ���̴� === */
		CHECK_RF(SetUniform4x4f("u_MVP", ansi::Core::GetRender()->GetCurrentCamera()->GetViewProjMatrix() * GetTransform()->GetWorldMatrix()));

		/* === �����׸�Ʈ ���̴� === */
		CHECK_RF(SetUniform4f("u_diffuseColor", GetDiffuseColor()));

		return true;
	}

}
