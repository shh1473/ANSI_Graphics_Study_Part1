#pragma once

#include "core/render/shader_executor/material/ansi_material.h"

namespace ansi
{

	/* �׸��ڸ� ���� ���� ��� ���� */
	class DepthMaterial : public Material
	{
	public:
		/* ������
		* @param shaderId - ���̴� ID
		*/
		explicit DepthMaterial(unsigned shaderId);

		/* �� �����Ӹ��� ȣ��Ǵ� ������ ������Ʈ �Լ� */
		bool OnUpdateUniforms() override;

	};

}
