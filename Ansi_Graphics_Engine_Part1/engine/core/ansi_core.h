#pragma once

#include "common/ansi_common.h"

namespace ansi
{

	/* ���� ���� */
	class Timer;
	class Window;
	class Render;
	class Gui;

	/* ���α׷� �ٽ� Ŭ���� */
	class Core
	{
	public:
		/* �̱��� �ν��Ͻ��� �����ϴ� �Լ� */
		static bool CreateInstance();
		/* �̱��� �ν��Ͻ��� �����ϴ� �Լ� */
		static void DeleteInstance();

		/* Getter - �̱��� �ν��Ͻ� */
		static Core * GetInstance() { return m_Instance; }
		/* Getter - Ÿ�̸� */
		static Timer * GetTimer() { return m_Instance->m_timer; }
		/* Getter - â */
		static Window * GetWindow() { return m_Instance->m_window; }
		/* Getter - ���� */
		static Render * GetRender() { return m_Instance->m_render; }
		/* Getter - GUI */
		static Gui * GetGui() { return m_Instance->m_gui; }

	private:
		/* ������ */
		explicit Core();
		/* �Ҹ��� */
		~Core();

		/* �ʱ�ȭ �Լ� */
		bool Initialize();

	private:
		/* �̱��� �ν��Ͻ� */
		static Core * m_Instance;
		
		/* Ÿ�̸� */
		Timer * m_timer;
		/* â */
		Window * m_window;
		/* ���� */
		Render * m_render;
		/* GUI */
		Gui * m_gui;

	};

}
