#include "texture_scene.h"

#include "../../material/texture/texture_material.h"

namespace example
{

	const std::string TextureScene::m_SceneName{ "02 - Texture" };

	TextureScene::TextureScene()
		: m_textureScale(5.0f)
	{

	}

	bool TextureScene::Initialize()
	{
		/* === 석상 오브젝트 === */
		m_statue = AddObject(new ansi::Object("Statue"));
		m_statue->GetTransform()->SetPositionY(-15.0f);
		m_statue->GetTransform()->SetScale(5.0f);

		auto statueMaterial = new TextureMaterial(m_textureShader->GetId());
		statueMaterial->SetTextureScale(m_textureScale);
		statueMaterial->SetDiffuseMap(m_stonebricksDiffuseMap->GetId());
		auto statueRenderer = m_statue->AddComponent<ansi::Renderer>(m_statueIE, statueMaterial);

		/* === 바닥 오브젝트 === */
		m_floor = AddObject(new ansi::Object("Floor"));
		m_floor->GetTransform()->SetPositionY(-15.0f);
		m_floor->GetTransform()->SetRotationX(-90.0f);

		auto floorMaterial = new TextureMaterial(m_textureShader->GetId());
		floorMaterial->SetTextureScale(m_textureScale);
		floorMaterial->SetDiffuseMap(m_stonebricksDiffuseMap->GetId());
		auto floorRenderer = m_floor->AddComponent<ansi::Renderer>(m_floorIE, floorMaterial);

		return ExampleScene::Initialize();
	}

	bool TextureScene::OnRenderGui()
	{
		ImGui::Text(">--------- Render Settings ---------<");

		/* [슬라이더] - 텍스처 좌표 스케일 */
		if (ImGui::SliderFloat("Texture Scale", &m_textureScale, 1.0f, 10.0f))
		{
			static_cast<TextureMaterial *>(m_statue->FindComponent<ansi::Renderer>()->GetMaterial())->SetTextureScale(m_textureScale);
			static_cast<TextureMaterial *>(m_floor->FindComponent<ansi::Renderer>()->GetMaterial())->SetTextureScale(m_textureScale);
		}

		return ExampleScene::OnRenderGui();
	}

	bool TextureScene::CreateResources()
	{
		/* === 셰이더 === */
		/* 텍스처 */
		CHECK_RF(m_textureShader = GetResources()->CreateShader("assets/shader/texture.shader"));

		/* === 지오메트리 === */
		/* 석상 */
		auto statueGeometry = GetResources()->CreateGeometry();
		CHECK_RF(statueGeometry->GenerateFromObj("assets/model/angel.obj"));
		CHECK_RF(m_statueIE = statueGeometry->CreateInputElements(ansi::VA_TEXCOORD));
		/* 바닥 */
		auto floorGeometry = GetResources()->CreateGeometry();
		CHECK_RF(floorGeometry->GeneratePlane(200.0f, 200.0f));
		CHECK_RF(m_floorIE = floorGeometry->CreateInputElements(ansi::VA_TEXCOORD));

		/* === 텍스처 === */
		/* 석재 */
		CHECK_RF(m_stonebricksDiffuseMap = GetResources()->CreateTexture("assets/texture/stonebricks_diffuse.jpg"));

		return true;
	}

}
