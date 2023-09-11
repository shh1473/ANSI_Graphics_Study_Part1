#pragma once

#include "core/render/shader_executor/material/ansi_material.h"

namespace ansi
{

	/* 그림자를 위한 깊이 기록 재질 */
	class DepthMaterial : public Material
	{
	public:
		/* 생성자
		* @param shaderId - 셰이더 ID
		*/
		explicit DepthMaterial(unsigned shaderId);

		/* 매 프레임마다 호출되는 유니폼 업데이트 함수 */
		bool OnUpdateUniforms() override;

	};

}
