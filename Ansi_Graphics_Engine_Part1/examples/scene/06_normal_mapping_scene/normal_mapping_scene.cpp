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
		/* === �𷺼ų� ����Ʈ === */
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

		/* === ���� ������Ʈ === */
		m_statue = AddObject(new ansi::Object("Statue"));
		m_statue->GetTransform()->SetPositionY(-15.0f);
		m_statue->GetTransform()->SetScale(5.0f);

		auto statueMaterial = new NormalMappingMaterial(m_normalMappingShader->GetId(), directionalLight);
		statueMaterial->SetSpecularIntensity(m_specularIntensity);
		statueMaterial->SetSpecularPower(m_specularPower);
		statueMaterial->SetDiffuseMap(m_stonebricksDiffuseMap->GetId());
		statueMaterial->SetNormalMap(m_stonebricksNormalMap->GetId());
		auto statueRenderer = m_statue->AddComponent<ansi::Renderer>(m_statueIE, statueMaterial);

		/* === �ٴ� ������Ʈ === */
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

		/* [üũ�ڽ�] - ���̾������� */
		if (ImGui::Checkbox("Wireframe", &m_isWireframe))
		{
			m_statue->FindComponent<ansi::Renderer>()->GetMaterial()->SetFillMode((m_isWireframe) ? ansi::FillMode::Wireframe : ansi::FillMode::Solid);
		}

		/* [üũ�ڽ�] - �ڵ� ȸ�� */
		ImGui::Checkbox("Auto Rotation", &m_isAutoRotate);

		/* [�����̴�] - ���ݻ� ���� */
		if (ImGui::SliderFloat("Specular Intensity", &m_specularIntensity, 0.0f, 3.0f))
		{
			m_statue->FindComponent<ansi::Renderer>()->GetMaterial()->SetSpecularIntensity(m_specularIntensity);
		}

		/* [�����̴�] - ���ݻ� ���̶���Ʈ */
		if (ImGui::SliderFloat("Specular Power", &m_specularPower, 1.0f, 100.0f))
		{
			m_statue->FindComponent<ansi::Renderer>()->GetMaterial()->SetSpecularPower(m_specularPower);
		}

		/* [����] - ���� ���� */
		if (ImGui::ColorEdit3("Light Color", glm::value_ptr(m_lightColor)))
		{
			m_directionalLight->FindComponent<ansi::DirectionalLight>()->SetColor(m_lightColor);
		}

		/* [�巡��] - ���� ȸ�� */
		if (ImGui::DragFloat2("Light Rotation", glm::value_ptr(m_lightRotation), 1.0f))
		{
			m_lightAnchor->GetTransform()->SetRotation(m_lightRotation.x, m_lightRotation.y, 0.0f);
		}

		return ExampleScene::OnRenderGui();
	}

	bool NormalMappingScene::CreateResources()
	{
		/* === ���̴� === */
		/* ���� */
		CHECK_RF(m_colorShader = GetResources()->CreateShader("assets/shader/color.shader"));
		/* ���� ���� */
		CHECK_RF(m_normalMappingShader = GetResources()->CreateShader("assets/shader/normal_mapping.shader"));

		/* === ������Ʈ�� === */
		/* ���� */
		auto lightGeometry = GetResources()->CreateGeometry();
		CHECK_RF(lightGeometry->GenerateSphere(5.0f));
		CHECK_RF(m_lightIE = lightGeometry->CreateInputElements(0));
		/* ���� */
		auto statueGeometry{ GetResources()->CreateGeometry() };
		CHECK_RF(statueGeometry->GenerateFromObj("assets/model/angel.obj"));
		CHECK_RF(m_statueIE = statueGeometry->CreateInputElements(ansi::VA_TEXCOORD | ansi::VA_NORMAL));
		/* �ٴ� */
		auto floorGeometry = GetResources()->CreateGeometry();
		CHECK_RF(floorGeometry->GeneratePlane(200.0f, 200.0f));
		CHECK_RF(m_floorIE = floorGeometry->CreateInputElements(ansi::VA_TEXCOORD | ansi::VA_NORMAL));

		/* === �ؽ�ó === */
		/* ���� */
		CHECK_RF(m_stonebricksDiffuseMap = GetResources()->CreateTexture("assets/texture/stonebricks_diffuse.jpg"));
		CHECK_RF(m_stonebricksNormalMap = GetResources()->CreateTexture("assets/texture/stonebricks_normal.jpg"));

		return true;
	}

}
