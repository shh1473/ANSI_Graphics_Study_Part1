#include "cel_shading_scene.h"

#include "../../material/color/color_material.h"
#include "../../material/cel_shading/cel_shading_material.h"

namespace example
{

	const std::string CelShadingScene::m_SceneName{ "05 - Cel Shading" };

	CelShadingScene::CelShadingScene()
		: m_isAutoRotate(false)
		, m_celLevel(5.0f)
		, m_specularIntensity(1.0f)
		, m_specularPower(32.0f)
		, m_lightColor(0.6f, 1.0f, 1.0f)
		, m_lightRotation(-45.0f, 225.0f)
	{

	}

	bool CelShadingScene::Initialize()
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

		auto statueMaterial = new CelShadingMaterial(m_celShadingShader->GetId(), directionalLight);
		statueMaterial->SetSpecularIntensity(m_specularIntensity);
		statueMaterial->SetSpecularPower(m_specularPower);
		auto statueRenderer = m_statue->AddComponent<ansi::Renderer>(m_statueIE, statueMaterial);

		/* === �ٴ� ������Ʈ === */
		m_floor = AddObject(new ansi::Object("Floor"));
		m_floor->GetTransform()->SetPositionY(-15.0f);
		m_floor->GetTransform()->SetRotationX(-90.0f);

		auto floorMaterial = new CelShadingMaterial(m_celShadingShader->GetId(), directionalLight);
		auto floorRenderer = m_floor->AddComponent<ansi::Renderer>(m_floorIE, floorMaterial);

		return ExampleScene::Initialize();
	}

	bool CelShadingScene::OnUpdate()
	{
		if (m_isAutoRotate) { m_lightAnchor->GetTransform()->AddRotationY(45.0f * DELTA_TIME); }

		return true;
	}

	bool CelShadingScene::OnRenderGui()
	{
		ImGui::Text(">--------- Render Settings ---------<");

		/* [üũ�ڽ�] - �ڵ� ȸ�� */
		ImGui::Checkbox("Auto Rotation", &m_isAutoRotate);

		/* [�����̴�] - �� ���̵� ���� */
		if (ImGui::SliderFloat("Cel Level", &m_celLevel, 1.0f, 10.0f))
		{
			static_cast<CelShadingMaterial *>(m_statue->FindComponent<ansi::Renderer>()->GetMaterial())->SetCelLevel(m_celLevel);
			static_cast<CelShadingMaterial *>(m_floor->FindComponent<ansi::Renderer>()->GetMaterial())->SetCelLevel(m_celLevel);
		}

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

	bool CelShadingScene::CreateResources()
	{
		/* === ���̴� === */
		/* ���� */
		CHECK_RF(m_colorShader = GetResources()->CreateShader("assets/shader/color.shader"));
		/* �� ���̵� */
		CHECK_RF(m_celShadingShader = GetResources()->CreateShader("assets/shader/cel_shading.shader"));

		/* === ������Ʈ�� === */
		/* ���� */
		auto lightGeometry = GetResources()->CreateGeometry();
		CHECK_RF(lightGeometry->GenerateSphere(5.0f));
		CHECK_RF(m_lightIE = lightGeometry->CreateInputElements(0));
		/* ���� */
		auto statueGeometry = GetResources()->CreateGeometry();
		CHECK_RF(statueGeometry->GenerateFromObj("assets/model/angel.obj"));
		CHECK_RF(m_statueIE = statueGeometry->CreateInputElements(ansi::VA_NORMAL));
		/* �ٴ� */
		auto floorGeometry = GetResources()->CreateGeometry();
		CHECK_RF(floorGeometry->GeneratePlane(200.0f, 200.0f));
		CHECK_RF(m_floorIE = floorGeometry->CreateInputElements(ansi::VA_NORMAL));

		return true;
	}

}
