#include "final_scene.h"

#include "../../material/color/color_material.h"
#include "../../material/screen_plane/screen_plane_material.h"
#include "../../material/all_in_one/all_in_one_material.h"
#include "../../material/filter_matrix/filter_matrix_material.h"
#include "../../material/luminance_extraction/luminance_extraction_material.h"
#include "../../material/gaussian_blur/gaussian_blur_material.h"
#include "../../material/bloom/bloom_material.h"

namespace example
{

	const std::string FinalScene::m_SceneName{ "08 - Final" };

	FinalScene::FinalScene()
		: m_isVisibleDepthMap(false)
		, m_specularIntensity(1.0f)
		, m_specularPower(32.0f)
		, m_ambientLightUpColor(0.7f, 0.7f, 0.0f)
		, m_ambientLightDownColor(0.5f, 0.0f, 0.0f)
		, m_directionalLightColor(1.0f)
		, m_directionalLightRotation(-45.0f, 225.0f)
		, m_isEnableGrayscale(false)
		, m_isEnableInvert(false)
		, m_brightness(1.0f)
		, m_bloomThreshold(0.6f)
		, m_bloomRadius(3)
	{

	}

	bool FinalScene::Initialize()
	{
		/* === �ں��Ʈ ����Ʈ === */
		m_ambientLight = AddObject(new ansi::Object("Ambient Light"));

		auto ambientLight = m_ambientLight->AddComponent<ansi::HSAmbientLight>(m_ambientLightUpColor, m_ambientLightDownColor);

		/* === �𷺼ų� ����Ʈ === */
		m_lightAnchor = AddObject(new ansi::Object("Light Anchor"));
		m_lightAnchor->GetTransform()->SetEulerOrder(EulerOrder::YXZ);
		m_lightAnchor->GetTransform()->SetRotation(m_directionalLightRotation.x, m_directionalLightRotation.y, 0.0f);

		m_directionalLight = m_lightAnchor->AddChild(new ansi::Object("Directional Light"));
		m_directionalLight->GetTransform()->SetPositionY(150.0f);
		m_directionalLight->GetTransform()->SetRotationX(90.0f);

		auto directionalLight = m_directionalLight->AddComponent<ansi::DirectionalLight>(m_directionalLightColor);
		directionalLight->CastShadow();
		directionalLight->GetDepthMapCamera()->SetZoom(20.0f);
		auto directionalLightMaterial = new ColorMaterial(m_colorShader->GetId());
		directionalLightMaterial->SetColor(glm::vec3(1.0f, 1.0f, 0.0f));
		auto directionalLightRenderer = m_directionalLight->AddComponent<ansi::Renderer>(m_lightIE, directionalLightMaterial);

		/* === ���� ������Ʈ === */
		m_statue = AddObject(new ansi::Object("Statue"));
		m_statue->GetTransform()->SetPositionY(-15.0f);
		m_statue->GetTransform()->SetScale(5.0f);

		auto statueMaterial = new AllInOneMaterial(m_allInOneShader->GetId(), ambientLight, directionalLight);
		statueMaterial->SetSpecularIntensity(2.0f);
		statueMaterial->SetDiffuseMap(m_stonebricksDiffuseMap->GetId());
		statueMaterial->SetNormalMap(m_stonebricksNormalMap->GetId());
		auto statueRenderer = m_statue->AddComponent<ansi::Renderer>(m_statueIE, statueMaterial);
		statueRenderer->SetIsCastShadow(true);

		/* === �ٴ� ������Ʈ === */
		m_floor = AddObject(new ansi::Object("Floor"));
		m_floor->GetTransform()->SetPositionY(-15.0f);
		m_floor->GetTransform()->SetRotationX(-90.0f);

		auto floorMaterial = new AllInOneMaterial(m_allInOneShader->GetId(), ambientLight, directionalLight);
		floorMaterial->SetDiffuseMap(m_stonebricksDiffuseMap->GetId());
		floorMaterial->SetNormalMap(m_stonebricksNormalMap->GetId());
		auto floorRenderer = m_floor->AddComponent<ansi::Renderer>(m_floorIE, floorMaterial);

		/* === ���̸� ��� ������Ʈ === */
		m_depthMapPlane = AddObject(new ansi::Object("Depth Map Plane"));
		m_depthMapPlane->SetIsEnabled(m_isVisibleDepthMap);

		auto depthMapPlaneMaterial = new ScreenPlaneMaterial(m_screenPlaneShader->GetId(),
			directionalLight->GetDepthMapCamera()->GetFramebuffer()->GetDepthTextureId(),
			glm::vec4(10.0f, 10.0f, 200.0f, 200.0f));
		depthMapPlaneMaterial->SetColor(glm::vec3(0.90f, 0.90f, 1.0f));
		auto depthMapPlaneRenderer = m_depthMapPlane->AddComponent<ansi::Renderer>(m_depthMapPlaneIE, depthMapPlaneMaterial, ansi::RendererType::Hud);

		/* === �⺻ ��ó�� ī�޶� ������Ʈ === */
		m_defaultCamera = AddObject(new ansi::Object("Default Camera"));
		m_defaultCamera->GetTransform()->SetPositionZ(60.0f);

		auto camera = m_defaultCamera->AddComponent<ansi::PostEffectCamera>();
		CHECK_RF(camera->Initialize());
		camera->GetOutput()->SetClearColor(glm::vec4(0.53f, 0.81f, 0.92f, 1.0f));

		/* === �⺻ ī�޶� �˵��� ��Ʈ�ѷ� === */
		m_defaultOrbitControls = new ansi::OrbitControls(camera);
		camera->SetOrbitControls(m_defaultOrbitControls);

		/* === ���� ��� ��ó�� ȿ�� === */
		auto colorMatrixMaterial = new FilterMatrixMaterial(m_filterMatrixShader->GetId(), camera->GetFramebuffer()->GetColorTextureId());
		colorMatrixMaterial->SetIsEnableGrayscale(m_isEnableGrayscale);
		colorMatrixMaterial->SetIsEnableInvert(m_isEnableInvert);
		colorMatrixMaterial->SetBrightness(m_brightness);
		auto colorMatrixEffect = camera->AddEffect(new ansi::PostEffect(colorMatrixMaterial), true);

		/* === �ֵ� ���� ��ó�� ȿ�� === */
		auto luminanceExtractionMaterial = new LuminanceExtractionMaterial(m_luminanceExtractionShader->GetId(), colorMatrixEffect->GetFramebuffer()->GetColorTextureId());
		luminanceExtractionMaterial->SetThreshold(m_bloomThreshold);
		auto luminanceExtractionEffect = camera->AddEffect(new ansi::PostEffect(luminanceExtractionMaterial), true);

		/* === ����þ� �� ��ó�� ȿ�� === */
		auto gaussianBlurMaterial = new GaussianBlurMaterial(m_gaussianBlurShader->GetId(), luminanceExtractionEffect->GetFramebuffer()->GetColorTextureId());
		gaussianBlurMaterial->SetRadius(m_bloomRadius);
		auto gaussianBlurEffect = camera->AddEffect(new ansi::PostEffect(gaussianBlurMaterial), true);

		/* === ��� ��ó�� ȿ�� === */
		auto bloomMaterial = new BloomMaterial(m_bloomShader->GetId(),
			colorMatrixEffect->GetFramebuffer()->GetColorTextureId(),
			gaussianBlurEffect->GetFramebuffer()->GetColorTextureId());
		auto bloomEffect = camera->AddEffect(new ansi::PostEffect(bloomMaterial));

		return true;
	}

