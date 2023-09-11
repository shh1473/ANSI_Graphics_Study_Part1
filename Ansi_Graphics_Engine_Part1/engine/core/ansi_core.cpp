#include "ansi_core.h"

#include "core/timer/ansi_timer.h"
#include "core/window/ansi_window.h"
#include "core/gui/ansi_gui.h"
#include "core/render/ansi_render.h"
#include "core/render/built_in/ansi_built_in.h"

namespace ansi
{

	/* �̱��� �ν��Ͻ� �ʱ�ȭ */
	Core * Core::m_Instance{ nullptr };

	/* �̱��� �ν��Ͻ��� �����ϴ� �Լ� */
	bool Core::CreateInstance()
	{
		m_Instance = new Core();
		CHECK_RF(m_Instance->Initialize());

		return true;
	}

	/* �̱��� �ν��Ͻ��� �����ϴ� �Լ� */
	void Core::DeleteInstance()
	{
		SAFE_DELETE(m_Instance);
	}

	/* ������ */
	Core::Core()
		: m_timer(new Timer())
		, m_window(new Window())
		, m_render(new Render())
		, m_gui(new Gui())
	{
		
	}

	/* �Ҹ��� */
	Core::~Core()
	{
		delete m_render->GetBuiltIn();
		SAFE_DELETE(m_gui);
		SAFE_DELETE(m_window);
		SAFE_DELETE(m_render);
		SAFE_DELETE(m_timer);
	}

	/* �ʱ�ȭ �Լ� */
	bool Core::Initialize()
	{
		CHECK_RF(m_window->Initialize());
		CHECK_RF(m_render->Initialize());
		CHECK_RF(m_gui->Initialize());

		return true;
	}

}
