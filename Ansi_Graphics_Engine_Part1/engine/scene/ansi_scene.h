#pragma once

#include "common/ansi_common.h"

namespace ansi
{

	/* ���� ���� */
	class Object;
	class RenderExecutor;
	class ResourceStorage;

	/* ��� Ŭ���� */
	class Scene
	{
	public:
		/* ������ */
		explicit Scene();
		/* �Ҹ��� */
		virtual ~Scene();

		/* �ʱ�ȭ �Լ� */
		virtual bool Initialize();
		/* �ڿ��� �����ϴ� �Լ� */
		virtual bool CreateResources();
		/* �� �����Ӹ��� ȣ��Ǵ� GUI ������ �Լ� */
		virtual bool OnRenderGui();
		/* �� �����Ӹ��� ȣ��Ǵ� ������Ʈ �Լ� */
		virtual bool OnUpdate();
		/* �� �����Ӹ��� ȣ��Ǵ� ���� ������Ʈ �Լ� */
		virtual bool OnLateUpdate();

		/* �� �����Ӹ��� ȣ��Ǵ� �⺻ ������Ʈ �Լ� */
		bool OnDefaultUpdate();
		/* �� �����Ӹ��� ȣ��Ǵ� �⺻ ���� ������Ʈ �Լ� */
		bool OnDefaultLateUpdate();

		/* ������Ʈ�� �߰��ϴ� ���ø� �Լ�
		* @param object - �߰��� ������Ʈ
		* @returns �߰��� ������Ʈ
		*/
		template <typename T>
		T * AddObject(T * object)
		{
			return static_cast<T *>(m_objects[object->GetName()] = object);
		}
		/* ������Ʈ�� ã�� ���ø� �Լ�
		* @param name - �̸�
		* @returns ������ ������Ʈ
		*/
		template <typename T>
		T * FindObject(const std::string & name)
		{
			if (m_objects.count(name) == 0) { return nullptr; }
			return static_cast<T *>(m_objects[name]);
		}

		/* Getter - �ڿ� ����� */
		ResourceStorage * GetResources() const { return m_resourceStorage; }

	private:
		/* �ڿ� ����� */
		ResourceStorage * m_resourceStorage;
		/* ������Ʈ ���̺� */
		std::unordered_map<std::string, Object *> m_objects;

	};

}
