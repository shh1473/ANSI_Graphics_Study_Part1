#pragma once

#include "common/ansi_common.h"

namespace ansi
{

	/* 전방 선언 */
	class Object;

	/* 컴포넌트 클래스 */
	class Component
	{
	public:
		/* 생성자
		* @param object - 소유자 오브젝트
		*/
		explicit Component(Object * object);
		/* 소멸자 */
		virtual ~Component();

		/* 매 프레임마다 호출되는 업데이트 함수 */
		virtual bool OnUpdate();
		/* 매 프레임마다 호출되는 지연 업데이트 함수 */
		virtual bool OnLateUpdate();

		/* Setter - 활성화 여부 */
		void SetIsEnabled(bool isEnabled) { m_isEnabled = isEnabled; }

		/* Getter - 활성화 여부 */
		bool GetIsEnabled() const { return m_isEnabled; }
		/* Getter - 소유자 오브젝트 */
		Object * GetObject() const { return m_object; }

	private:
		/* 활성화 여부 */
		bool m_isEnabled;
		/* 소유자 오브젝트 */
		Object * const m_object;

	};

}