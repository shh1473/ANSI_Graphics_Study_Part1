#include "color_scene.h"

#include "../../material/color/color_material.h"

namespace example
{

	const std::string ColorScene::m_SceneName{ "01 - Color" };

	ColorScene::ColorScene()
		: m_isWireframe(false)
		, m_boxColor(glm::vec3(0.0f, 1.0f, 0.0f))
	{

	}

	bool ColorScene::Initialize()
	{
		/* === 박스 오브젝트 === */
		m_box = AddObject(new ansi::Object("Box"));
		m_box->GetTransform()->SetPositionX(0.0f);
		m_box->GetTransform()->SetScale(5.0f);

		auto boxMaterial = new ColorMaterial(m_colorShader->GetId());
		boxMaterial->SetColor(m_boxColor);
		boxMaterial->SetCullMode(ansi::CullMode::None);
		m_box->AddComponent<ansi::Renderer>(m_boxIE, boxMaterial);

		/* === 구체 오브젝트 === */
		m_sphere = AddObject(new ansi::Object("Sphere"));
		m_sphere->GetTransform()->SetPositionX(20.0f);
		m_sphere->GetTransform()->SetScale(5.0f);

		auto sphereMaterial = new ColorMaterial(m_colorShader->GetId());
		sphereMaterial->SetColor(glm::vec3(0.0f, 0.0f, 1.0f));
		sphereMaterial->SetCullMode(ansi::CullMode::None);
		m_sphere->AddComponent<ansi::Renderer>(m_sphereIE, sphereMaterial);

		/* === 원기둥 오브젝트 === */
		m_cylinder = AddObject(new ansi::Object("Cylinder"));
		m_cylinder->GetTransform()->SetPositionX(-20.0f);
		m_cylinder->GetTransform()->SetScale(5.0f);

		auto cylinderMaterial = new ColorMaterial(m_colorShader->GetId());
		cylinderMaterial->SetColor(glm::vec3(1.0f, 0.0f, 0.0f));
		cylinderMaterial->SetCullMode(ansi::CullMode::None);
		m_cylinder->AddComponent<ansi::Renderer>(m_cylinderIE, cylinderMaterial);

		return ExampleScene::Initialize();
	}

	bool ColorScene::OnRenderGui()
	{
		ImGui::Text(">--------- Render Settings ---------<");

		/* [컬러] - 박스 색상 */
		if (ImGui::ColorEdit3("Box Color", glm::value_ptr(m_boxColor)))
		{
			m_box->FindComponent<ansi::Renderer>()->GetMaterial()->SetColor(m_boxColor);
		}

		/* [체크박스] - 와이어프레임 */
		if (ImGui::Checkbox("Wireframe", &m_isWireframe))
		{
			static_cast<ColorMaterial *>(m_box->FindComponent<ansi::Renderer>()->GetMaterial())->
				SetFillMode((m_isWireframe) ? ansi::FillMode::Wireframe : ansi::FillMode::Solid);
			static_cast<ColorMaterial *>(m_sphere->FindComponent<ansi::Renderer>()->GetMaterial())->
				SetFillMode((m_isWireframe) ? ansi::FillMode::Wireframe : ansi::FillMode::Solid);
			static_cast<ColorMaterial *>(m_cylinder->FindComponent<ansi::Renderer>()->GetMaterial())->
				SetFillMode((m_isWireframe) ? ansi::FillMode::Wireframe : ansi::FillMode::Solid);
		}

		return ExampleScene::OnRenderGui();
	}

	bool ColorScene::CreateResources()
	{
		/* === 셰이더 === */
		/* 색상 */
		CHECK_RF(m_colorShader = GetResources()->CreateShader("assets/shader/color.shader"));

		/* === 지오메트리 === */
		/* 박스 */
		auto boxGeometry = GetResources()->CreateGeometry();
		CHECK_RF(boxGeometry->GenerateBox(2.0f, 2.0f, 2.0f, 1, 1, 1));
		CHECK_RF(m_boxIE = boxGeometry->CreateInputElements(0));
		/* 구체 */
		auto sphereGeometry = GetResources()->CreateGeometry();
		CHECK_RF(sphereGeometry->GenerateSphere(1.0f, 16, 8));
		CHECK_RF(m_sphereIE = sphereGeometry->CreateInputElements(0));
		/* 원기둥 */
		auto cylinderGeometry = GetResources()->CreateGeometry();
		CHECK_RF(cylinderGeometry->GenerateCylinder(1.0f, 1.0f, 2.0f, 12, 1));
		CHECK_RF(m_cylinderIE = cylinderGeometry->CreateInputElements(0));

		return true;
	}

}
