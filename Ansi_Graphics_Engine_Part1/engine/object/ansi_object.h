	#pragma once

#include "common/ansi_common.h"

namespace ansi
{

	/* 전방 선언 */
	class Component;
	class Transform;

	/* 오브젝트 클래스 */
	class Object
	{
	public:
		/* 생성자
		* @param name - 이름
		*/
		explicit Object(const std::string & name);
		/* 소멸자 */
		virtual ~Object();

		/* 매 프레임마다 호출되는 업데이트 함수 */
		virtual bool OnUpdate();
		/* 매 프레임마다 호출되는 지연 업데이트 함수 */
		virtual bool OnLateUpdate();

		/* 매 프레임마다 호출되는 기본 업데이트 */
		bool OnDefaultUpdate();
		/* 매 프레임마다 호출되는 기본 지연 업데이트 */
		bool OnDefaultLateUpdate();

		/* 컴포넌트를 생성하고 추가하는 템플릿 함수
		* @param args - 소유자 오브젝트를 제외한 나머지 매개변수
		* @returns 생성된 컴포넌트
		*/
		template <typename T, typename ... Args>
		T * AddComponent(Args ... args)
		{
			return static_cast<T *>(m_components[typeid(T)] = new T(this, args ...));
		}
		/* 컴포넌트를 찾는 템플릿 함수
		* @returns 소유한 컴포넌트 (없을 경우 nullptr)
		*/
		template <typename T>
		T * FindComponent()
		{
			if (m_components.count(typeid(T)) == 0) { return nullptr; }
			return static_cast<T *>(m_components[typeid(T)]);
		}
		/* 자식 오브젝트를 추가하는 템플릿 함수
		* @param object - 추가할 자식 오브젝트
		* @returns 추가한 자식 오브젝트
		*/
		template <typename T>
		T * AddChild(T * object)
		{
			object->m_parent = this;
			return static_cast<T *>(m_children[object->GetName()] = object);
		}
		/* 자식 오브젝트를 찾는 템플릿 함수
		* @param name - 이름
		* @returns 소유한 자식 오브젝트
		*/
		template <typename T>
		T * FindChild(const std::string & name)
		{
			if (m_children.count(name) == 0) { return nullptr; }
			return static_cast<T *>(m_children[name]);
		}

		/* Setter - 활성화 여부 */
		void SetIsEnabled(bool isEnabled) { m_isEnabled = isEnabled; }
		/* Setter - 제거됨 여부 */
		void SetIsDeleted(bool isDeleted) { m_isDeleted = isDeleted; }

		/* Getter - 활성화 여부 */
		bool GetIsEnabled() const { return m_isEnabled; }
		/* Getter - 제거됨 여부 */
		bool GetIsDeleted() const { return m_isDeleted; }
		/* Getter - 이름 */
		const std::string & GetName() const { return m_name; }
		/* Getter - 자식 오브젝트 배열 */
		const std::unordered_map<std::string, Object *> & GetChildren() const { return m_children; }
		/* Getter - 컴포넌트 배열 */
		const std::unordered_map<std::type_index, Component *> & GetComponents() const { return m_components; }
		/* Getter - 부모 오브젝트 */
		Object * GetParent() const { return m_parent; }
		/* Getter - 트랜스폼 컴포넌트 */
		Transform * GetTransform() const { return m_transform; }

	private:
		/* 활성화 여부 */
		bool m_isEnabled;
		/* 제거됨 여부 */
		bool m_isDeleted;
		/* 이름 */
		std::string m_name;
		/* 자식 오브젝트 배열 */
		std::unordered_map<std::string, Object *> m_children;
		/* 컴포넌트 배열 */
		std::unordered_map<std::type_index, Component *> m_components;
		/* 부모 오브젝트 */
		Object * m_parent;
		/* 트랜스폼 컴포넌트 */
		Transform * m_transform;

	};

}
