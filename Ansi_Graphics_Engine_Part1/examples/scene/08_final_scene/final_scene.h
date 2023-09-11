#pragma once

#include <ansi_graphics_engine.h>

#include "../example_scene.h"

namespace example
{

	class FinalScene : public ExampleScene
	{
	public:
		explicit FinalScene();

		bool Initialize() override;
		bool OnUpdate() override;
		bool OnRenderGui() override;
		bool CreateResources() override;

	public:
		static const std::string m_SceneName;

	private: /* GUI */
		bool m_isAutoRotate;
		bool m_isVisibleDepthMap;
		float m_specularIntensity;
		float m_specularPower;

		glm::vec3 m_ambientLightUpColor;
		glm::vec3 m_ambientLightDownColor;
		glm::vec3 m_directionalLightColor;
		glm::vec2 m_directionalLightRotation;

		bool m_isEnableGrayscale;
		bool m_isEnableInvert;
		float m_brightness;
		float m_bloomThreshold;
		int m_bloomRadius;

	private: /* 조명 */
		ansi::Object * m_ambientLight{ nullptr };
		ansi::Object * m_lightAnchor{ nullptr };
		ansi::Object * m_directionalLight{ nullptr };

	private: /* 오브젝트 */
		ansi::Object * m_statue{ nullptr };
		ansi::Object * m_floor{ nullptr };
		ansi::Object * m_depthMapPlane{ nullptr };

	private: /* 자원 */
		ansi::Shader * m_colorShader{ nullptr };
		ansi::Shader * m_screenPlaneShader{ nullptr };
		ansi::Shader * m_allInOneShader{ nullptr };

		ansi::Shader * m_filterMatrixShader{ nullptr };
		ansi::Shader * m_luminanceExtractionShader{ nullptr };
		ansi::Shader * m_gaussianBlurShader{ nullptr };
		ansi::Shader * m_bloomShader{ nullptr };

		ansi::InputElements * m_lightIE{ nullptr };
		ansi::InputElements * m_statueIE{ nullptr };
		ansi::InputElements * m_floorIE{ nullptr };
		ansi::InputElements * m_depthMapPlaneIE{ nullptr };

		ansi::Texture * m_stonebricksDiffuseMap{ nullptr };
		ansi::Texture * m_stonebricksNormalMap{ nullptr };

	};

}
