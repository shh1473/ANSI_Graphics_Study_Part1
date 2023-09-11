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

	/* 생성자 */
	ExampleManager::ExampleManager()
		: m_exampleScenes()
	{

	}

	/* 초기화 함수 */
	bool ExampleManager::Initialize()
	{
		ansi::Core::GetGui()->SetTitle("Example Manager");

		/* 예제 장면 등록 (장면 이름과 장면을 생성하는 함수 객체 생성) */
		m_exampleScenes.push_back(std::make_pair(HelloWorldScene::m_SceneName, []() { return new HelloWorldScene(); }));
		m_exampleScenes.push_back(std::make_pair(ColorScene::m_SceneName, []() { return new ColorScene(); }));
		m_exampleScenes.push_back(std::make_pair(TextureScene::m_SceneName, []() { return new TextureScene(); }));
		m_exampleScenes.push_back(std::make_pair(HSAmbientLightScene::m_SceneName, []() { return new HSAmbientLightScene(); }));
		m_exampleScenes.push_back(std::make_pair(DirectionalLightScene::m_SceneName, []() { return new DirectionalLightScene(); }));
		m_exampleScenes.push_back(std::make_pair(CelShadingScene::m_SceneName, []() { return new CelShadingScene(); }));
		m_exampleScenes.push_back(std::make_pair(NormalMappingScene::m_SceneName, []() { return new NormalMappingScene(); }));
		m_exampleScenes.push_back(std::make_pair(ShadowScene::m_SceneName, []() { return new ShadowScene(); }));
		m_exampleScenes.push_back(std::make_pair(FinalScene::m_SceneName, []() { return new FinalScene(); }));

		/* 기본 프레임버퍼의 초기화 깊이와 초기화 색상 설정 (장면에 카메라가 없기 때문에 수동으로 호출해야 함) */
		GL_CHECK(glClearDepth(1.0f));
		GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));

		return true;
	}

	/* 매 프레임마다 호출되는 업데이트 함수 */
	bool ExampleManager::OnUpdate()
	{
		/* 기본 프레임버퍼의 깊이와 색상 초기화 (장면에 카메라가 없기 때문에 수동으로 호출해야 함) */
		GL_CHECK(glClear(GL_DEPTH_BUFFER_BIT));
		GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));

		return true;
	}

	/* 매 프레임마다 호출되는 GUI 렌더링 함수 */
	bool ExampleManager::OnRenderGui()
	{
		ImGui::Text(">---------- Example List -----------<");

		/* 각 예제 장면당 하나의 버튼을 만들어 선택 시 장면을 변경할 수 있도록 함 */
		for (unsigned i{ 0 }; i < m_exampleScenes.size(); ++i)
		{
			if (ImGui::Button(m_exampleScenes[i].first.c_str()))
			{
				/* 버튼을 누를 시 장면과 GUI 창의 타이틀 변경 */
				ansi::Core::GetWindow()->SetNextScene(m_exampleScenes[i].second());
				ansi::Core::GetGui()->SetTitle(m_exampleScenes[i].first);
			}
		}

		ImGui::NewLine();

		return true;
	}

}