	bool FinalScene::OnUpdate()
	{
		if (m_isAutoRotate) { m_lightAnchor->GetTransform()->AddRotationY(45.0f * DELTA_TIME); }

		return true;
	}

	bool FinalScene::OnRenderGui()
	{
		ImGui::Text(">--------- Render Settings ---------<");

		/* [����] - �ں��Ʈ ����Ʈ ���� ���� */
		if (ImGui::ColorEdit3("UpColor", glm::value_ptr(m_ambientLightUpColor)))
		{
			m_ambientLight->FindComponent<ansi::HSAmbientLight>()->SetUpColor(m_ambientLightUpColor);
		}

		/* [����] - �ں��Ʈ ����Ʈ �Ʒ��� ���� */
		if (ImGui::ColorEdit3("DownColor", glm::value_ptr(m_ambientLightDownColor)))
		{
			m_ambientLight->FindComponent<ansi::HSAmbientLight>()->SetDownColor(m_ambientLightDownColor);
		}

		/* [����] - �𷺼ų� ����Ʈ ���� */
		if (ImGui::ColorEdit3("Directional Light Color", glm::value_ptr(m_directionalLightColor)))
		{
			m_directionalLight->FindComponent<ansi::DirectionalLight>()->SetColor(m_directionalLightColor);
		}

		/* [�巡��] - �𷺼ų� ����Ʈ ȸ�� */
		if (ImGui::DragFloat2("Directional Light Rotation", glm::value_ptr(m_directionalLightRotation), 1.0f))
		{
			m_lightAnchor->GetTransform()->SetRotation(m_directionalLightRotation.x, m_directionalLightRotation.y, 0.0f);
		}

		/* [üũ�ڽ�] - �ڵ� ȸ�� */
		ImGui::Checkbox("Auto Rotation", &m_isAutoRotate);

		/* [üũ�ڽ�] - ���̸� ǥ�� ���� */
		if (ImGui::Checkbox("Show Depth Map", &m_isVisibleDepthMap))
		{
			m_depthMapPlane->SetIsEnabled(m_isVisibleDepthMap);
		}

		/* [üũ�ڽ�] - ��� */
		if (ImGui::Checkbox("Grayscale", &m_isEnableGrayscale))
		{
			static_cast<FilterMatrixMaterial *>(m_defaultCamera->FindComponent<ansi::PostEffectCamera>()->GetEffects()[0]->GetMaterial())
				->SetIsEnableGrayscale(m_isEnableGrayscale);
		}

		/* [üũ�ڽ�] - ���� */
		if (ImGui::Checkbox("Invert", &m_isEnableInvert))
		{
			static_cast<FilterMatrixMaterial *>(m_defaultCamera->FindComponent<ansi::PostEffectCamera>()->GetEffects()[0]->GetMaterial())
				->SetIsEnableInvert(m_isEnableInvert);
		}

		/* [�����̴�] - ��� */
		if (ImGui::SliderFloat("Brightness", &m_brightness, 0.0f, 3.0f))
		{
			static_cast<FilterMatrixMaterial *>(m_defaultCamera->FindComponent<ansi::PostEffectCamera>()->GetEffects()[0]->GetMaterial())
				->SetBrightness(m_brightness);
		}

		/* [�����̴�] - ��� �Ӱ谪 */
		if (ImGui::SliderFloat("Bloom Threshold", &m_bloomThreshold, 0.0f, 1.0f))
		{
			static_cast<LuminanceExtractionMaterial *>(m_defaultCamera->FindComponent<ansi::PostEffectCamera>()->GetEffects()[1]->GetMaterial())
				->SetThreshold(m_bloomThreshold);
		}

		/* [�����̴�] - ��� ���� */
		if (ImGui::SliderInt("Bloom Radius", &m_bloomRadius, 1, 5))
		{
			static_cast<GaussianBlurMaterial *>(m_defaultCamera->FindComponent<ansi::PostEffectCamera>()->GetEffects()[2]->GetMaterial())
				->SetRadius(m_bloomRadius);
		}

		return ExampleScene::OnRenderGui();
	}

