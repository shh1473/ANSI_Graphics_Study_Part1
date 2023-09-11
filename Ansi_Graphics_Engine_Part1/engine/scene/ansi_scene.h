#pragma once

#include "common/ansi_common.h"

namespace ansi
{

	/* 전방 선언 */
	class Object;
	class RenderExecutor;
	class ResourceStorage;

	/* 장면 클래스 */
	class Scene
	{
	public:
		/* 생성자 */
		explicit Scene();
		/* 소멸자 */
		virtual ~Scene();

		/* 초기화 함수 */
		virtual bool Initialize();
		/* 자원을 생성하는 함수 */
		virtual bool CreateResources();
		/* 매 프레임마다 호출되는 GUI 렌더링 함수 */
		virtual bool OnRenderGui();
		/* 매 프레임마다 호출되는 업데이트 함수 */
		virtual bool OnUpdate();
		/* 매 프레임마다 호출되는 지연 업데이트 함수 */
		virtual bool OnLateUpdate();

		/* 매 프레임마다 호출되는 기본 업데이트 함수 */
		bool OnDefaultUpdate();
		/* 매 프레임마다 호출되는 기본 지연 업데이트 함수 */
		bool OnDefaultLateUpdate();

		/* 오브젝트를 추가하는 템플릿 함수
		* @param object - 추가할 오브젝트
		* @returns 추가한 오브젝트
		*/
		template <typename T>
		T * AddObject(T * object)
		{
			return static_cast<T *>(m_objects[object->GetName()] = object);
		}
		/* 오브젝트를 찾는 템플릿 함수
		* @param name - 이름
		* @returns 소유한 오브젝트
		*/
		template <typename T>
		T * FindObject(const std::string & name)
		{
			if (m_objects.count(name) == 0) { return nullptr; }
			return static_cast<T *>(m_objects[name]);
		}

		/* Getter - 자원 저장소 */
		ResourceStorage * GetResources() const { return m_resourceStorage; }

	private:
		/* 자원 저장소 */
		ResourceStorage * m_resourceStorage;
		/* 오브젝트 테이블 */
		std::unordered_map<std::string, Object *> m_objects;

	};

}
