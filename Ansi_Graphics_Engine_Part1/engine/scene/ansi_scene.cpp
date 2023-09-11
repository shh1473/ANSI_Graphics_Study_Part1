#include "scene/ansi_scene.h"

#include "scene/resource_storage/ansi_resource_storage.h"
#include "object/ansi_object.h"

namespace ansi
{

	/* 생성자 */
	Scene::Scene()
		: m_resourceStorage(new ResourceStorage())
		, m_objects()
	{

	}

	/* 소멸자 */
	Scene::~Scene()
	{
		for (auto iter = m_objects.begin(); iter != m_objects.end(); ++iter) { SAFE_DELETE(iter->second); }
		SAFE_DELETE(m_resourceStorage);
	}

	/* 초기화 함수 */
	bool Scene::Initialize()
	{
		// 비어있음 (오버라이딩 필요)
		return true;
	}

	/* 자원을 생성하는 함수 */
	bool Scene::CreateResources()
	{
		// 비어있음 (오버라이딩 필요)
		return true;
	}

	/* 매 프레임마다 호출되는 GUI 렌더링 함수 */
	bool Scene::OnRenderGui()
	{
		// 비어있음 (오버라이딩 필요)
		return true;
	}

	/* 매 프레임마다 호출되는 업데이트 함수 */
	bool Scene::OnUpdate()
	{
		// 비어있음 (오버라이딩 필요)
		return true;
	}

	/* 매 프레임마다 호출되는 지연 업데이트 함수 */
	bool Scene::OnLateUpdate()
	{
		// 비어있음 (오버라이딩 필요)
		return true;
	}

	/* 매 프레임마다 호출되는 기본 업데이트 함수 */
	bool Scene::OnDefaultUpdate()
	{
		/* 활성화된 모든 오브젝트 업데이트 */
		for (const auto & iter : m_objects)
		{
			/* 자신의 업데이트를 먼저 하고 */
			CHECK_RF(iter.second->OnUpdate());
			/* 오브젝트의 업데이트 실행 */
			CHECK_RF(iter.second->OnDefaultUpdate());
		}

		return true;
	}

	/* 매 프레임마다 호출되는 기본 지연 업데이트 함수 */
	bool Scene::OnDefaultLateUpdate()
	{
		/* 제거된 모든 오브젝트 제거 */
		for (auto iter = m_objects.begin(); iter != m_objects.end();)
		{
			if (iter->second->GetIsDeleted())
			{
				CHECK_RF(iter->second);
				m_objects.erase(iter);
			}
			else { ++iter; }
		}

		/* 활성화된 모든 오브젝트 지연 업데이트 */
		for (const auto & iter : m_objects)
		{
			/* 자신의 지연 업데이트를 먼저 하고 */
			CHECK_RF(iter.second->OnLateUpdate());
			/* 오브젝트의 지연 업데이트 실행 */
			CHECK_RF(iter.second->OnDefaultLateUpdate());
		}

		return true;
	}

}
