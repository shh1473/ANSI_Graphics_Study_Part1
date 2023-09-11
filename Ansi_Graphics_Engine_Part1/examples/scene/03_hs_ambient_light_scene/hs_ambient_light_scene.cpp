#include "hs_ambient_light_scene.h"

#include "../../material/hs_ambient_light/hs_ambient_light_material.h"

namespace example
{

	const std::string HSAmbientLightScene::m_SceneName{ "03 - Hemisphere Ambient Light" };

	HSAmbientLightScene::HSAmbientLightScene()
		: m_upColor(1.0f, 1.0f, 0.3f)
		, m_downColor(0.5f, 0.0f, 0.0f)
	{

	}

	bool HSAmbientLightScene::Initialize()
	{
		/* === 앰비언트 라이트 === */
		m_ambientLight = AddObject(new ansi::Object("Ambient Light"));

		auto ambientLight = m_ambientLight->AddComponent<ansi::HSAmbientLight>(m_upColor, m_downColor);

		/* === 석상 오브젝트 === */
		m_statue = AddObject(new ansi::Object("Statue"));
		m_statue->GetTransform()->SetPositionY(-15.0f);
		m_statue->GetTransform()->SetScale(5.0f);

		auto statueMaterial = new HSAmbientLightMaterial(m_hsAmbientLightShader->GetId(), ambientLight);
		statueMaterial->SetDiffuseMap(m_stonebricksDiffuseMap->GetId());
		auto statueRenderer = m_statue->AddComponent<ansi::Renderer>(m_statueIE, statueMaterial);

		/* === 바닥 오브젝트 === */
		m_floor = AddObject(new ansi::Object("Floor"));
		m_floor->GetTransform()->SetPositionY(-15.0f);
		m_floor->GetTransform()->SetRotationX(-90.0f);

		auto floorMaterial = new HSAmbientLightMaterial(m_hsAmbientLightShader->GetId(), ambientLight);
		floorMaterial->SetDiffuseMap(m_stonebricksDiffuseMap->GetId());
		auto floorRenderer = m_floor->AddComponent<ansi::Renderer>(m_floorIE, floorMaterial);

		return ExampleScene::Initialize();
	}

	bool HSAmbientLightScene::OnRenderGui()
	{
		ImGui::Text(">--------- Render Settings ---------<");

		/* [색상] - 위쪽 광원 색상 */
		if (ImGui::ColorEdit3("UpColor", glm::value_ptr(m_upColor)))
		{
			m_ambientLight->FindComponent<ansi::HSAmbientLight>()->SetUpColor(m_upColor);
		}

		/* [색상] - 아래쪽 광원 색상 */
		if (ImGui::ColorEdit3("DownColor", glm::value_ptr(m_downColor)))
		{
			m_ambientLight->FindComponent<ansi::HSAmbientLight>()->SetDownColor(m_downColor);
		}

		return ExampleScene::OnRenderGui();
	}

	bool HSAmbientLightScene::CreateResources()
	{
		/* === 셰이더 === */
		/* 반구형 앰비언트 라이트 */
		CHECK_RF(m_hsAmbientLightShader = GetResources()->CreateShader("assets/shader/hs_ambient_light.shader"));

		/* === 지오메트리 === */
		/* 석상 */
		auto statueGeometry = GetResources()->CreateGeometry();
		CHECK_RF(statueGeometry->GenerateFromObj("assets/model/angel.obj"));
		CHECK_RF(m_statueIE = statueGeometry->CreateInputElements(ansi::VA_TEXCOORD | ansi::VA_NORMAL));
		/* 바닥 */
		auto floorGeometry = GetResources()->CreateGeometry();
		CHECK_RF(floorGeometry->GeneratePlane(200.0f, 200.0f));
		CHECK_RF(m_floorIE = floorGeometry->CreateInputElements(ansi::VA_TEXCOORD | ansi::VA_NORMAL));

		/* === 텍스처 === */
		/* 석재 */
		CHECK_RF(m_stonebricksDiffuseMap = GetResources()->CreateTexture("assets/texture/stonebricks_diffuse.jpg"));

		return true;
	}

}
