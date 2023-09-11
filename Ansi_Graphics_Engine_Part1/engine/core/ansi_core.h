#pragma once

#include "common/ansi_common.h"

namespace ansi
{

	/* 전방 선언 */
	class Timer;
	class Window;
	class Render;
	class Gui;

	/* 프로그램 핵심 클래스 */
	class Core
	{
	public:
		/* 싱글턴 인스턴스를 생성하는 함수 */
		static bool CreateInstance();
		/* 싱글턴 인스턴스를 제거하는 함수 */
		static void DeleteInstance();

		/* Getter - 싱글턴 인스턴스 */
		static Core * GetInstance() { return m_Instance; }
		/* Getter - 타이머 */
		static Timer * GetTimer() { return m_Instance->m_timer; }
		/* Getter - 창 */
		static Window * GetWindow() { return m_Instance->m_window; }
		/* Getter - 렌더 */
		static Render * GetRender() { return m_Instance->m_render; }
		/* Getter - GUI */
		static Gui * GetGui() { return m_Instance->m_gui; }

	private:
		/* 생성자 */
		explicit Core();
		/* 소멸자 */
		~Core();

		/* 초기화 함수 */
		bool Initialize();

	private:
		/* 싱글턴 인스턴스 */
		static Core * m_Instance;
		
		/* 타이머 */
		Timer * m_timer;
		/* 창 */
		Window * m_window;
		/* 렌더 */
		Render * m_render;
		/* GUI */
		Gui * m_gui;

	};

}
