#pragma once

#include "common/ansi_common.h"

namespace ansi
{

	/* ���� ���� */
	class Object;

	/* ������Ʈ Ŭ���� */
	class Component
	{
	public:
		/* ������
		* @param object - ������ ������Ʈ
		*/
		explicit Component(Object * object);
		/* �Ҹ��� */
		virtual ~Component();

		/* �� �����Ӹ��� ȣ��Ǵ� ������Ʈ �Լ� */
		virtual bool OnUpdate();
		/* �� �����Ӹ��� ȣ��Ǵ� ���� ������Ʈ �Լ� */
		virtual bool OnLateUpdate();

		/* Setter - Ȱ��ȭ ���� */
		void SetIsEnabled(bool isEnabled) { m_isEnabled = isEnabled; }

		/* Getter - Ȱ��ȭ ���� */
		bool GetIsEnabled() const { return m_isEnabled; }
		/* Getter - ������ ������Ʈ */
		Object * GetObject() const { return m_object; }

	private:
		/* Ȱ��ȭ ���� */
		bool m_isEnabled;
		/* ������ ������Ʈ */
		Object * const m_object;

	};

}