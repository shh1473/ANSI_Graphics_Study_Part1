#pragma once

#include "common/ansi_common.h"

namespace ansi
{

	/* 이벤트 수신기 클래스 */
	class EventListener
	{
	public:
		/* 생성자 */
		explicit EventListener();
		/* 소멸자 */
		virtual ~EventListener();

		/* 창 크기를 변경할 경우 호출되는 함수
		* @param size - 변경된 창 크기
		*/
		virtual void OnWindowResize(const glm::vec2 & size);
		/* 마우스 버튼을 누를 경우 호출되는 함수
		* @param button - 누른 마우스 버튼 (GLFW_MOUSE_BUTTON_LEFT, GLFW_MOUSE_BUTTON_RIGHT, GLFW_MOUSE_BUTTON_MIDDLE)
		* @param position - 누른 위치 (픽셀 단위)
		*/
		virtual void OnMouseDown(int button, const glm::vec2 & position);
		/* 마우스 버튼을 뗄 경우 호출되는 함수
		* @param button - 뗀 마우스 버튼 (GLFW_MOUSE_BUTTON_LEFT, GLFW_MOUSE_BUTTON_RIGHT, GLFW_MOUSE_BUTTON_MIDDLE)
		*/
		virtual void OnMouseUp(int button);
		/* 마우스를 움직일 경우 호출되는 함수
		* @param position - 마우스 위치 (픽셀 단위)
		*/
		virtual void OnMouseMove(const glm::vec2 & position);
		/* 마우스를 스크롤할 경우 호출되는 함수
		* @param deltaY - 스크롤한 마우스 휠의 틱 수
		*/
		virtual void OnMouseWheel(float deltaY);

	};

}
