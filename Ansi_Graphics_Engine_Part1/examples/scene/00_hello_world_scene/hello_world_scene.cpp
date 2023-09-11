#include "hello_world_scene.h"

namespace example
{

	/* 장면 이름 초기화 */
	const std::string HelloWorldScene::m_SceneName{ "00 - Hello World" };

	/* 생성자 */
	HelloWorldScene::HelloWorldScene()
	{

	}

	/* 초기화 함수 */
	bool HelloWorldScene::Initialize()
	{
		return ExampleScene::Initialize();
	}

	/* 매 프레임마다 호출되는 GUI 렌더링 함수 */
	bool HelloWorldScene::OnRenderGui()
	{
		ImGui::Text(">--------- Render Settings ---------<");

		/* Hello World 출력 */
		ImGui::Text("Hello World!");

		return ExampleScene::OnRenderGui();
	}

	bool HelloWorldScene::CreateResources()
	{
		return true;
	}

}
