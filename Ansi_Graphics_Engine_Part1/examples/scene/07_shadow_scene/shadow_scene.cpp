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
		/* === 디렉셔널 라이트 === */
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

		/* === 석상 오브젝트 === */
		m_statue = AddObject(new ansi::Object("Statue"));
		m_statue->GetTransform()->SetPositionY(-15.0f);
		m_statue->GetTransform()->SetScale(5.0f);

		auto statueMaterial = new ShadowMaterial(m_shadowShader->GetId(), directionalLight);
		auto statueRenderer = m_statue->AddComponent<ansi::Renderer>(m_statueIE, statueMaterial);
		statueRenderer->SetIsCastShadow(true);

		/* === 바닥 오브젝트 === */
		m_floor = AddObject(new ansi::Object("Floor"));
		m_floor->GetTransform()->SetPositionY(-15.0f);
		m_floor->GetTransform()->SetRotationX(-90.0f);

		auto floorMaterial = new ShadowMaterial(m_shadowShader->GetId(), directionalLight);
		auto floorRenderer = m_floor->AddComponent<ansi::Renderer>(m_floorIE, floorMaterial);

		/* === 깊이맵 평면 오브젝트 === */
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

		/* [드래그] - 광원 회전 */
		if (ImGui::DragFloat2("Light Rotation", glm::value_ptr(m_lightRotation), 1.0f))
		{
			m_lightAnchor->GetTransform()->SetRotation(m_lightRotation.x, m_lightRotation.y, 0.0f);
		}

		/* [슬라이더] - 깊이맵 카메라 줌 */
		if (ImGui::SliderFloat("Depth Map Zoom", &m_depthMapCameraZoom, 1.0f, 50.0f))
		{
			m_directionalLight->FindComponent<ansi::DirectionalLight>()->GetDepthMapCamera()->SetZoom(m_depthMapCameraZoom);
		}

		/* [체크박스] - 자동 회전 */
		ImGui::Checkbox("Auto Rotation", &m_isAutoRotate);

		/* [체크박스] - 깊이맵 표시 여부 */
		if (ImGui::Checkbox("Show Depth Map", &m_isVisibleDepthMap))
		{
			m_depthMapPlane->SetIsEnabled(m_isVisibleDepthMap);
		}

		return ExampleScene::OnRenderGui();
	}

	bool ShadowScene::CreateResources()
	{
		/* === 셰이더 === */
		/* 색상 */
		CHECK_RF(m_colorShader = GetResources()->CreateShader("assets/shader/color.shader"));
		/* 그림자 */
		CHECK_RF(m_shadowShader = GetResources()->CreateShader("assets/shader/shadow.shader"));
		/* 화면 공간 평면 */
		CHECK_RF(m_screenPlaneShader = GetResources()->CreateShader("assets/shader/screen_plane.shader"));

		/* === 지오메트리 === */
		/* 광원 */
		auto lightGeometry = GetResources()->CreateGeometry();
		CHECK_RF(lightGeometry->GenerateSphere(5.0f));
		CHECK_RF(m_lightIE = lightGeometry->CreateInputElements(0));
		/* 석상 */
		auto statueGeometry = GetResources()->CreateGeometry();
		CHECK_RF(statueGeometry->GenerateFromObj("assets/model/angel.obj"));
		CHECK_RF(m_statueIE = statueGeometry->CreateInputElements(ansi::VA_NORMAL));
		/* 바닥 */
		auto floorGeometry = GetResources()->CreateGeometry();
		CHECK_RF(floorGeometry->GeneratePlane(200.0f, 200.0f));
		CHECK_RF(m_floorIE = floorGeometry->CreateInputElements(ansi::VA_NORMAL));
		/* 깊이맵 평면 */
		auto depthMapPlaneGeometry = GetResources()->CreateGeometry();
		CHECK_RF(depthMapPlaneGeometry->GeneratePlane(1.0f, 1.0f));
		CHECK_RF(m_depthMapPlaneIE= depthMapPlaneGeometry->CreateInputElements(ansi::VA_TEXCOORD));

		return true;
	}

}
