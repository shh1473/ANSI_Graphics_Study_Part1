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

	/* â ũ�⸦ ������ ��� ȣ��Ǵ� �Լ�
	* @param window - GLFW â
	* @param width - ����� â�� �ʺ� (�ȼ� ����)
	* @param height - ����� â�� ���� (�ȼ� ����)
	*/
	void OnWindowResize(GLFWwindow * window, int width, int height);
	/* ���콺 ��ư�� �����ų� �� ��� ȣ��Ǵ� �Լ�
	* @param window - GLFW â
	* @param key - �����ų� �� ���콺 ��ư (GLFW_MOUSE_BUTTON_LEFT, GLFW_MOUSE_BUTTON_RIGHT, GLFW_MOUSE_BUTTON_MIDDLE)
	* @param action - ���콺 ��ư�� ���� (GLFW_RELEASE, GLFW_PRESS)
	* @param mods - ���콺 ��ư�� �Բ� ���� Ű (GLFW_MOD_CONTROL, GLFW_MOD_SHIFT, GLFW_MOD_ALT)
	*/
	void OnMouseButton(GLFWwindow * window, int button, int action, int mods);
	/* ���콺�� ������ ��� ȣ��Ǵ� �Լ�
	* @param window - GLFW â
	* @param positionX - ���콺�� X ��ġ (�ȼ� ����)
	* @param positionY - ���콺�� Y ��ġ (�ȼ� ����)
	*/
	void OnMouseMove(GLFWwindow * window, double positionX, double positionY);
	/* ���콺�� ��ũ���� ��� ȣ��Ǵ� �Լ�
	* @param window - GLFW â
	* @param deltaX - X �������� ��ũ���� �� (������� ����)
	* @param deltaY - Y �������� ��ũ���� �� ((+): ���� ��ũ��, (-): �Ʒ��� ��ũ��, �� ƽ�� ��: 1)
	*/
	void OnMouseWheel(GLFWwindow * window, double deltaX, double deltaY);

	/* ������ */
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

	/* �Ҹ��� */
	Window::~Window()
	{
		/* ���� ��� ���� */
		SAFE_DELETE(m_currentScene);
		/* ���� ��� ���� */
		SAFE_DELETE(m_nextScene);
		/* GLFW �ʱ�ȭ�� �������� ��� �޸� ���� */
		if (m_isGlfwInitialized) { glfwTerminate(); }
	}

	/* �ʱ�ȭ �Լ� */
	bool Window::Initialize()
	{
		/* GLFW �ʱ�ȭ */
		CHECK_PRINT_RF(glfwInit() == GLFW_TRUE, "[GLFW Error]: GLFW Initialization");
		/* GLFW ���� ��� */
		PRINT("GLFW Version: " + std::string(glfwGetVersionString()));
		/* GLFW �ʱ�ȭ ���� üũ */
		m_isGlfwInitialized = true;

		/* â ���� */
		CHECK_PRINT_RF(m_window = glfwCreateWindow(
			static_cast<int>(m_clientSize.x),
			static_cast<int>(m_clientSize.y),
			"A.N.S.I Graphics Engine Part 1", nullptr, nullptr), "[GLFW Error]: Window Creation");
		/* OpenGL ���ؽ�Ʈ ���� */
		GLFW_CHECK(glfwMakeContextCurrent(m_window));
		/* ���� ���� ���� */
		GLFW_CHECK(glfwSwapInterval(0));

		/* GLEW �ʱ�ȭ */
		GLenum result{ glewInit() };
		CHECK_PRINT_RF(result == GLEW_OK, glewGetErrorString(result));
		/* GLEW ���� ��� */
		PRINT("GLEW Version: " + std::string(reinterpret_cast<const char *>(glewGetString(GLEW_VERSION))));
		/* OpenGL ���� Ȯ�� */
		PRINT("OpenGL Version: " + std::string(reinterpret_cast<const char *>(glGetString(GL_VERSION))));

		/* â ũ�� ���� �̺�Ʈ �ݹ� ���� */
		GLFW_CHECK(glfwSetWindowSizeCallback(m_window, OnWindowResize));
		/* ���콺 ��ư �̺�Ʈ �ݹ� ���� */
		GLFW_CHECK(glfwSetMouseButtonCallback(m_window, OnMouseButton));
		/* ���콺 ��ġ �̺�Ʈ �ݹ� ���� */
		GLFW_CHECK(glfwSetCursorPosCallback(m_window, OnMouseMove));
		/* ���콺 ��ũ�� �̺�Ʈ �ݹ� ���� */
		GLFW_CHECK(glfwSetScrollCallback(m_window, OnMouseWheel));

		/* ���� ��� ���� �� ���� */
		m_nextScene = new example::ExampleManager();
		CHECK_RF(ApplyChangeScene());

		/* �����ӹ��� �ʱ�ȭ ���� ���� */
		GL_CHECK_RF(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		/* �����ӹ��� �ʱ�ȭ ���� ���� */
		GL_CHECK_RF(glClearDepthf(1.0f));

		PRINT("");

		return true;
	}

	/* ���α׷� ������ �����ϴ� �Լ� */
	bool Window::Run()
	{
		/* â �ݱ� �÷��װ� ��ȯ�Ǳ� ������ ���� ���� */
		while (!glfwWindowShouldClose(m_window))
		{
			/* ============================== */
			/*             UPDATE             */
			/* ============================== */

			/* ������ �� �ð� ���� ������Ʈ */
			Core::GetTimer()->OnUpdate();

			/* ��鿡 �Ҽӵ� ������Ʈ�� ������Ʈ �Լ� ȣ�� */
			CHECK_RF(m_currentScene->OnDefaultUpdate());
			/* ����� ������Ʈ �Լ� ȣ�� */
			CHECK_RF(m_currentScene->OnUpdate());

			/* ��鿡 �Ҽӵ� ������Ʈ�� ���� ������Ʈ �Լ� ȣ�� */
			CHECK_RF(m_currentScene->OnDefaultLateUpdate());
			/* ����� ���� ������Ʈ �Լ� ȣ�� */
			CHECK_RF(m_currentScene->OnLateUpdate());

			/* ============================== */
			/*             RENDER             */
			/* ============================== */

			/* ��鿡 �Ҽӵ� ��� ������Ʈ ������ */
			CHECK_RF(Core::GetRender()->OnRender());

			/* GUI ������ ���� */
			if (Core::GetGui()->OnRenderBegin())
			{
				/* ����� GUI ������ */
				CHECK_RF(m_currentScene->OnRenderGui());
				/* �⺻ ���� GUI ������ (â ���, �ػ� ���� ��) */
				CHECK_RF(OnRenderGui());
			}
			/* GUI ������ ���� */
			Core::GetGui()->OnRenderEnd();

			/* ============================== */
			/*            HANDLING            */
			/* ============================== */

			/* �����ӹ��� ���� */
			GLFW_CHECK(glfwSwapBuffers(m_window));
			/* �̺�Ʈ ó�� */
			GLFW_CHECK(glfwPollEvents());

			/* ������ ���� ����� ���� ���, ��� ���� */
			if (m_nextScene) { CHECK_RF(ApplyChangeScene()); }
		}

		return true;
	}

	/* �� �����Ӹ��� ȣ��Ǵ� �⺻ ���� GUI ������ �Լ� */
	bool Window::OnRenderGui()
	{
		/* ���м� ��� */
		ImGui::Text(">--------- Window Settings ---------<");

		/* [üũ�ڽ�] - â ��� */
		ImGui::Checkbox("Windowed", &m_isWindowed);
		/* â ����� ��� */
		if (m_isWindowed) {
			/* [üũ�ڽ�] - �׵θ� ���� â ��� */
			ImGui::Checkbox("Borderless", &m_isBorderless);
			/* �׵θ� ���� â ��尡 �ƴ� ��� */
			if (!m_isBorderless)
			{
				/* [�Է�] - �ػ� */
				ImGui::InputFloat2("Resolution", &m_clientSize[0]);
			}
		}

		/* [��ư] - ���� */
		if (ImGui::Button("Apply"))
		{ 
			CHECK_RF(ApplyWindowSettings());
		}

		return true;
	}

	/* GUI�� ������ â ������ �����ϴ� �Լ� */
	bool Window::ApplyWindowSettings()
	{
		/* �� ����� ���� �ҷ����� */
		GLFWmonitor * monitor{ glfwGetPrimaryMonitor() };
		CHECK_PRINT_RF(monitor, "[Window Error]: Can't find primary monitor");
		/* �� ������� ���� ���(�ػ�, ä��, �ֻ���) �ҷ����� */
		const GLFWvidmode * mode{ glfwGetVideoMode(monitor) };
		CHECK_PRINT_RF(mode, "[Window Error]: Can't find video mode");

		/* â ����� ��� */
		if (m_isWindowed)
		{
			/* �׵θ� ���� â ����� ��� */
			if (m_isBorderless)
			{
				/* ��ü �ػ󵵷� ȭ�鿡 �� �°� ���� */
				GLFW_CHECK(glfwSetWindowMonitor(m_window, nullptr, 0, 0,
					mode->width, mode->height, mode->refreshRate));
			}
			/* �׵θ� ���� â ��尡 �ƴ� ��� */
			else
			{
				/* ���� â ��ġ �������� */
				glm::ivec2 windowPosition(0);
				GLFW_CHECK(glfwGetWindowPos(m_window, &windowPosition.x, &windowPosition.y));
				/* GUI�� ������ �ػ󵵷� ���� (������ ������ ���� �����ϱ� ���� ����� ���� ������κ��� �ּ� 50�ȼ��� ������ ��) */
				GLFW_CHECK(glfwSetWindowMonitor(m_window, nullptr, glm::max(windowPosition.x, 50), glm::max(windowPosition.y, 50),
					static_cast<int>(m_clientSize.x), static_cast<int>(m_clientSize.y), mode->refreshRate));
			}
		}
		/* â ��尡 �ƴ� ��� */
		else
		{
			/* ��üȭ������ ���� */
			GLFW_CHECK(glfwSetWindowMonitor(m_window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate));
		}

		return true;
	}

	/* ������ ���� ����� ���� ������� �����ϴ� �Լ� */
	bool Window::ApplyChangeScene()
	{
		/* ���� ��� ���� */
		SAFE_DELETE(m_currentScene);
		/* ���� ����� ���� ������� ���� */
		m_currentScene = m_nextScene;
		/* ���� ����� ��� */
		m_nextScene = nullptr;

		/* ���ο� ����� �ڿ� ���� */
		CHECK_RF(m_currentScene->CreateResources());
		/* ���ο� ��� �ʱ�ȭ */
		CHECK_RF(m_currentScene->Initialize());
		/* OpenGL ���ؽ�Ʈ ���� �ʱ�ȭ */
		CHECK_RF(Core::GetRender()->Reset());

		return true;
	}

	/* â ũ�⸦ ������ ��� ȣ��Ǵ� �Լ� */
	void OnWindowResize(GLFWwindow * window, int width, int height)
	{
		/* â �����ڿ� ����� â ũ�� ���� */
		Core::GetWindow()->SetClientSize(static_cast<float>(width), static_cast<float>(height));
		/* ��� �̺�Ʈ ���ű⿡ ���� */
		for (const auto & iter : Core::GetWindow()->GetEventListeners()) { iter->OnWindowResize(glm::vec2(static_cast<float>(width), static_cast<float>(height))); }
	}

	/* ���콺 ��ư�� �����ų� �� ��� ȣ��Ǵ� �Լ� */
	void OnMouseButton(GLFWwindow * window, int button, int action, int mods)
	{
		/* ��ư�� ���� ��� */
		if (action == GLFW_PRESS)
		{
			/* ��� �̺�Ʈ ���ű⿡ ���� */
			for (const auto & iter : Core::GetWindow()->GetEventListeners()) { iter->OnMouseDown(button, Core::GetWindow()->GetMousePosition()); }
		}
		/* ��ư�� �� ��� */
		else
		{
			/* ��� �̺�Ʈ ���ű⿡ ���� */
			for (const auto & iter : Core::GetWindow()->GetEventListeners()) { iter->OnMouseUp(button); }
		}
	}

	/* ���콺�� ������ ��� ȣ��Ǵ� �Լ� */
	void OnMouseMove(GLFWwindow * window, double positionX, double positionY)
	{
		/* â �����ڿ� ���콺 ��ġ ���� */
		Core::GetWindow()->SetMousePosition(static_cast<float>(positionX), static_cast<float>(positionY));
		/* ��� �̺�Ʈ ���ű⿡ ���� */
		for (const auto & iter : Core::GetWindow()->GetEventListeners()) { iter->OnMouseMove(Core::GetWindow()->GetMousePosition()); }
	}

	/* ���콺�� ��ũ���� ��� ȣ��Ǵ� �Լ� */
	void OnMouseWheel(GLFWwindow * window, double deltaX, double deltaY)
	{
		/* ��� �̺�Ʈ ���ű⿡ ���� */
		for (const auto & iter : Core::GetWindow()->GetEventListeners()) { iter->OnMouseWheel(static_cast<float>(deltaY)); }
	}

}