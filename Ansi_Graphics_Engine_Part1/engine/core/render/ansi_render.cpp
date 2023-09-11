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

	/* 생성자 */
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

	/* 소멸자 */
	Render::~Render()
	{
		SAFE_DELETE(m_inputExecutor);
		SAFE_DELETE(m_outputExecutor);
		SAFE_DELETE(m_shaderExecutor);
	}

	/* 초기화 함수 */
	bool Render::Initialize()
	{
		/* 내장 자원 생성 */
		CHECK_RF(m_builtIn->Initialize());

		return true;
	}

	/* OpenGL 컨텍스트의 모든 상태를 초기화하는 함수 */
	bool Render::Reset()
	{
		/* 모든 실행기의 상태 초기화 */
		CHECK_RF(m_inputExecutor->Reset());
		CHECK_RF(m_outputExecutor->Reset());
		CHECK_RF(m_shaderExecutor->Reset());

		return true;
	}

	/* 매 프레임마다 호출되는 렌더링 함수 */
	bool Render::OnRender()
	{
		/* === 깊이 기록 === */

		/* 모든 광원 카메라를 순회 */
		for (const auto & camera : m_cameras[static_cast<unsigned>(CameraType::Light)])
		{
			/* 오브젝트나 카메라가 비활성화된 경우 생략 */
			if (!camera->GetObject()->GetIsEnabled() || !camera->GetIsEnabled()) { continue; }
			m_currentCamera = camera;

			/* 출력 실행기의 상태를 카메라의 출력 상태 집합으로 설정 */
			CHECK_RF(m_outputExecutor->Apply(camera->GetOutput()));

			/* 모든 일반 렌더러를 순회 */
			for (const auto & renderer : m_renderers[static_cast<unsigned>(RendererType::Normal)])
			{
				/* 오브젝트나 렌더러가 비활성화됐거나, 그림자를 생성하지 않는 경우 생략 */
				if (!renderer->GetObject()->GetIsEnabled() ||
					!renderer->GetIsEnabled() ||
					!renderer->GetIsCastShadow()) { continue; }

				/* 깊이 기록 재질의 트랜스폼을 현재 렌더러의 트랜스폼으로 설정 */
				m_builtIn->GetDepthMaterial()->SetTransform(renderer->GetObject()->GetTransform());

				/* 입력 실행기와 셰이더 실행기에 상태 적용 후 렌더 */
				CHECK_RF(m_inputExecutor->Apply(renderer->GetInput()));
				CHECK_RF(m_shaderExecutor->Apply(m_builtIn->GetDepthMaterial()));
				CHECK_RF(Draw());
			}
		}

		/* === 오브젝트 (일반) 렌더링 === */

		/* 모든 시야 카메라를 순회 */
		for (const auto & camera : m_cameras[static_cast<unsigned>(CameraType::View)])
		{
			/* 오브젝트나 카메라가 비활성화된 경우 생략 */
			if (!camera->GetObject()->GetIsEnabled() || !camera->GetIsEnabled()) { continue; }
			m_currentCamera = camera;

			/* 출력 실행기의 상태를 카메라의 출력 상태 집합으로 설정 */
			CHECK_RF(m_outputExecutor->Apply(camera->GetOutput()));

			/* 모든 일반 렌더러를 순회 */
			for (const auto & renderer : m_renderers[static_cast<unsigned>(RendererType::Normal)])
			{
				/* 오브젝트나 렌더러가 비활성화된 경우 생략 */
				if (!renderer->GetObject()->GetIsEnabled() || !renderer->GetIsEnabled()) { continue; }

				/* 입력 실행기와 셰이더 실행기에 상태 적용 후 렌더 */
				CHECK_RF(m_inputExecutor->Apply(renderer->GetInput()));
				CHECK_RF(m_shaderExecutor->Apply(renderer->GetMaterial()));
				CHECK_RF(Draw());
			}
		}

		/* === 후처리 === */

		/* 모든 시야 카메라를 순회 */
		for (const auto & camera : m_cameras[static_cast<unsigned>(CameraType::View)])
		{
			/* 오브젝트나 카메라가 비활성화되었거나 후처리 카메라가 아닌 경우 생략 */
			if (!camera->GetObject()->GetIsEnabled() || !camera->GetIsEnabled() || !camera->GetIsPostEffectCamera()) { continue; }
			m_currentCamera = camera;

			/* 모든 후처리 효과를 순회 */
			for (const auto & effect : static_cast<PostEffectCamera *>(camera)->GetEffects())
			{
				unsigned framebufferId = (effect->GetFramebuffer()) ? effect->GetFramebuffer()->GetId() : 0;
				camera->GetOutput()->SetFramebufferId(framebufferId);

				/* 출력 실행기의 상태를 카메라의 출력 상태 집합으로 설정 */
				CHECK_RF(m_outputExecutor->Apply(camera->GetOutput()));

				/* 입력 실행기와 셰이더 실행기에 상태 적용 후 렌더 */
				CHECK_RF(m_inputExecutor->Apply(m_builtIn->GetScreenAlignedQuadIP()));
				CHECK_RF(m_shaderExecutor->Apply(effect->GetMaterial()));
				CHECK_RF(Draw());
			}

			camera->GetOutput()->SetFramebufferId(camera->GetFramebuffer()->GetId());
		}

		/* === 오브젝트 (HUD) 렌더링 === */

		/* 모든 시야 카메라를 순회 */
		for (const auto & camera : m_cameras[static_cast<unsigned>(CameraType::View)])
		{
			/* 오브젝트나 카메라가 비활성화된 경우 생략 */
			if (!camera->GetObject()->GetIsEnabled() || !camera->GetIsEnabled()) { continue; }
			m_currentCamera = camera;

			camera->GetOutput()->SetFramebufferId(0);

			/* 출력 실행기의 상태를 카메라의 출력 상태 집합으로 설정 */
			CHECK_RF(m_outputExecutor->Apply(camera->GetOutput(), false));

			/* 모든 HUD 렌더러를 순회 */
			for (const auto & renderer : m_renderers[static_cast<unsigned>(RendererType::Hud)])
			{
				/* 오브젝트나 렌더러가 비활성화된 경우 생략 */
				if (!renderer->GetObject()->GetIsEnabled() || !renderer->GetIsEnabled()) { continue; }

				/* 입력 실행기와 셰이더 실행기에 상태 적용 후 렌더 */
				CHECK_RF(m_inputExecutor->Apply(renderer->GetInput()));
				CHECK_RF(m_shaderExecutor->Apply(renderer->GetMaterial()));
				CHECK_RF(Draw());
			}

			if (camera->GetFramebuffer()) { camera->GetOutput()->SetFramebufferId(camera->GetFramebuffer()->GetId()); }
		}

		return true;
	}

	/* 설정한 OpenGL 컨텍스트의 상태로 렌더링을 실행하는 함수 */
	bool Render::Draw()
	{
		/* 설정된 인덱스가 없을 경우 */
		if (m_inputExecutor->GetIndexCount() == 0)
		{
			/* 버텍스 배열만 사용하여 렌더 */
			GL_CHECK_RF(glDrawArrays(static_cast<unsigned>(m_inputExecutor->GetPrimitiveTopology()), 0, m_inputExecutor->GetVertexCount()));
		}
		/* 설정된 인덱스가 있을 경우 */
		else
		{
			/* 버텍스 배열과 인덱스 버퍼를 사용하여 렌더 */
			GL_CHECK_RF(glDrawElements(static_cast<unsigned>(m_inputExecutor->GetPrimitiveTopology()), m_inputExecutor->GetIndexCount(), GL_UNSIGNED_INT, nullptr));
		}

		return true;
	}

}
