#include "ansi_object.h"

#include "object/component/transform/ansi_transform.h"

namespace ansi
{

	/* 생성자 */
	Object::Object(const std::string & name)
		: m_isEnabled(true)
		, m_isDeleted(false)
		, m_name(name)
		, m_children()
		, m_components()
		, m_parent(nullptr)
		, m_transform(AddComponent<Transform>())
	{

	}

	/* 소멸자 */
	Object::~Object()
	{
		for (auto iter = m_children.begin(); iter != m_children.end(); ++iter) { SAFE_DELETE(iter->second); }
		for (auto iter = m_components.begin(); iter != m_components.end(); ++iter) { SAFE_DELETE(iter->second); }
	}

	/* 매 프레임마다 호출되는 업데이트 함수 */
	bool Object::OnUpdate()
	{
		// 비어있음 (오버라이딩 필요)
		return true;
	}

	/* 매 프레임마다 호출되는 지연 업데이트 함수 */
	bool Object::OnLateUpdate()
	{
		// 비어있음 (오버라이딩 필요)
		return true;
	}

	/* 매 프레임마다 호출되는 기본 업데이트 */
	bool Object::OnDefaultUpdate()
	{
		/* 활성화된 모든 컴포넌트 업데이트 */
		for (const auto & iter : m_components)
		{
			if (iter.second->GetIsEnabled())
			{
				CHECK_RF(iter.second->OnUpdate());
			}
		}

		/* 활성화된 모든 자식 오브젝트 업데이트 */
		for (const auto & iter : m_children)
		{
			if (iter.second->GetIsEnabled())
			{
				/* 자신의 업데이트를 먼저 하고 */
				CHECK_RF(iter.second->OnUpdate());
				/* 자식 오브젝트의 업데이트 실행 */
				CHECK_RF(iter.second->OnDefaultUpdate());
			}
		}

		return true;
	}

	/* 매 프레임마다 호출되는 기본 지연 업데이트 */
	bool Object::OnDefaultLateUpdate()
	{
		/* 제거된 모든 자식 오브젝트 제거 */
		for (auto iter = m_children.begin(); iter != m_children.end();)
		{
			if (iter->second->GetIsDeleted())
			{
				SAFE_DELETE(iter->second);
				iter = m_children.erase(iter);
			}
			else { ++iter; }
		}

		/* 활성화된 모든 컴포넌트 지연 업데이트 */
		for (const auto & iter : m_components)
		{
			if (iter.second->GetIsEnabled())
			{
				CHECK_RF(iter.second->OnLateUpdate());
			}
		}

		/* 활성화된 모든 자식 오브젝트 지연 업데이트 */
		for (const auto & iter : m_children)
		{
			if (iter.second->GetIsEnabled())
			{
				/* 자신의 지연 업데이트를 먼저 하고 */
				CHECK_RF(iter.second->OnLateUpdate());
				/* 자식 오브젝트의 지연 업데이트 실행 */
				CHECK_RF(iter.second->OnDefaultLateUpdate());
			}
		}

		return true;
	}

}
