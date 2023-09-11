#pragma once

#include <ansi_graphics_engine.h>

#include "../example_scene.h"

namespace example
{
	
	/* Hello World 장면 클래스 */
	class HelloWorldScene : public ExampleScene
	{
	public:
		/* 장면 이름 */
		static const std::string m_SceneName;

	public:
		/* 생성자 */
		explicit HelloWorldScene();

		/* 초기화 함수 */
		bool Initialize() override;
		/* 매 프레임마다 호출되는 GUI 렌더링 함수 */
		bool OnRenderGui() override;
		/* 자원을 생성하는 함수 */
		bool CreateResources() override;
		
	};

}
