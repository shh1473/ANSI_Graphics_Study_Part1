#include "ansi_timer.h"

namespace ansi
{

	/* 생성자 */
	Timer::Timer()
		: m_deltaTime(0.0f)
		, m_currentTime(std::chrono::high_resolution_clock::now())
		, m_previousTime(std::chrono::high_resolution_clock::now())
		, m_elapsedTick(0)
	{

	}

	/* 매 프레임마다 호출되는 업데이트 함수 */
	void Timer::OnUpdate()
	{
		/* 현재 시간 측정 */
		m_currentTime = std::chrono::high_resolution_clock::now();
		/* 이전에 측정한 시간과의 간격 계산 */
		m_elapsedTick = m_currentTime - m_previousTime;
		/* 이전에 측정한 시간을 현재로 덮어 씌우기 */
		m_previousTime = m_currentTime;
		/* 시간 간격을 나노초에서 초 단위로 변환 */
		m_deltaTime = m_elapsedTick.count() / 1000000000.0f;
	}

}
