#pragma once

#include <ansi_graphics_engine.h>

namespace example
{

	/* 예제 관리자 장면 클래스 */
	class ExampleManager : public ansi::Scene
	{
	public:
		/* 생성자 */
		explicit ExampleManager();

		/* 초기화 함수 */
		bool Initialize() override;
		/* 매 프레임마다 호출되는 업데이트 함수 */
		bool OnUpdate() override;
		/* 매 프레임마다 호출되는 GUI 렌더링 함수 */
		bool OnRenderGui() override;

	private:
		/* 등록된 예제 장면 타입 */
		using ExampleSceneRegistry = std::pair<std::string, std::function<ansi::Scene * ()>>;

	private:
		/* 등록된 예제 장면 배열 */
		std::vector<ExampleSceneRegistry> m_exampleScenes;

	};

}
