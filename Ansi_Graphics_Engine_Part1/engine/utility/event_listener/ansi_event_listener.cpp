#include "ansi_event_listener.h"

#include "core/window/ansi_window.h"

namespace ansi
{

	/* ������ */
	EventListener::EventListener()
	{
		/* â �����ڿ� ��� */
		Core::GetWindow()->AddEventListener(this);
	}

	/* �Ҹ��� */
	EventListener::~EventListener()
	{
		/* â �����ڿ��� ��� ���� */
		Core::GetWindow()->RemoveEventListener(this);
	}

	/* â ũ�⸦ ������ ��� ȣ��Ǵ� �Լ� */
	void EventListener::OnWindowResize(const glm::vec2 & size)
	{
		// ������� (�������̵� �ʿ�)
	}

	/* ���콺 ��ư�� ���� ��� ȣ��Ǵ� �Լ� */
	void EventListener::OnMouseDown(int button, const glm::vec2 & position)
	{
		// ������� (�������̵� �ʿ�)
	}

	/* ���콺 ��ư�� �� ��� ȣ��Ǵ� �Լ� */
	void EventListener::OnMouseUp(int button)
	{
		// ������� (�������̵� �ʿ�)
	}

	/* ���콺�� ������ ��� ȣ��Ǵ� �Լ� */
	void EventListener::OnMouseMove(const glm::vec2 & position)
	{
		// ������� (�������̵� �ʿ�)
	}

	/* ���콺�� ��ũ���� ��� ȣ��Ǵ� �Լ� */
	void EventListener::OnMouseWheel(float deltaY)
	{
		// ������� (�������̵� �ʿ�)
	}

}
