#include "texture_material.h"

namespace example
{

	TextureMaterial::TextureMaterial(unsigned shaderId)
		: Material(shaderId)
		, m_textureScale(1.0f)
	{

	}

	bool TextureMaterial::OnUpdateUniforms()
	{
		/* === 버텍스 셰이더 === */
		CHECK_RF(SetUniform4x4f("u_MVP", ansi::Core::GetRender()->GetCurrentCamera()->GetViewProjMatrix() * GetTransform()->GetWorldMatrix()));
		CHECK_RF(SetUniform1f("u_textureScale", m_textureScale));

		/* === 프래그먼트 셰이더 === */
		CHECK_RF(SetUniform1i("u_diffuseMap", 0));

		return true;
	}

}
