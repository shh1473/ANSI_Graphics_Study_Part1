#include "ansi_gui.h"

#include "core/ansi_core.h"

namespace ansi
{

	/* ������ */
	Gui::Gui()
		: m_isCreatedContext(false)
		, m_isInitializedGlfw(false)
		, m_isInitializedOpenGL(false)
		, m_isWindowHovered(false)
		, m_title("A.N.S.I Graphics")
	{

	}

	/* �Ҹ��� */
	Gui::~Gui()
	{
		if (m_isInitializedOpenGL) { ImGui_ImplOpenGL3_Shutdown(); }
		if (m_isInitializedGlfw) { ImGui_ImplGlfw_Shutdown(); }
		if (m_isCreatedContext) { ImGui::DestroyContext(); }
	}

	/* �ʱ�ȭ �Լ� */
	bool Gui::Initialize()
	{
		/* ���� üũ */
		CHECK_RF(IMGUI_CHECKVERSION());
		/* ImGui ���ؽ�Ʈ ���� */
		ImGui::CreateContext();
		/* ��ũ �׸��� ���� */
		ImGui::StyleColorsDark();
		/* ImGui ���ؽ�Ʈ ����  ���� üũ */
		m_isCreatedContext = true;

		/* GLFW-binding �ʱ�ȭ */
		CHECK_PRINT_RF(ImGui_ImplGlfw_InitForOpenGL(glfwGetCurrentContext(), true), "[ImGui Error]: GLFW-binding Creation");
		/* GLFW-binding �ʱ�ȭ ���� üũ */
		m_isInitializedGlfw = true;

		/* OpenGL-binding �ʱ�ȭ */
		CHECK_PRINT_RF(ImGui_ImplOpenGL3_Init("#version 330"), "[ImGui Error]: OpenGL-binding Creation");
		/* OpenGL-binding �ʱ�ȭ ���� üũ */
		m_isInitializedOpenGL = true;

		return true;
	}

	/* GUI �������� �����ϴ� �Լ� */
	bool Gui::OnRenderBegin()
	{
		/* ImGui�� ���ο� ������ ���� (���� ������ ������ ����) */
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		/* �̹� �����ӿ� ǥ���� GUI ������ ���� ���� (ImGui â�� ������ �ִ��� ���� üũ) */
		bool isShowWindow{ ImGui::Begin(m_title.c_str()) };
		/* â ���� ���콺�� �ö󰬴��� ���� (�ݵ�� ImGui::Begin() �Լ� ���� ȣ���ؾ� ��) */
		m_isWindowHovered = ImGui::IsWindowHovered(ImGuiHoveredFlags_::ImGuiHoveredFlags_AnyWindow);
		
		return isShowWindow;
	}

	/* GUI �������� ������ �Լ� */
	void Gui::OnRenderEnd()
	{
		/* �̹� �����ӿ� ǥ���� GUI ������ ���� ���� */
		ImGui::End();
		/* ������ GUI �����Ϳ� ���� ImGui â ������ */
		ImGui::Render();
		/* ImGui â ������ ����� OpenGL�� �ݿ� */
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

}
