#include "ansi_component.h"

#include "object/ansi_object.h"

namespace ansi
{

	/* ������ */
	Component::Component(Object * object)
		: m_isEnabled(true)
		, m_object(object)
	{

	}

	/* �Ҹ��� */
	Component::~Component()
	{

	}

	/* �� �����Ӹ��� ȣ��Ǵ� ������Ʈ �Լ� */
	bool Component::OnUpdate()
	{
		// ������� (�������̵� �ʿ�)
		return true;
	}

	/* �� �����Ӹ��� ȣ��Ǵ� ���� ������Ʈ �Լ� */
	bool Component::OnLateUpdate()
	{
		// ������� (�������̵� �ʿ�)
		return true;
	}

}