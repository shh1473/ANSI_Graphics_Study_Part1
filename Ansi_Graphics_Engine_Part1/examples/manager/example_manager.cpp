#include "example_manager.h"

#include "../scene/00_hello_world_scene/hello_world_scene.h"
#include "../scene/01_color_scene/color_scene.h"
#include "../scene/02_texture_scene/texture_scene.h"
#include "../scene/03_hs_ambient_light_scene/hs_ambient_light_scene.h"
#include "../scene/04_directional_light_scene/directional_light_scene.h"
#include "../scene/05_cel_shading_scene/cel_shading_scene.h"
#include "../scene/06_normal_mapping_scene/normal_mapping_scene.h"
#include "../scene/07_shadow_scene/shadow_scene.h"
#include "../scene/08_final_scene/final_scene.h"

namespace example
{

	/* ������ */
	ExampleManager::ExampleManager()
		: m_exampleScenes()
	{

	}

	/* �ʱ�ȭ �Լ� */
	bool ExampleManager::Initialize()
	{
		ansi::Core::GetGui()->SetTitle("Example Manager");

		/* ���� ��� ��� (��� �̸��� ����� �����ϴ� �Լ� ��ü ����) */
		m_exampleScenes.push_back(std::make_pair(HelloWorldScene::m_SceneName, []() { return new HelloWorldScene(); }));
		m_exampleScenes.push_back(std::make_pair(ColorScene::m_SceneName, []() { return new ColorScene(); }));
		m_exampleScenes.push_back(std::make_pair(TextureScene::m_SceneName, []() { return new TextureScene(); }));
		m_exampleScenes.push_back(std::make_pair(HSAmbientLightScene::m_SceneName, []() { return new HSAmbientLightScene(); }));
		m_exampleScenes.push_back(std::make_pair(DirectionalLightScene::m_SceneName, []() { return new DirectionalLightScene(); }));
		m_exampleScenes.push_back(std::make_pair(CelShadingScene::m_SceneName, []() { return new CelShadingScene(); }));
		m_exampleScenes.push_back(std::make_pair(NormalMappingScene::m_SceneName, []() { return new NormalMappingScene(); }));
		m_exampleScenes.push_back(std::make_pair(ShadowScene::m_SceneName, []() { return new ShadowScene(); }));
		m_exampleScenes.push_back(std::make_pair(FinalScene::m_SceneName, []() { return new FinalScene(); }));

		/* �⺻ �����ӹ����� �ʱ�ȭ ���̿� �ʱ�ȭ ���� ���� (��鿡 ī�޶� ���� ������ �������� ȣ���ؾ� ��) */
		GL_CHECK(glClearDepth(1.0f));
		GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));

		return true;
	}

	/* �� �����Ӹ��� ȣ��Ǵ� ������Ʈ �Լ� */
	bool ExampleManager::OnUpdate()
	{
		/* �⺻ �����ӹ����� ���̿� ���� �ʱ�ȭ (��鿡 ī�޶� ���� ������ �������� ȣ���ؾ� ��) */
		GL_CHECK(glClear(GL_DEPTH_BUFFER_BIT));
		GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

		return true;
	}

	/* �� �����Ӹ��� ȣ��Ǵ� GUI ������ �Լ� */
	bool ExampleManager::OnRenderGui()
	{
		ImGui::Text(">---------- Example List -----------<");

		/* �� ���� ���� �ϳ��� ��ư�� ����� ���� �� ����� ������ �� �ֵ��� �� */
		for (unsigned i{ 0 }; i < m_exampleScenes.size(); ++i)
		{
			if (ImGui::Button(m_exampleScenes[i].first.c_str()))
			{
				/* ��ư�� ���� �� ���� GUI â�� Ÿ��Ʋ ���� */
				ansi::Core::GetWindow()->SetNextScene(m_exampleScenes[i].second());
				ansi::Core::GetGui()->SetTitle(m_exampleScenes[i].first);
			}
		}

		ImGui::NewLine();

		return true;
	}

}
