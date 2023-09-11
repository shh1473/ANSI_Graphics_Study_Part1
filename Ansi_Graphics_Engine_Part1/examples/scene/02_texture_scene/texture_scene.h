#pragma once

#include <ansi_graphics_engine.h>

#include "../example_scene.h"

namespace example
{

	class TextureScene : public ExampleScene
	{
	public:
		static const std::string m_SceneName;

	public:
		explicit TextureScene();

		bool Initialize() override;
		bool OnRenderGui() override;
		bool CreateResources() override;

	private: /* GUI */
		float m_textureScale;

	private: /* ������Ʈ */
		ansi::Object * m_statue{ nullptr };
		ansi::Object * m_floor{ nullptr };

	private: /* �ڿ� */
		ansi::Shader * m_textureShader{ nullptr };

		ansi::InputElements * m_statueIE{ nullptr };
		ansi::InputElements * m_floorIE{ nullptr };

		ansi::Texture * m_stonebricksDiffuseMap{ nullptr };

	};

}
