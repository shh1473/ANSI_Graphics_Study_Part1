#include "ansi_window.h"

#include "core/timer/ansi_timer.h"
#include "core/render/ansi_render.h"
#include "core/gui/ansi_gui.h"
#include "scene/ansi_scene.h"
#include "utility/obj_loader/ansi_obj_loader.h"
#include "utility/event_listener/ansi_event_listener.h"

#include "../examples/manager/example_manager.h"

namespace ansi
{

	/* 창 크기를 변경할 경우 호출되는 함수
	* @param window - GLFW 창
	* @param width - 변경된 창의 너비 (픽셀 단위)
	* @param height - 변경된 창의 높이 (픽셀 단위)
	*/
	void OnWindowResize(GLFWwindow * window, int width, int height);
	/* 마우스 버튼을 누르거나 뗄 경우 호출되는 함수
	* @param window - GLFW 창
	* @param key - 누르거나 뗀 마우스 버튼 (GLFW_MOUSE_BUTTON_LEFT, GLFW_MOUSE_BUTTON_RIGHT, GLFW_MOUSE_BUTTON_MIDDLE)
	* @param action - 마우스 버튼의 상태 (GLFW_RELEASE, GLFW_PRESS)
	* @param mods - 마우스 버튼과 함께 누른 키 (GLFW_MOD_CONTROL, GLFW_MOD_SHIFT, GLFW_MOD_ALT)
	*/
	void OnMouseButton(GLFWwindow * window, int button, int action, int mods);
	/* 마우스를 움직일 경우 호출되는 함수
	* @param window - GLFW 창
	* @param positionX - 마우스의 X 위치 (픽셀 단위)
	* @param positionY - 마우스의 Y 위치 (픽셀 단위)
	*/
	void OnMouseMove(GLFWwindow * window, double positionX, double positionY);
	/* 마우스를 스크롤할 경우 호출되는 함수
	* @param window - GLFW 창
	* @param deltaX - X 방향으로 스크롤한 양 (사용하지 않음)
	* @param deltaY - Y 방향으로 스크롤한 양 ((+): 위로 스크롤, (-): 아래로 스크롤, 한 틱당 값: 1)
	*/
	void OnMouseWheel(GLFWwindow * window, double deltaX, double deltaY);

	/* 생성자 */
	Window::Window()
		: m_isGlfwInitialized(false)
		, m_isWindowed(true)
		, m_isBorderless(false)
		, m_clientSize(1280.0f, 720.0f)
		, m_mousePosition(0.0f)
		, m_window(nullptr)
		, m_currentScene(nullptr)
		, m_nextScene(nullptr)
		, m_eventListeners()
	{

	}

	/* 소멸자 */
	Window::~Window()
	{
		/* 현재 장면 제거 */
		SAFE_DELETE(m_currentScene);
		/* 다음 장면 제거 */
		SAFE_DELETE(m_nextScene);
		/* GLFW 초기화에 성공했을 경우 메모리 정리 */
		if (m_isGlfwInitialized) { glfwTerminate(); }
	}

