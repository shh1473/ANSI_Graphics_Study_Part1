	#pragma once

#include "common/ansi_common.h"

namespace ansi
{

	/* ���� ���� */
	class Component;
	class Transform;

	/* ������Ʈ Ŭ���� */
	class Object
	{
	public:
		/* ������
		* @param name - �̸�
		*/
		explicit Object(const std::string & name);
		/* �Ҹ��� */
		virtual ~Object();

		/* �� �����Ӹ��� ȣ��Ǵ� ������Ʈ �Լ� */
		virtual bool OnUpdate();
		/* �� �����Ӹ��� ȣ��Ǵ� ���� ������Ʈ �Լ� */
		virtual bool OnLateUpdate();

		/* �� �����Ӹ��� ȣ��Ǵ� �⺻ ������Ʈ */
		bool OnDefaultUpdate();
		/* �� �����Ӹ��� ȣ��Ǵ� �⺻ ���� ������Ʈ */
		bool OnDefaultLateUpdate();

		/* ������Ʈ�� �����ϰ� �߰��ϴ� ���ø� �Լ�
		* @param args - ������ ������Ʈ�� ������ ������ �Ű�����
		* @returns ������ ������Ʈ
		*/
		template <typename T, typename ... Args>
		T * AddComponent(Args ... args)
		{
			return static_cast<T *>(m_components[typeid(T)] = new T(this, args ...));
		}
		/* ������Ʈ�� ã�� ���ø� �Լ�
		* @returns ������ ������Ʈ (���� ��� nullptr)
		*/
		template <typename T>
		T * FindComponent()
		{
			if (m_components.count(typeid(T)) == 0) { return nullptr; }
			return static_cast<T *>(m_components[typeid(T)]);
		}
		/* �ڽ� ������Ʈ�� �߰��ϴ� ���ø� �Լ�
		* @param object - �߰��� �ڽ� ������Ʈ
		* @returns �߰��� �ڽ� ������Ʈ
		*/
		template <typename T>
		T * AddChild(T * object)
		{
			object->m_parent = this;
			return static_cast<T *>(m_children[object->GetName()] = object);
		}
		/* �ڽ� ������Ʈ�� ã�� ���ø� �Լ�
		* @param name - �̸�
		* @returns ������ �ڽ� ������Ʈ
		*/
		template <typename T>
		T * FindChild(const std::string & name)
		{
			if (m_children.count(name) == 0) { return nullptr; }
			return static_cast<T *>(m_children[name]);
		}

		/* Setter - Ȱ��ȭ ���� */
		void SetIsEnabled(bool isEnabled) { m_isEnabled = isEnabled; }
		/* Setter - ���ŵ� ���� */
		void SetIsDeleted(bool isDeleted) { m_isDeleted = isDeleted; }

		/* Getter - Ȱ��ȭ ���� */
		bool GetIsEnabled() const { return m_isEnabled; }
		/* Getter - ���ŵ� ���� */
		bool GetIsDeleted() const { return m_isDeleted; }
		/* Getter - �̸� */
		const std::string & GetName() const { return m_name; }
		/* Getter - �ڽ� ������Ʈ �迭 */
		const std::unordered_map<std::string, Object *> & GetChildren() const { return m_children; }
		/* Getter - ������Ʈ �迭 */
		const std::unordered_map<std::type_index, Component *> & GetComponents() const { return m_components; }
		/* Getter - �θ� ������Ʈ */
		Object * GetParent() const { return m_parent; }
		/* Getter - Ʈ������ ������Ʈ */
		Transform * GetTransform() const { return m_transform; }

	private:
		/* Ȱ��ȭ ���� */
		bool m_isEnabled;
		/* ���ŵ� ���� */
		bool m_isDeleted;
		/* �̸� */
		std::string m_name;
		/* �ڽ� ������Ʈ �迭 */
		std::unordered_map<std::string, Object *> m_children;
		/* ������Ʈ �迭 */
		std::unordered_map<std::type_index, Component *> m_components;
		/* �θ� ������Ʈ */
		Object * m_parent;
		/* Ʈ������ ������Ʈ */
		Transform * m_transform;

	};

}
