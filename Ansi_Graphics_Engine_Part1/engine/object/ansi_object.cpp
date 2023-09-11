#include "ansi_object.h"

#include "object/component/transform/ansi_transform.h"

namespace ansi
{

	/* ������ */
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

	/* �Ҹ��� */
	Object::~Object()
	{
		for (auto iter = m_children.begin(); iter != m_children.end(); ++iter) { SAFE_DELETE(iter->second); }
		for (auto iter = m_components.begin(); iter != m_components.end(); ++iter) { SAFE_DELETE(iter->second); }
	}

	/* �� �����Ӹ��� ȣ��Ǵ� ������Ʈ �Լ� */
	bool Object::OnUpdate()
	{
		// ������� (�������̵� �ʿ�)
		return true;
	}

	/* �� �����Ӹ��� ȣ��Ǵ� ���� ������Ʈ �Լ� */
	bool Object::OnLateUpdate()
	{
		// ������� (�������̵� �ʿ�)
		return true;
	}

	/* �� �����Ӹ��� ȣ��Ǵ� �⺻ ������Ʈ */
	bool Object::OnDefaultUpdate()
	{
		/* Ȱ��ȭ�� ��� ������Ʈ ������Ʈ */
		for (const auto & iter : m_components)
		{
			if (iter.second->GetIsEnabled())
			{
				CHECK_RF(iter.second->OnUpdate());
			}
		}

		/* Ȱ��ȭ�� ��� �ڽ� ������Ʈ ������Ʈ */
		for (const auto & iter : m_children)
		{
			if (iter.second->GetIsEnabled())
			{
				/* �ڽ��� ������Ʈ�� ���� �ϰ� */
				CHECK_RF(iter.second->OnUpdate());
				/* �ڽ� ������Ʈ�� ������Ʈ ���� */
				CHECK_RF(iter.second->OnDefaultUpdate());
			}
		}

		return true;
	}

	/* �� �����Ӹ��� ȣ��Ǵ� �⺻ ���� ������Ʈ */
	bool Object::OnDefaultLateUpdate()
	{
		/* ���ŵ� ��� �ڽ� ������Ʈ ���� */
		for (auto iter = m_children.begin(); iter != m_children.end();)
		{
			if (iter->second->GetIsDeleted())
			{
				SAFE_DELETE(iter->second);
				iter = m_children.erase(iter);
			}
			else { ++iter; }
		}

		/* Ȱ��ȭ�� ��� ������Ʈ ���� ������Ʈ */
		for (const auto & iter : m_components)
		{
			if (iter.second->GetIsEnabled())
			{
				CHECK_RF(iter.second->OnLateUpdate());
			}
		}

		/* Ȱ��ȭ�� ��� �ڽ� ������Ʈ ���� ������Ʈ */
		for (const auto & iter : m_children)
		{
			if (iter.second->GetIsEnabled())
			{
				/* �ڽ��� ���� ������Ʈ�� ���� �ϰ� */
				CHECK_RF(iter.second->OnLateUpdate());
				/* �ڽ� ������Ʈ�� ���� ������Ʈ ���� */
				CHECK_RF(iter.second->OnDefaultLateUpdate());
			}
		}

		return true;
	}

}
