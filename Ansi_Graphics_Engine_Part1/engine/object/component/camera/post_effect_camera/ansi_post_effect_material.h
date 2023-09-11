#pragma once

#include "core/render/shader_executor/material/ansi_material.h"

namespace ansi
{

	class PostEffectMaterial : public Material
	{
	public:
		explicit PostEffectMaterial(unsigned shaderId, unsigned srcTextureId);

		/* 매 프레임마다 호출되는 유니폼 업데이트 함수 */
		bool OnUpdateUniforms() override;

	};

}
