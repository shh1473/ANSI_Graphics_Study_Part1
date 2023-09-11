#pragma once

#include <ansi_graphics_engine.h>

namespace example
{

	/* 예제 장면 클래스 */
	class ExampleScene : public ansi::Scene
	{
	public:
		/* 생성자 */
		explicit ExampleScene();

		/* 초기화 함수 */
		bool Initialize() override;
		/* 매 프레임마다 호출되는 GUI 렌더링 함수 */
		bool OnRenderGui() override;

	protected:
		/* 기본 카메라 */
		ansi::Object * m_defaultCamera{ nullptr };
		/* 기본 카메라 궤도형 컨트롤러 */
		ansi::OrbitControls * m_defaultOrbitControls{ nullptr };

	};

}
