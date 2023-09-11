#include "ansi_render.h"

#include "core/render/input_executor/ansi_input_executor.h"
#include "core/render/output_executor/ansi_output_executor.h"
#include "core/render/shader_executor/ansi_shader_executor.h"
#include "core/render/built_in/ansi_built_in.h"
#include "resource/framebuffer/ansi_framebuffer.h"
#include "object/ansi_object.h"
#include "object/component/camera/ansi_camera.h"
#include "object/component/camera/post_effect_camera/ansi_post_effect_camera.h"
#include "object/component/renderer/ansi_renderer.h"

namespace ansi
{

	/* ������ */
	Render::Render()
		: m_currentCamera(nullptr)
		, m_inputExecutor(new InputExecutor())
		, m_outputExecutor(new OutputExecutor())
		, m_shaderExecutor(new ShaderExecutor())
		, m_builtIn(new BuiltIn())
		, m_cameras()
		, m_renderers()
	{

	}

	/* �Ҹ��� */
	Render::~Render()
	{
		SAFE_DELETE(m_inputExecutor);
		SAFE_DELETE(m_outputExecutor);
		SAFE_DELETE(m_shaderExecutor);
	}

	/* �ʱ�ȭ �Լ� */
	bool Render::Initialize()
	{
		/* ���� �ڿ� ���� */
		CHECK_RF(m_builtIn->Initialize());

		return true;
	}

	/* OpenGL ���ؽ�Ʈ�� ��� ���¸� �ʱ�ȭ�ϴ� �Լ� */
	bool Render::Reset()
	{
		/* ��� ������� ���� �ʱ�ȭ */
		CHECK_RF(m_inputExecutor->Reset());
		CHECK_RF(m_outputExecutor->Reset());
		CHECK_RF(m_shaderExecutor->Reset());

		return true;
	}

