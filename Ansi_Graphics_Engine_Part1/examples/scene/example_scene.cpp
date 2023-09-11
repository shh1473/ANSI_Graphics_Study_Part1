#include "example_scene.h"

#include "../manager/example_manager.h"

namespace example
{

	/* ������ */
	ExampleScene::ExampleScene()
	{

	}

	bool ExampleScene::Initialize()
	{
		/* === �⺻ ī�޶� ������Ʈ === */
		m_defaultCamera = AddObject(new ansi::Object("Default Camera"));
		m_defaultCamera->GetTransform()->SetPositionZ(60.0f);

		auto camera = m_defaultCamera->AddComponent<ansi::Camera>();
		camera->GetOutput()->SetClearColor(glm::vec4(0.53f, 0.81f, 0.92f, 1.0f));

		/* === �⺻ ī�޶� �˵��� ��Ʈ�ѷ� === */
		m_defaultOrbitControls = new ansi::OrbitControls(camera);
		camera->SetOrbitControls(m_defaultOrbitControls);

		return true;
	}

	/* �� �����Ӹ��� ȣ��Ǵ� GUI ������ �Լ� */
	bool ExampleScene::OnRenderGui()
	{
		ImGui::NewLine();
		
		/* ��Ÿ ���� */
		ImGui::Text(">---------- Miscellaneous ----------<");

		/* [�ؽ�Ʈ] - �ʴ� �����Ӱ� ������ �� �ð� ���� ǥ�� */
		ImGui::Text("%.3f ms / %d FPS", 1000.0f / ImGui::GetIO().Framerate, static_cast<unsigned>(ImGui::GetIO().Framerate));

		/* [��ư] - ī�޶� ��ġ �ʱ�ȭ */
		if (ImGui::Button("Reset Camera")) { m_defaultOrbitControls->Reset(); }

		/* [��ư] - ��� ���� �޴��� ���ư��� */
		if (ImGui::Button("Back to menu")) { ansi::Core::GetWindow()->SetNextScene(new ExampleManager()); }

		ImGui::NewLine();

		return true;
	}

}
