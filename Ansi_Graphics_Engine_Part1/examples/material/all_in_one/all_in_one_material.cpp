#include "all_in_one_material.h"

#include "object/component/camera/depth_camera/ansi_depth_camera.h"

namespace example
{

	AllInOneMaterial::AllInOneMaterial(unsigned shaderId,
		ansi::HSAmbientLight * ambientLight,
		ansi::DirectionalLight * directionalLight)
		: Material(shaderId)
		, m_ambientLight(ambientLight)
		, m_directionalLight(directionalLight)
	{
		SetTextureId(0, m_directionalLight->GetDepthMapCamera()->GetFramebuffer()->GetDepthTextureId());
	}

	bool AllInOneMaterial::OnUpdateUniforms()
	{
		/* === 버텍스 셰이더 === */
		CHECK_RF(SetUniform4x4f("u_directionalLightMVP", m_directionalLight->GetDepthMapCamera()->GetViewProjMatrix() * GetTransform()->GetWorldMatrix()));

		CHECK_RF(SetUniform4x4f("u_MVP", ansi::Core::GetRender()->GetCurrentCamera()->GetViewProjMatrix() * GetTransform()->GetWorldMatrix()));

		/* === 프래그먼트 셰이더 === */
		CHECK_RF(SetUniform4x4f("u_worldMatrix", GetTransform()->GetWorldMatrix()));

		CHECK_RF(SetUniform3f("u_cameraPosition", ansi::Core::GetRender()->GetCurrentCamera()->GetObject()->GetTransform()->GetWorldPosition()));

		CHECK_RF(SetUniform3f("u_ambientLightDownColor", m_ambientLight->GetDownColor()));
		CHECK_RF(SetUniform3f("u_ambientLightColorRange", m_ambientLight->GetColorRange()));

		CHECK_RF(SetUniform3f("u_directionalLightColor", m_directionalLight->GetColor()));
		CHECK_RF(SetUniform3f("u_directionalLightDirection", m_directionalLight->GetObject()->GetTransform()->GetLookAt()));

		CHECK_RF(SetUniform1f("u_specularIntensity", GetSpecularIntensity()));
		CHECK_RF(SetUniform1f("u_specularPower", GetSpecularPower()));

		CHECK_RF(SetUniform1i("u_depthMap", 0));
		CHECK_RF(SetUniform1i("u_diffuseMap", 1));
		CHECK_RF(SetUniform1i("u_normalMap", 2));

		return true;
	}

}
