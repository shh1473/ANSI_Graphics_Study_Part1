#pragma once

#include <ansi_graphics_engine.h>

namespace example
{

	class ColorMaterial : public ansi::Material
	{
	public:
		explicit ColorMaterial(unsigned shaderId);

		bool OnUpdateUniforms() override;

	};

}
