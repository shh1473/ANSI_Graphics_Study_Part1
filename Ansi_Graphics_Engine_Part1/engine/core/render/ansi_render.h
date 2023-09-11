#pragma once

#include "common/ansi_common_render.h"
#include "core/ansi_core.h"

namespace ansi
{

	/* ���� ���� */
	class Camera;
	class Renderer;
	class InputExecutor;
	class OutputExecutor;
	class ShaderExecutor;
	class BuiltIn;

	/* ���� Ŭ���� */
	class Render
	{
	public:
		/* ������ */
		explicit Render();
		/* �Ҹ��� */
		~Render();

		/* �ʱ�ȭ �Լ� */
		bool Initialize();
		/* OpenGL ���ؽ�Ʈ�� ��� ���¸� �ʱ�ȭ�ϴ� �Լ� */
		bool Reset();

		/* �� �����Ӹ��� ȣ��Ǵ� ������ �Լ� */
		bool OnRender();

		/* ī�޶� ����ϴ� �Լ�
		* @param camera - ī�޶�
		* @param type - ī�޶� ����
		*/
		void AddCamera(Camera * camera, CameraType type) { m_cameras[static_cast<unsigned>(type)].push_back(camera); }
		/* ī�޶� ��� �����ϴ� �Լ�
		* @param camera - ī�޶�
		* @param type - ī�޶� ����
		*/
		void RemoveCamera(Camera * camera, CameraType type)
		{
			unsigned typeIndex{ static_cast<unsigned>(type) };
			m_cameras[typeIndex].erase(std::find(m_cameras[typeIndex].begin(), m_cameras[typeIndex].end(), camera));
		}

		/* �������� ����ϴ� �Լ�
		* @param renderer - ������
		* @param type - ������ ����
		*/
		void AddRenderer(Renderer * renderer, RendererType type) { m_renderers[static_cast<unsigned>(type)].push_back(renderer); }
		/* �������� ��� �����ϴ� �Լ�
		* @param renderer - ������
		* @param type - ������ ����
		*/
		void RemoveRenderer(Renderer * renderer, RendererType type)
		{
			unsigned typeIndex{ static_cast<unsigned>(type) };
			m_renderers[typeIndex].erase(std::find(m_renderers[typeIndex].begin(), m_renderers[typeIndex].end(), renderer));
		}

		/* Getter - ���� ī�޶� */
		Camera * GetCurrentCamera() const { return m_currentCamera; }
		/* Getter - ���� �ڿ� */
		BuiltIn * GetBuiltIn() const { return m_builtIn; }

	private:
		/* ������ OpenGL ���ؽ�Ʈ�� ���·� �������� �����ϴ� �Լ� */
		bool Draw();

	private:
		/* ���� ī�޶� */
		Camera * m_currentCamera;
		/* �Է� ����� */
		InputExecutor * m_inputExecutor;
		/* ��� ����� */
		OutputExecutor * m_outputExecutor;
		/* ���̴� ����� */
		ShaderExecutor * m_shaderExecutor;
		/* ���� �ڿ� */
		BuiltIn * m_builtIn;
		/* ������ ī�޶� �迭 (�þ�, ����) */
		std::vector<Camera *> m_cameras[static_cast<unsigned>(CameraType::length)];
		/* ������ ������ �迭 (�Ϲ�, HUD) */
		std::vector<Renderer *> m_renderers[static_cast<unsigned>(RendererType::length)];

	};

}
