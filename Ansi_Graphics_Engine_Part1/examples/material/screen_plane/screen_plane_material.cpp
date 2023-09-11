#include "screen_plane_material.h"

namespace example
{

	ScreenPlaneMaterial::ScreenPlaneMaterial(unsigned shaderId, unsigned textureId, const glm::vec4 & viewport)
		: Material(shaderId)
		, m_viewport(viewport)
	{
		SetIsEnableDepthTest(false);
		SetIsEnableDepthWrite(false);

		SetTextureId(0, textureId);
	}

	bool ScreenPlaneMaterial::OnUpdateUniforms()
	{
		/* 카메라 해상도가 업데이트되었을 경우, 위치 오프셋 업데이트 */
		m_cameraSize.Set(ansi::Core::GetRender()->GetCurrentCamera()->GetSize());

		if (m_cameraSize.Check())
		{
			glm::vec2 halfCameraSize{ ansi::Core::GetRender()->GetCurrentCamera()->GetSize() * 0.5f };

			GetTransform()->SetScaleX(m_viewport.z / halfCameraSize.x);
			GetTransform()->SetScaleY(m_viewport.w / halfCameraSize.y);
			GetTransform()->SetPositionX((m_viewport.x / halfCameraSize.x) + (GetTransform()->GetScale().x * 0.5f) - 1.0f);
			GetTransform()->SetPositionY((m_viewport.y / halfCameraSize.y) + (GetTransform()->GetScale().y * 0.5f) - 1.0f);
		}

		/* === 버텍스 셰이더 === */
		CHECK_RF(SetUniform4x4f("u_worldMatrix", GetTransform()->GetWorldMatrix()));

		/* === 프래그먼트 셰이더 === */
		CHECK_RF(SetUniform4f("u_diffuseColor", GetDiffuseColor()));

		CHECK_RF(SetUniform1i("u_diffuseMap", 0));

		return true;
	}

}
