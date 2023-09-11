#pragma once

#include "core/ansi_core.h"

namespace ansi
{

	/* ���� ���� */
	class Scene;
	class EventListener;

	/* â Ŭ���� */
	class Window
	{
	public:
		/* ������ */
		explicit Window();
		/* �Ҹ��� */
		~Window();

		/* �ʱ�ȭ �Լ� */
		bool Initialize();
		/* ���α׷� ������ �����ϴ� �Լ� */
		bool Run();

		/* �̺�Ʈ ���ű⸦ ����ϴ� �Լ�
		* @param listener - ����� �̺�Ʈ ���ű�
		*/
		void AddEventListener(EventListener * listener) { m_eventListeners.push_back(listener); }
		/* �̺�Ʈ ���ű⸦ ��� �����ϴ� �Լ�
		* @param listener - ��� ������ �̺�Ʈ ���ű�
		*/
		void RemoveEventListener(EventListener * listener) { m_eventListeners.erase(std::remove(m_eventListeners.begin(), m_eventListeners.end(), listener), m_eventListeners.end()); }

		/* Setter - â ũ�� */
		void SetClientSize(float width, float height) { m_clientSize.x = width; m_clientSize.y = height; }
		/* Setter - ���콺 ��ġ */
		void SetMousePosition(float x, float y) { m_mousePosition.x = x; m_mousePosition.y = y; }
		/* Setter - ���� ��� */
		void SetNextScene(Scene * nextScene) { m_nextScene = nextScene; }

		/* Getter - â ũ�� */
		const glm::vec2 & GetClientSize() const { return m_clientSize; }
		/* Getter - ���콺 ��ġ */
		const glm::vec2 & GetMousePosition() const { return m_mousePosition; }
		/* Getter - �̺�Ʈ ���ű� �迭 */
		const std::vector<EventListener *> & GetEventListeners() const { return m_eventListeners; }

	private:
		/* �� �����Ӹ��� ȣ��Ǵ� �⺻ ���� GUI ������ �Լ� */
		bool OnRenderGui();
		/* GUI�� ������ â ������ �����ϴ� �Լ� */
		bool ApplyWindowSettings();
		/* ������ ���� ����� ���� ������� �����ϴ� �Լ� */
		bool ApplyChangeScene();

	private:
		/* GLFW �ʱ�ȭ ���� */
		bool m_isGlfwInitialized;
		/* â ��� Ȱ��ȭ ���� */
		bool m_isWindowed;
		/* �׵θ� ���� â ��� Ȱ��ȭ ���� */
		bool m_isBorderless;
		/* â ũ�� (�ȼ� ����) */
		glm::vec2 m_clientSize;
		/* ���콺 ��ġ (�ȼ� ����) */
		glm::vec2 m_mousePosition;
		/* GLFW â */
		GLFWwindow * m_window;
		/* ���� ��� */
		Scene * m_currentScene;
		/* ���� ��� */
		Scene * m_nextScene;
		/* �̺�Ʈ ���ű� �迭 */
		std::vector<EventListener *> m_eventListeners;

	};

}
