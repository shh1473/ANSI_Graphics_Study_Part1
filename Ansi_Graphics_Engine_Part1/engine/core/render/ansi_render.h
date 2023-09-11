#pragma once

#include "common/ansi_common_render.h"
#include "core/ansi_core.h"

namespace ansi
{

	/* 전방 선언 */
	class Camera;
	class Renderer;
	class InputExecutor;
	class OutputExecutor;
	class ShaderExecutor;
	class BuiltIn;

	/* 렌더 클래스 */
	class Render
	{
	public:
		/* 생성자 */
		explicit Render();
		/* 소멸자 */
		~Render();

		/* 초기화 함수 */
		bool Initialize();
		/* OpenGL 컨텍스트의 모든 상태를 초기화하는 함수 */
		bool Reset();

		/* 매 프레임마다 호출되는 렌더링 함수 */
		bool OnRender();

		/* 카메라를 등록하는 함수
		* @param camera - 카메라
		* @param type - 카메라 종류
		*/
		void AddCamera(Camera * camera, CameraType type) { m_cameras[static_cast<unsigned>(type)].push_back(camera); }
		/* 카메라를 등록 해제하는 함수
		* @param camera - 카메라
		* @param type - 카메라 종류
		*/
		void RemoveCamera(Camera * camera, CameraType type)
		{
			unsigned typeIndex{ static_cast<unsigned>(type) };
			m_cameras[typeIndex].erase(std::find(m_cameras[typeIndex].begin(), m_cameras[typeIndex].end(), camera));
		}

		/* 렌더러를 등록하는 함수
		* @param renderer - 렌더러
		* @param type - 렌더러 종류
		*/
		void AddRenderer(Renderer * renderer, RendererType type) { m_renderers[static_cast<unsigned>(type)].push_back(renderer); }
		/* 렌더러를 등록 해제하는 함수
		* @param renderer - 렌더러
		* @param type - 렌더러 종류
		*/
		void RemoveRenderer(Renderer * renderer, RendererType type)
		{
			unsigned typeIndex{ static_cast<unsigned>(type) };
			m_renderers[typeIndex].erase(std::find(m_renderers[typeIndex].begin(), m_renderers[typeIndex].end(), renderer));
		}

		/* Getter - 현재 카메라 */
		Camera * GetCurrentCamera() const { return m_currentCamera; }
		/* Getter - 내장 자원 */
		BuiltIn * GetBuiltIn() const { return m_builtIn; }

	private:
		/* 설정한 OpenGL 컨텍스트의 상태로 렌더링을 실행하는 함수 */
		bool Draw();

	private:
		/* 현재 카메라 */
		Camera * m_currentCamera;
		/* 입력 실행기 */
		InputExecutor * m_inputExecutor;
		/* 출력 실행기 */
		OutputExecutor * m_outputExecutor;
		/* 셰이더 실행기 */
		ShaderExecutor * m_shaderExecutor;
		/* 내장 자원 */
		BuiltIn * m_builtIn;
		/* 종류별 카메라 배열 (시야, 광원) */
		std::vector<Camera *> m_cameras[static_cast<unsigned>(CameraType::length)];
		/* 종류별 렌더러 배열 (일반, HUD) */
		std::vector<Renderer *> m_renderers[static_cast<unsigned>(RendererType::length)];

	};

}
