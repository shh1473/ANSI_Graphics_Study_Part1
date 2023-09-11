#pragma once

#include <ansi_graphics_engine.h>

#include "../example_scene.h"

namespace example
{
	
	/* Hello World ��� Ŭ���� */
	class HelloWorldScene : public ExampleScene
	{
	public:
		/* ��� �̸� */
		static const std::string m_SceneName;

	public:
		/* ������ */
		explicit HelloWorldScene();

		/* �ʱ�ȭ �Լ� */
		bool Initialize() override;
		/* �� �����Ӹ��� ȣ��Ǵ� GUI ������ �Լ� */
		bool OnRenderGui() override;
		/* �ڿ��� �����ϴ� �Լ� */
		bool CreateResources() override;
		
	};

}
