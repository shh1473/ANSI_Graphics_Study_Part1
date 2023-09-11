#pragma once

#include <ansi_graphics_engine.h>

namespace example
{

	class ScreenPlaneMaterial : public ansi::Material
	{
	public:
		explicit ScreenPlaneMaterial(unsigned shaderId, unsigned textureId, const glm::vec4 & viewport = glm::vec4(0.0f, 0.0f, 100.0f, 100.0f));

		bool OnUpdateUniforms() override;

	private:
		glm::vec4 m_viewport;
		ansi::StateChecker<glm::vec2> m_cameraSize;

	};

}
