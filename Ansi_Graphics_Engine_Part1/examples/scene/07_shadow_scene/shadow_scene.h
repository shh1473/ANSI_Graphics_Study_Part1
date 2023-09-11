#pragma once

#include <ansi_graphics_engine.h>

#include "../example_scene.h"

namespace example
{

	class ShadowScene : public ExampleScene
	{
	public:
		static const std::string m_SceneName;

	public:
		explicit ShadowScene();

		bool Initialize() override;
		bool OnUpdate() override;
		bool OnRenderGui() override;
		bool CreateResources() override;

	private: /* GUI */
		bool m_isAutoRotate;
		bool m_isVisibleDepthMap;
		float m_depthMapCameraZoom;
		glm::vec2 m_lightRotation;

	private: /* 조명 */
		ansi::Object * m_lightAnchor{ nullptr };
		ansi::Object * m_directionalLight{ nullptr };

	private: /* 오브젝트 */
		ansi::Object * m_statue{ nullptr };
		ansi::Object * m_floor{ nullptr };
		ansi::Object * m_depthMapPlane{ nullptr };

	private: /* 자원 */
		ansi::Shader * m_colorShader{ nullptr };
		ansi::Shader * m_screenPlaneShader{ nullptr };
		ansi::Shader * m_shadowShader{ nullptr };

		ansi::InputElements * m_lightIE{ nullptr };
		ansi::InputElements * m_statueIE{ nullptr };
		ansi::InputElements * m_floorIE{ nullptr };
		ansi::InputElements * m_depthMapPlaneIE{ nullptr };

	};

}
