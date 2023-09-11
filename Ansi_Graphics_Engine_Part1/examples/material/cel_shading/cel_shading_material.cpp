#include "cel_shading_material.h"

namespace example
{

	CelShadingMaterial::CelShadingMaterial(unsigned shaderId, ansi::DirectionalLight * light)
		: Material(shaderId)
		, m_celLevel(4.0f)
		, m_light(light)
	{

	}

	bool CelShadingMaterial::OnUpdateUniforms()
	{
		/* === ���ؽ� ���̴� === */
		CHECK_RF(SetUniform4x4f("u_MVP", ansi::Core::GetRender()->GetCurrentCamera()->GetViewProjMatrix() * GetTransform()->GetWorldMatrix()));
		CHECK_RF(SetUniform4x4f("u_worldMatrix", GetTransform()->GetWorldMatrix()));

		/* === �����׸�Ʈ ���̴� === */
		CHECK_RF(SetUniform3f("u_cameraPosition", ansi::Core::GetRender()->GetCurrentCamera()->GetObject()->GetTransform()->GetWorldPosition()));

		CHECK_RF(SetUniform3f("u_lightColor", m_light->GetColor()));
		CHECK_RF(SetUniform3f("u_lightDirection", m_light->GetObject()->GetTransform()->GetLookAt()));

		CHECK_RF(SetUniform1f("u_specularIntensity", GetSpecularIntensity()));
		CHECK_RF(SetUniform1f("u_specularPower", GetSpecularPower()));

		CHECK_RF(SetUniform1f("u_celLevel", m_celLevel));

		return true;
	}

}