	/* �� �����Ӹ��� ȣ��Ǵ� ������ �Լ� */
	bool Render::OnRender()
	{
		/* === ���� ��� === */

		/* ��� ���� ī�޶� ��ȸ */
		for (const auto & camera : m_cameras[static_cast<unsigned>(CameraType::Light)])
		{
			/* ������Ʈ�� ī�޶� ��Ȱ��ȭ�� ��� ���� */
			if (!camera->GetObject()->GetIsEnabled() || !camera->GetIsEnabled()) { continue; }
			m_currentCamera = camera;

			/* ��� ������� ���¸� ī�޶��� ��� ���� �������� ���� */
			CHECK_RF(m_outputExecutor->Apply(camera->GetOutput()));

			/* ��� �Ϲ� �������� ��ȸ */
			for (const auto & renderer : m_renderers[static_cast<unsigned>(RendererType::Normal)])
			{
				/* ������Ʈ�� �������� ��Ȱ��ȭ�ưų�, �׸��ڸ� �������� �ʴ� ��� ���� */
				if (!renderer->GetObject()->GetIsEnabled() ||
					!renderer->GetIsEnabled() ||
					!renderer->GetIsCastShadow()) { continue; }

				/* ���� ��� ������ Ʈ�������� ���� �������� Ʈ���������� ���� */
				m_builtIn->GetDepthMaterial()->SetTransform(renderer->GetObject()->GetTransform());

				/* �Է� ������ ���̴� ����⿡ ���� ���� �� ���� */
				CHECK_RF(m_inputExecutor->Apply(renderer->GetInput()));
				CHECK_RF(m_shaderExecutor->Apply(m_builtIn->GetDepthMaterial()));
				CHECK_RF(Draw());
			}
		}

		/* === ������Ʈ (�Ϲ�) ������ === */

		/* ��� �þ� ī�޶� ��ȸ */
		for (const auto & camera : m_cameras[static_cast<unsigned>(CameraType::View)])
		{
			/* ������Ʈ�� ī�޶� ��Ȱ��ȭ�� ��� ���� */
			if (!camera->GetObject()->GetIsEnabled() || !camera->GetIsEnabled()) { continue; }
			m_currentCamera = camera;

			/* ��� ������� ���¸� ī�޶��� ��� ���� �������� ���� */
			CHECK_RF(m_outputExecutor->Apply(camera->GetOutput()));

			/* ��� �Ϲ� �������� ��ȸ */
			for (const auto & renderer : m_renderers[static_cast<unsigned>(RendererType::Normal)])
			{
				/* ������Ʈ�� �������� ��Ȱ��ȭ�� ��� ���� */
				if (!renderer->GetObject()->GetIsEnabled() || !renderer->GetIsEnabled()) { continue; }

				/* �Է� ������ ���̴� ����⿡ ���� ���� �� ���� */
				CHECK_RF(m_inputExecutor->Apply(renderer->GetInput()));
				CHECK_RF(m_shaderExecutor->Apply(renderer->GetMaterial()));
				CHECK_RF(Draw());
			}
		}

		/* === ��ó�� === */

		/* ��� �þ� ī�޶� ��ȸ */
		for (const auto & camera : m_cameras[static_cast<unsigned>(CameraType::View)])
		{
			/* ������Ʈ�� ī�޶� ��Ȱ��ȭ�Ǿ��ų� ��ó�� ī�޶� �ƴ� ��� ���� */
			if (!camera->GetObject()->GetIsEnabled() || !camera->GetIsEnabled() || !camera->GetIsPostEffectCamera()) { continue; }
			m_currentCamera = camera;

			/* ��� ��ó�� ȿ���� ��ȸ */
			for (const auto & effect : static_cast<PostEffectCamera *>(camera)->GetEffects())
			{
				unsigned framebufferId = (effect->GetFramebuffer()) ? effect->GetFramebuffer()->GetId() : 0;
				camera->GetOutput()->SetFramebufferId(framebufferId);

				/* ��� ������� ���¸� ī�޶��� ��� ���� �������� ���� */
				CHECK_RF(m_outputExecutor->Apply(camera->GetOutput()));

				/* �Է� ������ ���̴� ����⿡ ���� ���� �� ���� */
				CHECK_RF(m_inputExecutor->Apply(m_builtIn->GetScreenAlignedQuadIP()));
				CHECK_RF(m_shaderExecutor->Apply(effect->GetMaterial()));
				CHECK_RF(Draw());
			}

			camera->GetOutput()->SetFramebufferId(camera->GetFramebuffer()->GetId());
		}

		/* === ������Ʈ (HUD) ������ === */

		/* ��� �þ� ī�޶� ��ȸ */
		for (const auto & camera : m_cameras[static_cast<unsigned>(CameraType::View)])
		{
			/* ������Ʈ�� ī�޶� ��Ȱ��ȭ�� ��� ���� */
			if (!camera->GetObject()->GetIsEnabled() || !camera->GetIsEnabled()) { continue; }
			m_currentCamera = camera;

			camera->GetOutput()->SetFramebufferId(0);

			/* ��� ������� ���¸� ī�޶��� ��� ���� �������� ���� */
			CHECK_RF(m_outputExecutor->Apply(camera->GetOutput(), false));

			/* ��� HUD �������� ��ȸ */
			for (const auto & renderer : m_renderers[static_cast<unsigned>(RendererType::Hud)])
			{
				/* ������Ʈ�� �������� ��Ȱ��ȭ�� ��� ���� */
				if (!renderer->GetObject()->GetIsEnabled() || !renderer->GetIsEnabled()) { continue; }

				/* �Է� ������ ���̴� ����⿡ ���� ���� �� ���� */
				CHECK_RF(m_inputExecutor->Apply(renderer->GetInput()));
				CHECK_RF(m_shaderExecutor->Apply(renderer->GetMaterial()));
				CHECK_RF(Draw());
			}

			if (camera->GetFramebuffer()) { camera->GetOutput()->SetFramebufferId(camera->GetFramebuffer()->GetId()); }
		}

		return true;
	}

	/* ������ OpenGL ���ؽ�Ʈ�� ���·� �������� �����ϴ� �Լ� */
	bool Render::Draw()
	{
		/* ������ �ε����� ���� ��� */
		if (m_inputExecutor->GetIndexCount() == 0)
		{
			/* ���ؽ� �迭�� ����Ͽ� ���� */
			GL_CHECK_RF(glDrawArrays(static_cast<unsigned>(m_inputExecutor->GetPrimitiveTopology()), 0, m_inputExecutor->GetVertexCount()));
		}
		/* ������ �ε����� ���� ��� */
		else
		{
			/* ���ؽ� �迭�� �ε��� ���۸� ����Ͽ� ���� */
			GL_CHECK_RF(glDrawElements(static_cast<unsigned>(m_inputExecutor->GetPrimitiveTopology()), m_inputExecutor->GetIndexCount(), GL_UNSIGNED_INT, nullptr));
		}

		return true;
	}

}
