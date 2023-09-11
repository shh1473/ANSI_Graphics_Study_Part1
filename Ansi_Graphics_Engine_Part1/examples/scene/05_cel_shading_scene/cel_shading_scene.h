#pragma once

#include <ansi_graphics_engine.h>

#include "../example_scene.h"

namespace example
{

	class CelShadingScene : public ExampleScene
	{
	public:
		static const std::string m_SceneName;

	public:
		explicit CelShadingScene();

		bool Initialize() override;
		bool OnUpdate() override;
		bool OnRenderGui() override;
		bool CreateResources() override;

	private: /* GUI */
		bool m_isAutoRotate;
		float m_celLevel;
		float m_specularIntensity;
		float m_specularPower;
		glm::vec3 m_lightColor;
		glm::vec2 m_lightRotation;

	private: /* 조명 */
		ansi::Object * m_lightAnchor{ nullptr };
		ansi::Object * m_directionalLight{ nullptr };

	private: /* 오브젝트 */
		ansi::Object * m_statue{ nullptr };
		ansi::Object * m_floor{ nullptr };

	private: /* 자원 */
		ansi::Shader * m_colorShader{ nullptr };
		ansi::Shader * m_celShadingShader{ nullptr };

		ansi::InputElements * m_lightIE{ nullptr };
		ansi::InputElements * m_statueIE{ nullptr };
		ansi::InputElements * m_floorIE{ nullptr };

	};

}
