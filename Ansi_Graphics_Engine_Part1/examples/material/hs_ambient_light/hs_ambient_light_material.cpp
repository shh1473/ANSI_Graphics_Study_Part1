#include "hs_ambient_light_material.h"

namespace example
{

	HSAmbientLightMaterial::HSAmbientLightMaterial(unsigned shaderId, ansi::HSAmbientLight * light)
		: Material(shaderId)
		, m_light(light)
	{

	}

	bool HSAmbientLightMaterial::OnUpdateUniforms()
	{
		/* === ���ؽ� ���̴� === */
		CHECK_RF(SetUniform4x4f("u_MVP", ansi::Core::GetRender()->GetCurrentCamera()->GetViewProjMatrix() * GetTransform()->GetWorldMatrix()));
		CHECK_RF(SetUniform4x4f("u_worldMatrix", GetTransform()->GetWorldMatrix()));

		/* === �����׸�Ʈ ���̴� === */
		CHECK_RF(SetUniform3f("u_downColor", m_light->GetDownColor()));
		CHECK_RF(SetUniform3f("u_colorRange", m_light->GetColorRange()));

		CHECK_RF(SetUniform1i("u_diffuseMap", 0));

		return true;
	}

}
