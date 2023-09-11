#pragma once

#include "core/ansi_core.h"

namespace ansi
{

	/* 전방 선언 */
	class Scene;
	class EventListener;

	/* 창 클래스 */
	class Window
	{
	public:
		/* 생성자 */
		explicit Window();
		/* 소멸자 */
		~Window();

		/* 초기화 함수 */
		bool Initialize();
		/* 프로그램 루프를 시작하는 함수 */
		bool Run();

		/* 이벤트 수신기를 등록하는 함수
		* @param listener - 등록할 이벤트 수신기
		*/
		void AddEventListener(EventListener * listener) { m_eventListeners.push_back(listener); }
		/* 이벤트 수신기를 등록 해제하는 함수
		* @param listener - 등록 해제할 이벤트 수신기
		*/
		void RemoveEventListener(EventListener * listener) { m_eventListeners.erase(std::remove(m_eventListeners.begin(), m_eventListeners.end(), listener), m_eventListeners.end()); }

		/* Setter - 창 크기 */
		void SetClientSize(float width, float height) { m_clientSize.x = width; m_clientSize.y = height; }
		/* Setter - 마우스 위치 */
		void SetMousePosition(float x, float y) { m_mousePosition.x = x; m_mousePosition.y = y; }
		/* Setter - 다음 장면 */
		void SetNextScene(Scene * nextScene) { m_nextScene = nextScene; }

		/* Getter - 창 크기 */
		const glm::vec2 & GetClientSize() const { return m_clientSize; }
		/* Getter - 마우스 위치 */
		const glm::vec2 & GetMousePosition() const { return m_mousePosition; }
		/* Getter - 이벤트 수신기 배열 */
		const std::vector<EventListener *> & GetEventListeners() const { return m_eventListeners; }

	private:
		/* 매 프레임마다 호출되는 기본 공통 GUI 렌더링 함수 */
		bool OnRenderGui();
		/* GUI로 선택한 창 설정을 적용하는 함수 */
		bool ApplyWindowSettings();
		/* 예약한 다음 장면을 현재 장면으로 변경하는 함수 */
		bool ApplyChangeScene();

	private:
		/* GLFW 초기화 여부 */
		bool m_isGlfwInitialized;
		/* 창 모드 활성화 여부 */
		bool m_isWindowed;
		/* 테두리 없는 창 모드 활성화 여부 */
		bool m_isBorderless;
		/* 창 크기 (픽셀 단위) */
		glm::vec2 m_clientSize;
		/* 마우스 위치 (픽셀 단위) */
		glm::vec2 m_mousePosition;
		/* GLFW 창 */
		GLFWwindow * m_window;
		/* 현재 장면 */
		Scene * m_currentScene;
		/* 다음 장면 */
		Scene * m_nextScene;
		/* 이벤트 수신기 배열 */
		std::vector<EventListener *> m_eventListeners;

	};

}
