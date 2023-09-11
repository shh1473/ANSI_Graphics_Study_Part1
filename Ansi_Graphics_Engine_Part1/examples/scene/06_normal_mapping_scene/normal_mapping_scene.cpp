#include "normal_mapping_scene.h"

#include "../../material/color/color_material.h"
#include "../../material/normal_mapping/normal_mapping_material.h"

namespace example
{

	const std::string NormalMappingScene::m_SceneName{ "06 - Normal Mapping" };

	NormalMappingScene::NormalMappingScene()
		: m_isWireframe(false)
		, m_isAutoRotate(false)
		, m_specularIntensity(1.5f)
		, m_specularPower(32.0f)
		, m_lightColor(1.0f)
		, m_lightRotation(-45.0f, 225.0f)
	{

	}

	bool NormalMappingScene::Initialize()
	{
		/* === 디렉셔널 라이트 === */
		m_lightAnchor = AddObject(new ansi::Object("Light Anchor"));
		m_lightAnchor->GetTransform()->SetEulerOrder(EulerOrder::YXZ);
		m_lightAnchor->GetTransform()->SetRotation(m_lightRotation.x, m_lightRotation.y, 0.0f);

		m_directionalLight = m_lightAnchor->AddChild(new ansi::Object("Directional Light"));
		m_directionalLight->GetTransform()->SetPositionY(150.0f);
		m_directionalLight->GetTransform()->SetRotationX(90.0f);

		auto directionalLight = m_directionalLight->AddComponent<ansi::DirectionalLight>(m_lightColor);
		auto directionalLightMaterial = new ColorMaterial(m_colorShader->GetId());
		directionalLightMaterial->SetColor(glm::vec3(1.0f, 1.0f, 0.0f));
		auto directionalLightRenderer = m_directionalLight->AddComponent<ansi::Renderer>(m_lightIE, directionalLightMaterial);

		/* === 석상 오브젝트 === */
		m_statue = AddObject(new ansi::Object("Statue"));
		m_statue->GetTransform()->SetPositionY(-15.0f);
		m_statue->GetTransform()->SetScale(5.0f);

		auto statueMaterial = new NormalMappingMaterial(m_normalMappingShader->GetId(), directionalLight);
		statueMaterial->SetSpecularIntensity(m_specularIntensity);
		statueMaterial->SetSpecularPower(m_specularPower);
		statueMaterial->SetDiffuseMap(m_stonebricksDiffuseMap->GetId());
		statueMaterial->SetNormalMap(m_stonebricksNormalMap->GetId());
		auto statueRenderer = m_statue->AddComponent<ansi::Renderer>(m_statueIE, statueMaterial);

		/* === 바닥 오브젝트 === */
		m_floor = AddObject(new ansi::Object("Floor"));
		m_floor->GetTransform()->SetPositionY(-15.0f);
		m_floor->GetTransform()->SetRotationX(-90.0f);

		auto floorMaterial = new NormalMappingMaterial(m_normalMappingShader->GetId(), directionalLight);
		floorMaterial->SetDiffuseMap(m_stonebricksDiffuseMap->GetId());
		floorMaterial->SetNormalMap(m_stonebricksNormalMap->GetId());
		auto floorRenderer = m_floor->AddComponent<ansi::Renderer>(m_floorIE, floorMaterial);

		return ExampleScene::Initialize();
	}

	bool NormalMappingScene::OnUpdate()
	{
		if (m_isAutoRotate) { m_lightAnchor->GetTransform()->AddRotationY(45.0f * DELTA_TIME); }

		return true;
	}

	bool NormalMappingScene::OnRenderGui()
	{
		ImGui::Text(">--------- Render Settings ---------<");

		/* [체크박스] - 와이어프레임 */
		if (ImGui::Checkbox("Wireframe", &m_isWireframe))
		{
			m_statue->FindComponent<ansi::Renderer>()->GetMaterial()->SetFillMode((m_isWireframe) ? ansi::FillMode::Wireframe : ansi::FillMode::Solid);
		}

		/* [체크박스] - 자동 회전 */
		ImGui::Checkbox("Auto Rotation", &m_isAutoRotate);

		/* [슬라이더] - 정반사 강도 */
		if (ImGui::SliderFloat("Specular Intensity", &m_specularIntensity, 0.0f, 3.0f))
		{
			m_statue->FindComponent<ansi::Renderer>()->GetMaterial()->SetSpecularIntensity(m_specularIntensity);
		}

		/* [슬라이더] - 정반사 하이라이트 */
		if (ImGui::SliderFloat("Specular Power", &m_specularPower, 1.0f, 100.0f))
		{
			m_statue->FindComponent<ansi::Renderer>()->GetMaterial()->SetSpecularPower(m_specularPower);
		}

		/* [색상] - 광원 색상 */
		if (ImGui::ColorEdit3("Light Color", glm::value_ptr(m_lightColor)))
		{
			m_directionalLight->FindComponent<ansi::DirectionalLight>()->SetColor(m_lightColor);
		}

		/* [드래그] - 광원 회전 */
		if (ImGui::DragFloat2("Light Rotation", glm::value_ptr(m_lightRotation), 1.0f))
		{
			m_lightAnchor->GetTransform()->SetRotation(m_lightRotation.x, m_lightRotation.y, 0.0f);
		}

		return ExampleScene::OnRenderGui();
	}

	bool NormalMappingScene::CreateResources()
	{
		/* === 셰이더 === */
		/* 색상 */
		CHECK_RF(m_colorShader = GetResources()->CreateShader("assets/shader/color.shader"));
		/* 법선 매핑 */
		CHECK_RF(m_normalMappingShader = GetResources()->CreateShader("assets/shader/normal_mapping.shader"));

		/* === 지오메트리 === */
		/* 광원 */
		auto lightGeometry = GetResources()->CreateGeometry();
		CHECK_RF(lightGeometry->GenerateSphere(5.0f));
		CHECK_RF(m_lightIE = lightGeometry->CreateInputElements(0));
		/* 석상 */
		auto statueGeometry{ GetResources()->CreateGeometry() };
		CHECK_RF(statueGeometry->GenerateFromObj("assets/model/angel.obj"));
		CHECK_RF(m_statueIE = statueGeometry->CreateInputElements(ansi::VA_TEXCOORD | ansi::VA_NORMAL));
		/* 바닥 */
		auto floorGeometry = GetResources()->CreateGeometry();
		CHECK_RF(floorGeometry->GeneratePlane(200.0f, 200.0f));
		CHECK_RF(m_floorIE = floorGeometry->CreateInputElements(ansi::VA_TEXCOORD | ansi::VA_NORMAL));

		/* === 텍스처 === */
		/* 석재 */
		CHECK_RF(m_stonebricksDiffuseMap = GetResources()->CreateTexture("assets/texture/stonebricks_diffuse.jpg"));
		CHECK_RF(m_stonebricksNormalMap = GetResources()->CreateTexture("assets/texture/stonebricks_normal.jpg"));

		return true;
	}

}
