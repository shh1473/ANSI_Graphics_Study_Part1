#include "ansi_gui.h"

#include "core/ansi_core.h"

namespace ansi
{

	/* 생성자 */
	Gui::Gui()
		: m_isCreatedContext(false)
		, m_isInitializedGlfw(false)
		, m_isInitializedOpenGL(false)
		, m_isWindowHovered(false)
		, m_title("A.N.S.I Graphics")
	{

	}

	/* 소멸자 */
	Gui::~Gui()
	{
		if (m_isInitializedOpenGL) { ImGui_ImplOpenGL3_Shutdown(); }
		if (m_isInitializedGlfw) { ImGui_ImplGlfw_Shutdown(); }
		if (m_isCreatedContext) { ImGui::DestroyContext(); }
	}

	/* 초기화 함수 */
	bool Gui::Initialize()
	{
		/* 버전 체크 */
		CHECK_RF(IMGUI_CHECKVERSION());
		/* ImGui 컨텍스트 생성 */
		ImGui::CreateContext();
		/* 다크 테마로 설정 */
		ImGui::StyleColorsDark();
		/* ImGui 컨텍스트 생성  여부 체크 */
		m_isCreatedContext = true;

		/* GLFW-binding 초기화 */
		CHECK_PRINT_RF(ImGui_ImplGlfw_InitForOpenGL(glfwGetCurrentContext(), true), "[ImGui Error]: GLFW-binding Creation");
		/* GLFW-binding 초기화 여부 체크 */
		m_isInitializedGlfw = true;

		/* OpenGL-binding 초기화 */
		CHECK_PRINT_RF(ImGui_ImplOpenGL3_Init("#version 330"), "[ImGui Error]: OpenGL-binding Creation");
		/* OpenGL-binding 초기화 여부 체크 */
		m_isInitializedOpenGL = true;

		return true;
	}

	/* GUI 렌더링을 시작하는 함수 */
	bool Gui::OnRenderBegin()
	{
		/* ImGui의 새로운 프레임 시작 (이전 프레임 데이터 정리) */
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		/* 이번 프레임에 표시할 GUI 데이터 설정 시작 (ImGui 창이 펼쳐져 있는지 여부 체크) */
		bool isShowWindow{ ImGui::Begin(m_title.c_str()) };
		/* 창 위에 마우스가 올라갔는지 여부 (반드시 ImGui::Begin() 함수 이후 호출해야 함) */
		m_isWindowHovered = ImGui::IsWindowHovered(ImGuiHoveredFlags_::ImGuiHoveredFlags_AnyWindow);
		
		return isShowWindow;
	}

	/* GUI 렌더링을 끝내는 함수 */
	void Gui::OnRenderEnd()
	{
		/* 이번 프레임에 표시할 GUI 데이터 설정 종료 */
		ImGui::End();
		/* 설정한 GUI 데이터에 따라 ImGui 창 렌더링 */
		ImGui::Render();
		/* ImGui 창 렌더링 결과를 OpenGL에 반영 */
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

}