	bool FinalScene::CreateResources()
	{
		/* === ���̴� === */
		/* ���� */
		CHECK_RF(m_colorShader = GetResources()->CreateShader("assets/shader/color.shader"));
		/* ���ο� */
		CHECK_RF(m_allInOneShader = GetResources()->CreateShader("assets/shader/all_in_one.shader"));
		/* ȭ�� ���� ��� */
		CHECK_RF(m_screenPlaneShader = GetResources()->CreateShader("assets/shader/screen_plane.shader"));
		/* ���� ��� */
		CHECK_RF(m_filterMatrixShader = GetResources()->CreateShader("assets/shader/filter_matrix.shader"));
		/* �ֵ� ���� */
		CHECK_RF(m_luminanceExtractionShader = GetResources()->CreateShader("assets/shader/luminance_extraction.shader"));
		/* ����þ� �� */
		CHECK_RF(m_gaussianBlurShader = GetResources()->CreateShader("assets/shader/gaussian_blur.shader"));
		/* ��� */
		CHECK_RF(m_bloomShader = GetResources()->CreateShader("assets/shader/bloom_effect.shader"));

		/* === ������Ʈ�� === */
		/* ���� */
		auto lightGeometry = GetResources()->CreateGeometry();
		CHECK_RF(lightGeometry->GenerateSphere(5.0f));
		CHECK_RF(m_lightIE = lightGeometry->CreateInputElements(0));
		/* ���� */
		auto statueGeometry = GetResources()->CreateGeometry();
		CHECK_RF(statueGeometry->GenerateFromObj("assets/model/angel.obj"));
		CHECK_RF(m_statueIE = statueGeometry->CreateInputElements(ansi::VA_TEXCOORD | ansi::VA_NORMAL));
		/* �ٴ� */
		auto floorGeometry = GetResources()->CreateGeometry();
		CHECK_RF(floorGeometry->GeneratePlane(200.0f, 200.0f));
		CHECK_RF(m_floorIE = floorGeometry->CreateInputElements(ansi::VA_TEXCOORD | ansi::VA_NORMAL));
		/* ���̸� ��� */
		auto depthMapPlaneGeometry = GetResources()->CreateGeometry();
		CHECK_RF(depthMapPlaneGeometry->GeneratePlane(1.0f, 1.0f));
		CHECK_RF(m_depthMapPlaneIE = depthMapPlaneGeometry->CreateInputElements(ansi::VA_TEXCOORD));

		/* === �ؽ�ó === */
		/* ���� */
		CHECK_RF(m_stonebricksDiffuseMap = GetResources()->CreateTexture("assets/texture/stonebricks_diffuse.jpg"));
		CHECK_RF(m_stonebricksNormalMap = GetResources()->CreateTexture("assets/texture/stonebricks_normal.jpg"));

		return true;
	}

}
