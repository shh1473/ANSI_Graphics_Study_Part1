#include "ansi_timer.h"

namespace ansi
{

	/* ������ */
	Timer::Timer()
		: m_deltaTime(0.0f)
		, m_currentTime(std::chrono::high_resolution_clock::now())
		, m_previousTime(std::chrono::high_resolution_clock::now())
		, m_elapsedTick(0)
	{

	}

	/* �� �����Ӹ��� ȣ��Ǵ� ������Ʈ �Լ� */
	void Timer::OnUpdate()
	{
		/* ���� �ð� ���� */
		m_currentTime = std::chrono::high_resolution_clock::now();
		/* ������ ������ �ð����� ���� ��� */
		m_elapsedTick = m_currentTime - m_previousTime;
		/* ������ ������ �ð��� ����� ���� ����� */
		m_previousTime = m_currentTime;
		/* �ð� ������ �����ʿ��� �� ������ ��ȯ */
		m_deltaTime = m_elapsedTick.count() / 1000000000.0f;
	}

}
