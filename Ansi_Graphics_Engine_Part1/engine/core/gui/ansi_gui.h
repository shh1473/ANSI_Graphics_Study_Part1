#pragma once

#include "core/ansi_core.h"

namespace ansi
{

	/* GUI Ŭ���� */
	class Gui
	{
	public:
		/* ������ */
		explicit Gui();
		/* �Ҹ��� */
		~Gui();

		/* �ʱ�ȭ �Լ� */
		bool Initialize();
		/* GUI �������� �����ϴ� �Լ�
		* @returns ImGui â�� ������ �ִ���(GUI �������� �ʿ�����) ����
		*/
		bool OnRenderBegin();
		/* GUI �������� ������ �Լ� */
		void OnRenderEnd();

		/* Setter - GUI â Ÿ��Ʋ */
		void SetTitle(const std::string & title) { m_title = title; }

		/* Getter - â ���� ���콺�� �ö󰬴��� ���� */
		bool GetIsWindowHovered() const { return m_isWindowHovered; }

	private:
		/* ImGui ���ؽ�Ʈ ���� ���� */
		bool m_isCreatedContext;
		/* GLFW-binding �ʱ�ȭ ���� */
		bool m_isInitializedGlfw;
		/* OpenGL-binding �ʱ�ȭ ���� */
		bool m_isInitializedOpenGL;
		/* â ���� ���콺�� �ö󰬴��� ���� */
		bool m_isWindowHovered;
		/* GUI â Ÿ��Ʋ */
		std::string m_title;

	};

}
