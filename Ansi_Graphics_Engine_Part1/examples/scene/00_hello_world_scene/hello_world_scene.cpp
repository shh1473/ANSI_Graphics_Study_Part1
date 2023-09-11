#include "hello_world_scene.h"

namespace example
{

	/* ��� �̸� �ʱ�ȭ */
	const std::string HelloWorldScene::m_SceneName{ "00 - Hello World" };

	/* ������ */
	HelloWorldScene::HelloWorldScene()
	{

	}

	/* �ʱ�ȭ �Լ� */
	bool HelloWorldScene::Initialize()
	{
		return ExampleScene::Initialize();
	}

	/* �� �����Ӹ��� ȣ��Ǵ� GUI ������ �Լ� */
	bool HelloWorldScene::OnRenderGui()
	{
		ImGui::Text(">--------- Render Settings ---------<");

		/* Hello World ��� */
		ImGui::Text("Hello World!");

		return ExampleScene::OnRenderGui();
	}

	bool HelloWorldScene::CreateResources()
	{
		return true;
	}

}
