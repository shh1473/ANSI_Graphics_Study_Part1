#pragma once

#include <ansi_graphics_engine.h>

namespace example
{

	/* ���� ������ ��� Ŭ���� */
	class ExampleManager : public ansi::Scene
	{
	public:
		/* ������ */
		explicit ExampleManager();

		/* �ʱ�ȭ �Լ� */
		bool Initialize() override;
		/* �� �����Ӹ��� ȣ��Ǵ� ������Ʈ �Լ� */
		bool OnUpdate() override;
		/* �� �����Ӹ��� ȣ��Ǵ� GUI ������ �Լ� */
		bool OnRenderGui() override;

	private:
		/* ��ϵ� ���� ��� Ÿ�� */
		using ExampleSceneRegistry = std::pair<std::string, std::function<ansi::Scene * ()>>;

	private:
		/* ��ϵ� ���� ��� �迭 */
		std::vector<ExampleSceneRegistry> m_exampleScenes;

	};

}
