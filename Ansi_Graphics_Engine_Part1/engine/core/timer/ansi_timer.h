#pragma once

#include "core/ansi_core.h"

/* ������ �� �ð� ���� (�� ����) */
#define DELTA_TIME ansi::Core::GetTimer()->GetDeltaTime()

namespace ansi
{

	/* Ÿ�̸� Ŭ���� */
	class Timer
	{
	public:
		/* ������ */
		explicit Timer();

		/* �� �����Ӹ��� ȣ��Ǵ� ������Ʈ �Լ� */
		void OnUpdate();

		/* Getter - ������ �� �ð� ���� (�� ����) */
		float GetDeltaTime() const { return m_deltaTime; }

	private:
		/* ������ �� �ð� ���� (�� ����) */
		float m_deltaTime;
		/* ���� ������ �ð� */
		std::chrono::steady_clock::time_point m_currentTime;
		/* ������ ������ �ð� */
		std::chrono::steady_clock::time_point m_previousTime;
		/* ������ �� �ð� ���� (������ ����) */
		std::chrono::nanoseconds m_elapsedTick;

	};

}
