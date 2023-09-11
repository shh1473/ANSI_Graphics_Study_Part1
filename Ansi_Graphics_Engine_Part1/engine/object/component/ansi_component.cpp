#include "ansi_component.h"

#include "object/ansi_object.h"

namespace ansi
{

	/* 생성자 */
	Component::Component(Object * object)
		: m_isEnabled(true)
		, m_object(object)
	{

	}

	/* 소멸자 */
	Component::~Component()
	{

	}

	/* 매 프레임마다 호출되는 업데이트 함수 */
	bool Component::OnUpdate()
	{
		// 비어있음 (오버라이딩 필요)
		return true;
	}

	/* 매 프레임마다 호출되는 지연 업데이트 함수 */
	bool Component::OnLateUpdate()
	{
		// 비어있음 (오버라이딩 필요)
		return true;
	}

}