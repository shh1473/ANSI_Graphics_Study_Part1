#include "ansi_depth_material.h"

#include "core/render/ansi_render.h"
#include "object/component/camera/ansi_camera.h"
#include "object/component/transform/ansi_transform.h"

namespace ansi
{

	/* 생성자 */
	DepthMaterial::DepthMaterial(unsigned shaderId)
		: Material(shaderId)
	{
		SetCullMode(CullMode::None);
	}

	/* 매 프레임마다 호출되는 유니폼 업데이트 함수 */
	bool DepthMaterial::OnUpdateUniforms()
	{
		/* === 버텍스 셰이더 === */
		CHECK_RF(SetUniform4x4f("u_MVP", Core::GetRender()->GetCurrentCamera()->GetViewProjMatrix() * GetTransform()->GetWorldMatrix()));

		return true;
	}

}
