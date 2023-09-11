#pragma once

#include <ansi_graphics_engine.h>

#include "../example_scene.h"

namespace example
{

	class HSAmbientLightScene : public ExampleScene
	{
	public:
		static const std::string m_SceneName;

	public:
		explicit HSAmbientLightScene();

		bool Initialize() override;
		bool OnRenderGui() override;
		bool CreateResources() override;

	private: /* GUI */
		glm::vec3 m_upColor;
		glm::vec3 m_downColor;

	private: /* ���� */
		ansi::Object * m_ambientLight{ nullptr };

	private: /* ������Ʈ */
		ansi::Object * m_statue{ nullptr };
		ansi::Object * m_floor{ nullptr };

	private: /* �ڿ� */
		ansi::Shader * m_hsAmbientLightShader{ nullptr };

		ansi::InputElements * m_statueIE{ nullptr };
		ansi::InputElements * m_floorIE{ nullptr };

		ansi::Texture * m_stonebricksDiffuseMap{ nullptr };

	};

}
