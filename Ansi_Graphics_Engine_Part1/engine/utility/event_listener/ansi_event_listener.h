#pragma once

#include "common/ansi_common.h"

namespace ansi
{

	/* �̺�Ʈ ���ű� Ŭ���� */
	class EventListener
	{
	public:
		/* ������ */
		explicit EventListener();
		/* �Ҹ��� */
		virtual ~EventListener();

		/* â ũ�⸦ ������ ��� ȣ��Ǵ� �Լ�
		* @param size - ����� â ũ��
		*/
		virtual void OnWindowResize(const glm::vec2 & size);
		/* ���콺 ��ư�� ���� ��� ȣ��Ǵ� �Լ�
		* @param button - ���� ���콺 ��ư (GLFW_MOUSE_BUTTON_LEFT, GLFW_MOUSE_BUTTON_RIGHT, GLFW_MOUSE_BUTTON_MIDDLE)
		* @param position - ���� ��ġ (�ȼ� ����)
		*/
		virtual void OnMouseDown(int button, const glm::vec2 & position);
		/* ���콺 ��ư�� �� ��� ȣ��Ǵ� �Լ�
		* @param button - �� ���콺 ��ư (GLFW_MOUSE_BUTTON_LEFT, GLFW_MOUSE_BUTTON_RIGHT, GLFW_MOUSE_BUTTON_MIDDLE)
		*/
		virtual void OnMouseUp(int button);
		/* ���콺�� ������ ��� ȣ��Ǵ� �Լ�
		* @param position - ���콺 ��ġ (�ȼ� ����)
		*/
		virtual void OnMouseMove(const glm::vec2 & position);
		/* ���콺�� ��ũ���� ��� ȣ��Ǵ� �Լ�
		* @param deltaY - ��ũ���� ���콺 ���� ƽ ��
		*/
		virtual void OnMouseWheel(float deltaY);

	};

}
