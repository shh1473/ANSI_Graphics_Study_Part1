#include "ansi_event_listener.h"

#include "core/window/ansi_window.h"

namespace ansi
{

	/* 생성자 */
	EventListener::EventListener()
	{
		/* 창 관리자에 등록 */
		Core::GetWindow()->AddEventListener(this);
	}

	/* 소멸자 */
	EventListener::~EventListener()
	{
		/* 창 관리자에서 등록 해제 */
		Core::GetWindow()->RemoveEventListener(this);
	}

	/* 창 크기를 변경할 경우 호출되는 함수 */
	void EventListener::OnWindowResize(const glm::vec2 & size)
	{
		// 비어있음 (오버라이딩 필요)
	}

	/* 마우스 버튼을 누를 경우 호출되는 함수 */
	void EventListener::OnMouseDown(int button, const glm::vec2 & position)
	{
		// 비어있음 (오버라이딩 필요)
	}

	/* 마우스 버튼을 뗄 경우 호출되는 함수 */
	void EventListener::OnMouseUp(int button)
	{
		// 비어있음 (오버라이딩 필요)
	}

	/* 마우스를 움직일 경우 호출되는 함수 */
	void EventListener::OnMouseMove(const glm::vec2 & position)
	{
		// 비어있음 (오버라이딩 필요)
	}

	/* 마우스를 스크롤할 경우 호출되는 함수 */
	void EventListener::OnMouseWheel(float deltaY)
	{
		// 비어있음 (오버라이딩 필요)
	}

}
