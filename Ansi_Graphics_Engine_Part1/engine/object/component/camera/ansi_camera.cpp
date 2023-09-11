#include "ansi_camera.h"

#include "core/window/ansi_window.h"
#include "core/render/ansi_render.h"
#include "core/render/output_executor/output_param/ansi_output_param.h"
#include "resource/framebuffer/ansi_framebuffer.h"
#include "resource/texture/ansi_texture.h"
#include "object/ansi_object.h"
#include "object/component/transform/ansi_transform.h"
#include "utility/orbit_controls/ansi_orbit_controls.h"

namespace ansi
{

	/* 생성자 */
	Camera::Camera(Object * object, CameraType type, bool isUseClientSize, bool isPerspective)
		: Component(object)
		, m_isUseClientSize(isUseClientSize)
		, m_isPostEffectCamera(false)
		, m_isUpdateViewMatrix(true)
		, m_isUpdateProjMatrix(true)
		, m_isChangedViewMatrix(false)
		, m_isChangedProjMatrix(false)
		, m_aspectRatio(0.0f)
		, m_type(type)
		, m_viewportOffset(0)
		, m_up(0.0f, 1.0f, 0.0f)
		, m_right(1.0f, 0.0f, 0.0f)
		, m_viewMatrix(1.0f)
		, m_projMatrix(1.0f)
		, m_viewProjMatrix(1.0f)
		, m_outputParam(new OutputParam())
		, m_framebuffer(nullptr)
		, m_orbitControls(nullptr)
	{
		/* 렌더 관리자에 등록 */
		Core::GetRender()->AddCamera(this, m_type);

		m_isPerspective.Set(isPerspective);
		m_zoom.Set(1.0f);
		m_fov.Set(PI * 0.25f);
		m_near.Set(1.0f);
		m_far.Set(1000.0f);
		m_lookAt.Set(glm::vec3(0.0f));

		/* 창 크기 사용 여부에 따라 해상도 설정 */
		SetSize((m_isUseClientSize) ? Core::GetWindow()->GetClientSize() : glm::vec2(1024.0f));
	}

	/* 소멸자 */
	Camera::~Camera()
	{
		/* 렌더 관리자에서 등록 해제 */
		Core::GetRender()->RemoveCamera(this, m_type);

		SAFE_DELETE(m_outputParam);
		SAFE_DELETE(m_framebuffer);
		SAFE_DELETE(m_orbitControls);
	}

	/* 매 프레임마다 호출되는 업데이트 함수 */
	bool Camera::OnUpdate()
	{
		/* 뷰 또는 투영 행렬 중 하나라도 변경되었는지 여부 (뷰 투영 행렬 업데이트 필요 여부 확인용) */
		static bool isMatrixChanged{ false };
		isMatrixChanged = false;

		/* 뷰 행렬 업데이트가 활성화 되어있고, 카메라의 월드 행렬 또는 바라보는 대상 위치가 변경되었을 경우 */
		if (m_isUpdateViewMatrix && (
			GetObject()->GetTransform()->GetIsChangedMatrix() ||
			m_lookAt.Check()))
		{
			m_isChangedViewMatrix = true;
			isMatrixChanged = true;

			/* 뷰 행렬 업데이트 */
			UpdateViewMatrix();

			m_lookAt.Reset();
		}
		else { m_isChangedViewMatrix = false; }

		/* 투영 행렬 업데이트가 활성화 되어있고, 투영 행렬 관련 변수들이 하나라도 변경되었을 경우 */
		if (m_isUpdateProjMatrix && (
			m_isPerspective.Check() ||
			m_zoom.Check() ||
			m_fov.Check() ||
			m_near.Check() ||
			m_far.Check() ||
			m_width.Check() ||
			m_height.Check()))
		{
			m_isChangedProjMatrix = true;
			isMatrixChanged = true;

			/* 투영 행렬 업데이트 */
			UpdateProjMatrix();

			m_isPerspective.Reset();
			m_zoom.Reset();
			m_fov.Reset();
			m_near.Reset();
			m_far.Reset();
			m_width.Reset();
			m_height.Reset();
		}
		else { m_isChangedProjMatrix = false; }

		/* 뷰 또는 투영 행렬 중 하나라도 변경되었을 경우, 뷰 투영 행렬 업데이트 */
		if (isMatrixChanged) { m_viewProjMatrix = m_projMatrix * m_viewMatrix; }

		return true;
	}

	/* 전용 프레임버퍼를 생성하는 함수 */
	bool Camera::CreateFramebuffer(unsigned flag)
	{
		/* 프레임버퍼 자원 생성 */
		m_framebuffer = new Framebuffer();
		m_framebuffer->Initialize(m_width.Get(), m_height.Get(), flag);

		/* 출력 관련 상태 집합에 설정 */
		m_outputParam->SetFramebufferId(m_framebuffer->GetId());

		return true;
	}

	/* 창 크기를 변경할 경우 호출되는 함수 */
	void Camera::OnWindowResize(const glm::vec2 & size)
	{
		/* 창 크기에 맞춘 카메라일 경우, 해상도 업데이트 (창이 최소화된 경우, 해상도로 0.0f가 전달되므로 반영하지 않음) */
		if (m_isUseClientSize && (size.x > 0.0f) && (size.y > 0.0f))
		{
			SetSize(size);

			if (m_framebuffer) { CHECK_PRINT(m_framebuffer->UpdateSize(m_width.Get(), m_height.Get()), "[Framebuffer Error]: Resize Failed"); }
		}
	}

	/* Setter - 해상도 (픽셀 단위) */
	void Camera::SetSize(const glm::vec2 & size)
	{
		/* 해상도와 종횡비 설정 */
		m_width.Set(size.x);
		m_height.Set(size.y);
		m_aspectRatio = m_width.Get() / m_height.Get();

		/* 출력 관련 상태 집합에 설정 */
		m_outputParam->SetViewportZ(static_cast<int>(m_width.Get()));
		m_outputParam->SetViewportW(static_cast<int>(m_height.Get()));
	}

	/* Setter - 뷰포트 위치 오프셋 (픽셀 단위) */
	void Camera::SetOffset(const glm::ivec2 & offset)
	{
		/* 출력 관련 상태 집합에 설정 */
		m_outputParam->SetViewportX(offset.x);
		m_outputParam->SetViewportX(offset.y);
	}

	/* 뷰 행렬을 업데이트하는 함수 */
	void Camera::UpdateViewMatrix()
	{
		/* 카메라를 기준으로 위쪽, 오른쪽 방향 계산 */
		m_up = GetObject()->GetTransform()->GetLookAt(glm::vec3(0.0f, 1.0f, 0.0f));
		m_right = glm::normalize(glm::cross(m_lookAt.Get() - GetObject()->GetTransform()->GetWorldPosition(), m_up));
		/* 뷰 행렬 생성 */
		m_viewMatrix = glm::lookAt(GetObject()->GetTransform()->GetWorldPosition(), m_lookAt.Get(), m_up);
	}

	/* 투영 행렬을 업데이트하는 함수 */
	void Camera::UpdateProjMatrix()
	{
		if (m_isPerspective.Get())
		{
			/* 원근 투영 행렬 생성 */
			m_projMatrix = glm::perspective(m_fov.Get(), m_aspectRatio, m_near.Get(), m_far.Get());
		}
		else
		{
			/* 직교 투영 행렬 생성 */
			float halfWidth{ m_width.Get() * 0.5f / m_zoom.Get() };
			float halfHeight{ m_height.Get() * 0.5f / m_zoom.Get() };
			m_projMatrix = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, -m_far.Get(), m_far.Get());
		}
	}

}