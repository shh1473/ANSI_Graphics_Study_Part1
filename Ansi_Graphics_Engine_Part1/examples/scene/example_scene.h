#pragma once

#include <ansi_graphics_engine.h>

namespace example
{

	/* ���� ��� Ŭ���� */
	class ExampleScene : public ansi::Scene
	{
	public:
		/* ������ */
		explicit ExampleScene();

		/* �ʱ�ȭ �Լ� */
		bool Initialize() override;
		/* �� �����Ӹ��� ȣ��Ǵ� GUI ������ �Լ� */
		bool OnRenderGui() override;

	protected:
		/* �⺻ ī�޶� */
		ansi::Object * m_defaultCamera{ nullptr };
		/* �⺻ ī�޶� �˵��� ��Ʈ�ѷ� */
		ansi::OrbitControls * m_defaultOrbitControls{ nullptr };

	};

}
