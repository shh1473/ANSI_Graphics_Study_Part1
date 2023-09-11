#pragma once

#include "core/render/shader_executor/material/ansi_material.h"

namespace ansi
{

	class PostEffectMaterial : public Material
	{
	public:
		explicit PostEffectMaterial(unsigned shaderId, unsigned srcTextureId);

		/* �� �����Ӹ��� ȣ��Ǵ� ������ ������Ʈ �Լ� */
		bool OnUpdateUniforms() override;

	};

}
