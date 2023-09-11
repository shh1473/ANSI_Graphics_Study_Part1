#include "example_scene.h"

#include "../manager/example_manager.h"

namespace example
{

	/* 생성자 */
	ExampleScene::ExampleScene()
	{

	}

	bool ExampleScene::Initialize()
	{
		/* === 기본 카메라 오브젝트 === */
		m_defaultCamera = AddObject(new ansi::Object("Default Camera"));
		m_defaultCamera->GetTransform()->SetPositionZ(60.0f);

		auto camera = m_defaultCamera->AddComponent<ansi::Camera>();
		camera->GetOutput()->SetClearColor(glm::vec4(0.53f, 0.81f, 0.92f, 1.0f));

		/* === 기본 카메라 궤도형 컨트롤러 === */
		m_defaultOrbitControls = new ansi::OrbitControls(camera);
		camera->SetOrbitControls(m_defaultOrbitControls);

		return true;
	}

	/* 매 프레임마다 호출되는 GUI 렌더링 함수 */
	bool ExampleScene::OnRenderGui()
	{
		ImGui::NewLine();
		
		/* 기타 영역 */
		ImGui::Text(">---------- Miscellaneous ----------<");

		/* [텍스트] - 초당 프레임과 프레임 간 시간 간격 표시 */
		ImGui::Text("%.3f ms / %d FPS", 1000.0f / ImGui::GetIO().Framerate, static_cast<unsigned>(ImGui::GetIO().Framerate));

		/* [버튼] - 카메라 위치 초기화 */
		if (ImGui::Button("Reset Camera")) { m_defaultOrbitControls->Reset(); }

		/* [버튼] - 장면 선택 메뉴로 돌아가기 */
		if (ImGui::Button("Back to menu")) { ansi::Core::GetWindow()->SetNextScene(new ExampleManager()); }

		ImGui::NewLine();

		return true;
	}

}
