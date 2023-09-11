#include "ansi_depth_material.h"

#include "core/render/ansi_render.h"
#include "object/component/camera/ansi_camera.h"
#include "object/component/transform/ansi_transform.h"

namespace ansi
{

	/* ������ */
	DepthMaterial::DepthMaterial(unsigned shaderId)
		: Material(shaderId)
	{
		SetCullMode(CullMode::None);
	}

	/* �� �����Ӹ��� ȣ��Ǵ� ������ ������Ʈ �Լ� */
	bool DepthMaterial::OnUpdateUniforms()
	{
		/* === ���ؽ� ���̴� === */
		CHECK_RF(SetUniform4x4f("u_MVP", Core::GetRender()->GetCurrentCamera()->GetViewProjMatrix() * GetTransform()->GetWorldMatrix()));

		return true;
	}

}
