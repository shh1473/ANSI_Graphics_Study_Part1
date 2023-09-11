#pragma once

#include "core/ansi_core.h"

/* 프레임 간 시간 간격 (초 단위) */
#define DELTA_TIME ansi::Core::GetTimer()->GetDeltaTime()

namespace ansi
{

	/* 타이머 클래스 */
	class Timer
	{
	public:
		/* 생성자 */
		explicit Timer();

		/* 매 프레임마다 호출되는 업데이트 함수 */
		void OnUpdate();

		/* Getter - 프레임 간 시간 간격 (초 단위) */
		float GetDeltaTime() const { return m_deltaTime; }

	private:
		/* 프레임 간 시간 간격 (초 단위) */
		float m_deltaTime;
		/* 현재 측정된 시간 */
		std::chrono::steady_clock::time_point m_currentTime;
		/* 이전에 측정된 시간 */
		std::chrono::steady_clock::time_point m_previousTime;
		/* 프레임 간 시간 간격 (나노초 단위) */
		std::chrono::nanoseconds m_elapsedTick;

	};

}
