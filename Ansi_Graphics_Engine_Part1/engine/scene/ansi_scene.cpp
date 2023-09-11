#include "scene/ansi_scene.h"

#include "scene/resource_storage/ansi_resource_storage.h"
#include "object/ansi_object.h"

namespace ansi
{

	/* ������ */
	Scene::Scene()
		: m_resourceStorage(new ResourceStorage())
		, m_objects()
	{

	}

	/* �Ҹ��� */
	Scene::~Scene()
	{
		for (auto iter = m_objects.begin(); iter != m_objects.end(); ++iter) { SAFE_DELETE(iter->second); }
		SAFE_DELETE(m_resourceStorage);
	}

	/* �ʱ�ȭ �Լ� */
	bool Scene::Initialize()
	{
		// ������� (�������̵� �ʿ�)
		return true;
	}

	/* �ڿ��� �����ϴ� �Լ� */
	bool Scene::CreateResources()
	{
		// ������� (�������̵� �ʿ�)
		return true;
	}

	/* �� �����Ӹ��� ȣ��Ǵ� GUI ������ �Լ� */
	bool Scene::OnRenderGui()
	{
		// ������� (�������̵� �ʿ�)
		return true;
	}

	/* �� �����Ӹ��� ȣ��Ǵ� ������Ʈ �Լ� */
	bool Scene::OnUpdate()
	{
		// ������� (�������̵� �ʿ�)
		return true;
	}

	/* �� �����Ӹ��� ȣ��Ǵ� ���� ������Ʈ �Լ� */
	bool Scene::OnLateUpdate()
	{
		// ������� (�������̵� �ʿ�)
		return true;
	}

	/* �� �����Ӹ��� ȣ��Ǵ� �⺻ ������Ʈ �Լ� */
	bool Scene::OnDefaultUpdate()
	{
		/* Ȱ��ȭ�� ��� ������Ʈ ������Ʈ */
		for (const auto & iter : m_objects)
		{
			/* �ڽ��� ������Ʈ�� ���� �ϰ� */
			CHECK_RF(iter.second->OnUpdate());
			/* ������Ʈ�� ������Ʈ ���� */
			CHECK_RF(iter.second->OnDefaultUpdate());
		}

		return true;
	}

	/* �� �����Ӹ��� ȣ��Ǵ� �⺻ ���� ������Ʈ �Լ� */
	bool Scene::OnDefaultLateUpdate()
	{
		/* ���ŵ� ��� ������Ʈ ���� */
		for (auto iter = m_objects.begin(); iter != m_objects.end();)
		{
			if (iter->second->GetIsDeleted())
			{
				CHECK_RF(iter->second);
				m_objects.erase(iter);
			}
			else { ++iter; }
		}

		/* Ȱ��ȭ�� ��� ������Ʈ ���� ������Ʈ */
		for (const auto & iter : m_objects)
		{
			/* �ڽ��� ���� ������Ʈ�� ���� �ϰ� */
			CHECK_RF(iter.second->OnLateUpdate());
			/* ������Ʈ�� ���� ������Ʈ ���� */
			CHECK_RF(iter.second->OnDefaultLateUpdate());
		}

		return true;
	}

}
