#include "shadow_scene.h"

#include "../../material/color/color_material.h"
#include "../../material/screen_plane/screen_plane_material.h"
#include "../../material/shadow/shadow_material.h"

namespace example
{

	const std::string ShadowScene::m_SceneName{ "07 - Shadow" };

	ShadowScene::ShadowScene()
		: m_isAutoRotate(false)
		, m_isVisibleDepthMap(true)
		, m_depthMapCameraZoom(20.0f)
		, m_lightRotation(-45.0f, 225.0f)
	{

	}

	bool ShadowScene::Initialize()
	{
		/* === �𷺼ų� ����Ʈ === */
		m_lightAnchor = AddObject(new ansi::Object("Light Anchor"));
		m_lightAnchor->GetTransform()->SetEulerOrder(EulerOrder::YXZ);
		m_lightAnchor->GetTransform()->SetRotation(m_lightRotation.x, m_lightRotation.y, 0.0f);

		m_directionalLight = m_lightAnchor->AddChild(new ansi::Object("Directional Light"));
		m_directionalLight->GetTransform()->SetPositionY(150.0f);
		m_directionalLight->GetTransform()->SetRotationX(90.0f);

		auto directionalLight = m_directionalLight->AddComponent<ansi::DirectionalLight>();
		directionalLight->CastShadow();
		directionalLight->GetDepthMapCamera()->SetZoom(m_depthMapCameraZoom);
		auto directionalLightMaterial = new ColorMaterial(m_colorShader->GetId());
		directionalLightMaterial->SetColor(glm::vec3(1.0f, 1.0f, 0.0f));
		auto directionalLightRenderer = m_directionalLight->AddComponent<ansi::Renderer>(m_lightIE, directionalLightMaterial);

		/* === ���� ������Ʈ === */
		m_statue = AddObject(new ansi::Object("Statue"));
		m_statue->GetTransform()->SetPositionY(-15.0f);
		m_statue->GetTransform()->SetScale(5.0f);

		auto statueMaterial = new ShadowMaterial(m_shadowShader->GetId(), directionalLight);
		auto statueRenderer = m_statue->AddComponent<ansi::Renderer>(m_statueIE, statueMaterial);
		statueRenderer->SetIsCastShadow(true);

		/* === �ٴ� ������Ʈ === */
		m_floor = AddObject(new ansi::Object("Floor"));
		m_floor->GetTransform()->SetPositionY(-15.0f);
		m_floor->GetTransform()->SetRotationX(-90.0f);

		auto floorMaterial = new ShadowMaterial(m_shadowShader->GetId(), directionalLight);
		auto floorRenderer = m_floor->AddComponent<ansi::Renderer>(m_floorIE, floorMaterial);

		/* === ���̸� ��� ������Ʈ === */
		m_depthMapPlane = AddObject(new ansi::Object("Depth Map Plane"));
		m_depthMapPlane->SetIsEnabled(m_isVisibleDepthMap);

		auto depthMapPlaneMaterial = new ScreenPlaneMaterial(m_screenPlaneShader->GetId(),
			directionalLight->GetDepthMapCamera()->GetFramebuffer()->GetDepthTextureId(),
			glm::vec4(10.0f, 10.0f, 200.0f, 200.0f));
		depthMapPlaneMaterial->SetColor(glm::vec3(0.90f, 0.90f, 1.0f));
		auto depthMapPlaneRenderer = m_depthMapPlane->AddComponent<ansi::Renderer>(m_depthMapPlaneIE, depthMapPlaneMaterial, ansi::RendererType::Hud);

		return ExampleScene::Initialize();
	}

	bool ShadowScene::OnUpdate()
	{
		if (m_isAutoRotate) { m_lightAnchor->GetTransform()->AddRotationY(45.0f * DELTA_TIME); }

		return true;
	}

	bool ShadowScene::OnRenderGui()
	{
		ImGui::Text(">--------- Render Settings ---------<");

		/* [�巡��] - ���� ȸ�� */
		if (ImGui::DragFloat2("Light Rotation", glm::value_ptr(m_lightRotation), 1.0f))
		{
			m_lightAnchor->GetTransform()->SetRotation(m_lightRotation.x, m_lightRotation.y, 0.0f);
		}

		/* [�����̴�] - ���̸� ī�޶� �� */
		if (ImGui::SliderFloat("Depth Map Zoom", &m_depthMapCameraZoom, 1.0f, 50.0f))
		{
			m_directionalLight->FindComponent<ansi::DirectionalLight>()->GetDepthMapCamera()->SetZoom(m_depthMapCameraZoom);
		}

		/* [üũ�ڽ�] - �ڵ� ȸ�� */
		ImGui::Checkbox("Auto Rotation", &m_isAutoRotate);

		/* [üũ�ڽ�] - ���̸� ǥ�� ���� */
		if (ImGui::Checkbox("Show Depth Map", &m_isVisibleDepthMap))
		{
			m_depthMapPlane->SetIsEnabled(m_isVisibleDepthMap);
		}

		return ExampleScene::OnRenderGui();
	}

	bool ShadowScene::CreateResources()
	{
		/* === ���̴� === */
		/* ���� */
		CHECK_RF(m_colorShader = GetResources()->CreateShader("assets/shader/color.shader"));
		/* �׸��� */
		CHECK_RF(m_shadowShader = GetResources()->CreateShader("assets/shader/shadow.shader"));
		/* ȭ�� ���� ��� */
		CHECK_RF(m_screenPlaneShader = GetResources()->CreateShader("assets/shader/screen_plane.shader"));

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
		/* ���̸� ��� */
		auto depthMapPlaneGeometry = GetResources()->CreateGeometry();
		CHECK_RF(depthMapPlaneGeometry->GeneratePlane(1.0f, 1.0f));
		CHECK_RF(m_depthMapPlaneIE= depthMapPlaneGeometry->CreateInputElements(ansi::VA_TEXCOORD));

		return true;
	}

}