	/* 초기화 함수 */
	bool Window::Initialize()
	{
		/* GLFW 초기화 */
		CHECK_PRINT_RF(glfwInit() == GLFW_TRUE, "[GLFW Error]: GLFW Initialization");
		/* GLFW 버전 출력 */
		PRINT("GLFW Version: " + std::string(glfwGetVersionString()));
		/* GLFW 초기화 여부 체크 */
		m_isGlfwInitialized = true;

		/* 창 생성 */
		CHECK_PRINT_RF(m_window = glfwCreateWindow(
			static_cast<int>(m_clientSize.x),
			static_cast<int>(m_clientSize.y),
			"A.N.S.I Graphics Engine Part 1", nullptr, nullptr), "[GLFW Error]: Window Creation");
		/* OpenGL 컨텍스트 생성 */
		GLFW_CHECK(glfwMakeContextCurrent(m_window));
		/* 스왑 간격 설정 */
		GLFW_CHECK(glfwSwapInterval(0));

		/* GLEW 초기화 */
		GLenum result{ glewInit() };
		CHECK_PRINT_RF(result == GLEW_OK, glewGetErrorString(result));
		/* GLEW 버전 출력 */
		PRINT("GLEW Version: " + std::string(reinterpret_cast<const char *>(glewGetString(GLEW_VERSION))));
		/* OpenGL 버전 확인 */
		PRINT("OpenGL Version: " + std::string(reinterpret_cast<const char *>(glGetString(GL_VERSION))));

		/* 창 크기 변경 이벤트 콜백 설정 */
		GLFW_CHECK(glfwSetWindowSizeCallback(m_window, OnWindowResize));
		/* 마우스 버튼 이벤트 콜백 설정 */
		GLFW_CHECK(glfwSetMouseButtonCallback(m_window, OnMouseButton));
		/* 마우스 위치 이벤트 콜백 설정 */
		GLFW_CHECK(glfwSetCursorPosCallback(m_window, OnMouseMove));
		/* 마우스 스크롤 이벤트 콜백 설정 */
		GLFW_CHECK(glfwSetScrollCallback(m_window, OnMouseWheel));

		/* 시작 장면 설정 및 적용 */
		m_nextScene = new example::ExampleManager();
		CHECK_RF(ApplyChangeScene());

		/* 프레임버퍼 초기화 색상 설정 */
		GL_CHECK_RF(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		/* 프레임버퍼 초기화 깊이 설정 */
		GL_CHECK_RF(glClearDepthf(1.0f));

		PRINT("");

		return true;
	}

	/* 프로그램 루프를 시작하는 함수 */
	bool Window::Run()
	{
		/* 창 닫기 플래그가 반환되기 전까지 루프 실행 */
		while (!glfwWindowShouldClose(m_window))
		{
			/* ============================== */
			/*             UPDATE             */
			/* ============================== */

			/* 프레임 간 시간 간격 업데이트 */
			Core::GetTimer()->OnUpdate();

			/* 장면에 소속된 오브젝트의 업데이트 함수 호출 */
			CHECK_RF(m_currentScene->OnDefaultUpdate());
			/* 장면의 업데이트 함수 호출 */
			CHECK_RF(m_currentScene->OnUpdate());

			/* 장면에 소속된 오브젝트의 지연 업데이트 함수 호출 */
			CHECK_RF(m_currentScene->OnDefaultLateUpdate());
			/* 장면의 지연 업데이트 함수 호출 */
			CHECK_RF(m_currentScene->OnLateUpdate());

			/* ============================== */
			/*             RENDER             */
			/* ============================== */

			/* 장면에 소속된 모든 오브젝트 렌더링 */
			CHECK_RF(Core::GetRender()->OnRender());

			/* GUI 렌더링 시작 */
			if (Core::GetGui()->OnRenderBegin())
			{
				/* 장면의 GUI 렌더링 */
				CHECK_RF(m_currentScene->OnRenderGui());
				/* 기본 공통 GUI 렌더링 (창 모드, 해상도 변경 등) */
				CHECK_RF(OnRenderGui());
			}
			/* GUI 렌더링 종료 */
			Core::GetGui()->OnRenderEnd();

			/* ============================== */
			/*            HANDLING            */
			/* ============================== */

			/* 프레임버퍼 스왑 */
			GLFW_CHECK(glfwSwapBuffers(m_window));
			/* 이벤트 처리 */
			GLFW_CHECK(glfwPollEvents());

			/* 예약한 다음 장면이 있을 경우, 장면 변경 */
			if (m_nextScene) { CHECK_RF(ApplyChangeScene()); }
		}

		return true;
	}

	/* 매 프레임마다 호출되는 기본 공통 GUI 렌더링 함수 */
	bool Window::OnRenderGui()
	{
		/* 구분선 출력 */
		ImGui::Text(">--------- Window Settings ---------<");

		/* [체크박스] - 창 모드 */
		ImGui::Checkbox("Windowed", &m_isWindowed);
		/* 창 모드일 경우 */
		if (m_isWindowed) {
			/* [체크박스] - 테두리 없는 창 모드 */
			ImGui::Checkbox("Borderless", &m_isBorderless);
			/* 테두리 없는 창 모드가 아닐 경우 */
			if (!m_isBorderless)
			{
				/* [입력] - 해상도 */
				ImGui::InputFloat2("Resolution", &m_clientSize[0]);
			}
		}

		/* [버튼] - 적용 */
		if (ImGui::Button("Apply"))
		{ 
			CHECK_RF(ApplyWindowSettings());
		}

		return true;
	}

	/* GUI로 선택한 창 설정을 적용하는 함수 */
	bool Window::ApplyWindowSettings()
	{
		/* 주 모니터 정보 불러오기 */
		GLFWmonitor * monitor{ glfwGetPrimaryMonitor() };
		CHECK_PRINT_RF(monitor, "[Window Error]: Can't find primary monitor");
		/* 주 모니터의 비디오 모드(해상도, 채널, 주사율) 불러오기 */
		const GLFWvidmode * mode{ glfwGetVideoMode(monitor) };
		CHECK_PRINT_RF(mode, "[Window Error]: Can't find video mode");

		/* 창 모드일 경우 */
		if (m_isWindowed)
		{
			/* 테두리 없는 창 모드일 경우 */
			if (m_isBorderless)
			{
				/* 전체 해상도로 화면에 딱 맞게 설정 */
				GLFW_CHECK(glfwSetWindowMonitor(m_window, nullptr, 0, 0,
					mode->width, mode->height, mode->refreshRate));
			}
			/* 테두리 없는 창 모드가 아닐 경우 */
			else
			{
				/* 현재 창 위치 가져오기 */
				glm::ivec2 windowPosition(0);
				GLFW_CHECK(glfwGetWindowPos(m_window, &windowPosition.x, &windowPosition.y));
				/* GUI로 선택한 해상도로 설정 (밖으로 나가는 것을 방지하기 위해 모니터 왼쪽 상단으로부터 최소 50픽셀의 간격을 둠) */
				GLFW_CHECK(glfwSetWindowMonitor(m_window, nullptr, glm::max(windowPosition.x, 50), glm::max(windowPosition.y, 50),
					static_cast<int>(m_clientSize.x), static_cast<int>(m_clientSize.y), mode->refreshRate));
			}
		}
		/* 창 모드가 아닐 경우 */
		else
		{
			/* 전체화면으로 설정 */
			GLFW_CHECK(glfwSetWindowMonitor(m_window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate));
		}

		return true;
	}

	/* 예약한 다음 장면을 현재 장면으로 변경하는 함수 */
	bool Window::ApplyChangeScene()
	{
		/* 현재 장면 제거 */
		SAFE_DELETE(m_currentScene);
		/* 다음 장면을 현재 장면으로 설정 */
		m_currentScene = m_nextScene;
		/* 다음 장면을 비움 */
		m_nextScene = nullptr;

		/* 새로운 장면의 자원 생성 */
		CHECK_RF(m_currentScene->CreateResources());
		/* 새로운 장면 초기화 */
		CHECK_RF(m_currentScene->Initialize());
		/* OpenGL 컨텍스트 상태 초기화 */
		CHECK_RF(Core::GetRender()->Reset());

		return true;
	}

	/* 창 크기를 변경할 경우 호출되는 함수 */
	void OnWindowResize(GLFWwindow * window, int width, int height)
	{
		/* 창 관리자에 변경된 창 크기 저장 */
		Core::GetWindow()->SetClientSize(static_cast<float>(width), static_cast<float>(height));
		/* 모든 이벤트 수신기에 전파 */
		for (const auto & iter : Core::GetWindow()->GetEventListeners()) { iter->OnWindowResize(glm::vec2(static_cast<float>(width), static_cast<float>(height))); }
	}

	/* 마우스 버튼을 누르거나 뗄 경우 호출되는 함수 */
	void OnMouseButton(GLFWwindow * window, int button, int action, int mods)
	{
		/* 버튼을 누른 경우 */
		if (action == GLFW_PRESS)
		{
			/* 모든 이벤트 수신기에 전파 */
			for (const auto & iter : Core::GetWindow()->GetEventListeners()) { iter->OnMouseDown(button, Core::GetWindow()->GetMousePosition()); }
		}
		/* 버튼을 뗀 경우 */
		else
		{
			/* 모든 이벤트 수신기에 전파 */
			for (const auto & iter : Core::GetWindow()->GetEventListeners()) { iter->OnMouseUp(button); }
		}
	}

	/* 마우스를 움직일 경우 호출되는 함수 */
	void OnMouseMove(GLFWwindow * window, double positionX, double positionY)
	{
		/* 창 관리자에 마우스 위치 저장 */
		Core::GetWindow()->SetMousePosition(static_cast<float>(positionX), static_cast<float>(positionY));
		/* 모든 이벤트 수신기에 전파 */
		for (const auto & iter : Core::GetWindow()->GetEventListeners()) { iter->OnMouseMove(Core::GetWindow()->GetMousePosition()); }
	}

	/* 마우스를 스크롤할 경우 호출되는 함수 */
	void OnMouseWheel(GLFWwindow * window, double deltaX, double deltaY)
	{
		/* 모든 이벤트 수신기에 전파 */
		for (const auto & iter : Core::GetWindow()->GetEventListeners()) { iter->OnMouseWheel(static_cast<float>(deltaY)); }
	}

}