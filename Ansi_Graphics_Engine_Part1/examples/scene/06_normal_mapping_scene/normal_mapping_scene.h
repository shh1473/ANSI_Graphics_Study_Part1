#pragma once

#include <ansi_graphics_engine.h>

#include "../example_scene.h"

namespace example
{

	class NormalMappingScene : public ExampleScene
	{
	public:
		static const std::string m_SceneName;

	public:
		explicit NormalMappingScene();

		bool Initialize() override;
		bool OnUpdate() override;
		bool OnRenderGui() override;
		bool CreateResources() override;

	private: /* GUI */
		bool m_isWireframe;
		bool m_isAutoRotate;
		float m_specularIntensity;
		float m_specularPower;
		glm::vec3 m_lightColor;
		glm::vec2 m_lightRotation;

	private: /* ���� */
		ansi::Object * m_lightAnchor{ nullptr };
		ansi::Object * m_directionalLight{ nullptr };

	private: /* ������Ʈ */
		ansi::Object * m_statue{ nullptr };
		ansi::Object * m_floor{ nullptr };

	private: /* �ڿ� */
		ansi::Shader * m_colorShader{ nullptr };
		ansi::Shader * m_normalMappingShader{ nullptr };

		ansi::InputElements * m_lightIE{ nullptr };
		ansi::InputElements * m_statueIE{ nullptr };
		ansi::InputElements * m_floorIE{ nullptr };

		ansi::Texture * m_stonebricksDiffuseMap{ nullptr };
		ansi::Texture * m_stonebricksNormalMap{ nullptr };

	};

}