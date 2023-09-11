#pragma once

#include <ansi_graphics_engine.h>

#include "../example_scene.h"

namespace example
{

	class ColorScene : public ExampleScene
	{
	public:
		static const std::string m_SceneName;

	public:
		explicit ColorScene();

		bool Initialize() override;
		bool OnRenderGui() override;
		bool CreateResources() override;

	private: /* GUI */
		bool m_isWireframe;
		glm::vec3 m_boxColor;

	private: /* 오브젝트 */
		ansi::Object * m_box{ nullptr };
		ansi::Object * m_sphere{ nullptr };
		ansi::Object * m_cylinder{ nullptr };

	private: /* 자원 */
		ansi::Shader * m_colorShader{ nullptr };

		ansi::InputElements * m_boxIE{ nullptr };
		ansi::InputElements * m_sphereIE{ nullptr };
		ansi::InputElements * m_cylinderIE{ nullptr };

	};

}
