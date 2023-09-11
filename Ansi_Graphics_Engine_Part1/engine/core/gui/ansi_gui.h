#pragma once

#include "core/ansi_core.h"

namespace ansi
{

	/* GUI 클래스 */
	class Gui
	{
	public:
		/* 생성자 */
		explicit Gui();
		/* 소멸자 */
		~Gui();

		/* 초기화 함수 */
		bool Initialize();
		/* GUI 렌더링을 시작하는 함수
		* @returns ImGui 창이 펼쳐져 있는지(GUI 렌더링이 필요한지) 여부
		*/
		bool OnRenderBegin();
		/* GUI 렌더링을 끝내는 함수 */
		void OnRenderEnd();

		/* Setter - GUI 창 타이틀 */
		void SetTitle(const std::string & title) { m_title = title; }

		/* Getter - 창 위에 마우스가 올라갔는지 여부 */
		bool GetIsWindowHovered() const { return m_isWindowHovered; }

	private:
		/* ImGui 컨텍스트 생성 여부 */
		bool m_isCreatedContext;
		/* GLFW-binding 초기화 여부 */
		bool m_isInitializedGlfw;
		/* OpenGL-binding 초기화 여부 */
		bool m_isInitializedOpenGL;
		/* 창 위에 마우스가 올라갔는지 여부 */
		bool m_isWindowHovered;
		/* GUI 창 타이틀 */
		std::string m_title;

	};

}
