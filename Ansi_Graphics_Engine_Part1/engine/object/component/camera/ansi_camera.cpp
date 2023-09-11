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

	/* ������ */
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
		/* ���� �����ڿ� ��� */
		Core::GetRender()->AddCamera(this, m_type);

		m_isPerspective.Set(isPerspective);
		m_zoom.Set(1.0f);
		m_fov.Set(PI * 0.25f);
		m_near.Set(1.0f);
		m_far.Set(1000.0f);
		m_lookAt.Set(glm::vec3(0.0f));

		/* â ũ�� ��� ���ο� ���� �ػ� ���� */
		SetSize((m_isUseClientSize) ? Core::GetWindow()->GetClientSize() : glm::vec2(1024.0f));
	}

	/* �Ҹ��� */
	Camera::~Camera()
	{
		/* ���� �����ڿ��� ��� ���� */
		Core::GetRender()->RemoveCamera(this, m_type);

		SAFE_DELETE(m_outputParam);
		SAFE_DELETE(m_framebuffer);
		SAFE_DELETE(m_orbitControls);
	}

	/* �� �����Ӹ��� ȣ��Ǵ� ������Ʈ �Լ� */
	bool Camera::OnUpdate()
	{
		/* �� �Ǵ� ���� ��� �� �ϳ��� ����Ǿ����� ���� (�� ���� ��� ������Ʈ �ʿ� ���� Ȯ�ο�) */
		static bool isMatrixChanged{ false };
		isMatrixChanged = false;

		/* �� ��� ������Ʈ�� Ȱ��ȭ �Ǿ��ְ�, ī�޶��� ���� ��� �Ǵ� �ٶ󺸴� ��� ��ġ�� ����Ǿ��� ��� */
		if (m_isUpdateViewMatrix && (
			GetObject()->GetTransform()->GetIsChangedMatrix() ||
			m_lookAt.Check()))
		{
			m_isChangedViewMatrix = true;
			isMatrixChanged = true;

			/* �� ��� ������Ʈ */
			UpdateViewMatrix();

			m_lookAt.Reset();
		}
		else { m_isChangedViewMatrix = false; }

		/* ���� ��� ������Ʈ�� Ȱ��ȭ �Ǿ��ְ�, ���� ��� ���� �������� �ϳ��� ����Ǿ��� ��� */
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

			/* ���� ��� ������Ʈ */
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

		/* �� �Ǵ� ���� ��� �� �ϳ��� ����Ǿ��� ���, �� ���� ��� ������Ʈ */
		if (isMatrixChanged) { m_viewProjMatrix = m_projMatrix * m_viewMatrix; }

		return true;
	}

	/* ���� �����ӹ��۸� �����ϴ� �Լ� */
	bool Camera::CreateFramebuffer(unsigned flag)
	{
		/* �����ӹ��� �ڿ� ���� */
		m_framebuffer = new Framebuffer();
		m_framebuffer->Initialize(m_width.Get(), m_height.Get(), flag);

		/* ��� ���� ���� ���տ� ���� */
		m_outputParam->SetFramebufferId(m_framebuffer->GetId());

		return true;
	}

	/* â ũ�⸦ ������ ��� ȣ��Ǵ� �Լ� */
	void Camera::OnWindowResize(const glm::vec2 & size)
	{
		/* â ũ�⿡ ���� ī�޶��� ���, �ػ� ������Ʈ (â�� �ּ�ȭ�� ���, �ػ󵵷� 0.0f�� ���޵ǹǷ� �ݿ����� ����) */
		if (m_isUseClientSize && (size.x > 0.0f) && (size.y > 0.0f))
		{
			SetSize(size);

			if (m_framebuffer) { CHECK_PRINT(m_framebuffer->UpdateSize(m_width.Get(), m_height.Get()), "[Framebuffer Error]: Resize Failed"); }
		}
	}

	/* Setter - �ػ� (�ȼ� ����) */
	void Camera::SetSize(const glm::vec2 & size)
	{
		/* �ػ󵵿� ��Ⱦ�� ���� */
		m_width.Set(size.x);
		m_height.Set(size.y);
		m_aspectRatio = m_width.Get() / m_height.Get();

		/* ��� ���� ���� ���տ� ���� */
		m_outputParam->SetViewportZ(static_cast<int>(m_width.Get()));
		m_outputParam->SetViewportW(static_cast<int>(m_height.Get()));
	}

	/* Setter - ����Ʈ ��ġ ������ (�ȼ� ����) */
	void Camera::SetOffset(const glm::ivec2 & offset)
	{
		/* ��� ���� ���� ���տ� ���� */
		m_outputParam->SetViewportX(offset.x);
		m_outputParam->SetViewportX(offset.y);
	}

	/* �� ����� ������Ʈ�ϴ� �Լ� */
	void Camera::UpdateViewMatrix()
	{
		/* ī�޶� �������� ����, ������ ���� ��� */
		m_up = GetObject()->GetTransform()->GetLookAt(glm::vec3(0.0f, 1.0f, 0.0f));
		m_right = glm::normalize(glm::cross(m_lookAt.Get() - GetObject()->GetTransform()->GetWorldPosition(), m_up));
		/* �� ��� ���� */
		m_viewMatrix = glm::lookAt(GetObject()->GetTransform()->GetWorldPosition(), m_lookAt.Get(), m_up);
	}

	/* ���� ����� ������Ʈ�ϴ� �Լ� */
	void Camera::UpdateProjMatrix()
	{
		if (m_isPerspective.Get())
		{
			/* ���� ���� ��� ���� */
			m_projMatrix = glm::perspective(m_fov.Get(), m_aspectRatio, m_near.Get(), m_far.Get());
		}
		else
		{
			/* ���� ���� ��� ���� */
			float halfWidth{ m_width.Get() * 0.5f / m_zoom.Get() };
			float halfHeight{ m_height.Get() * 0.5f / m_zoom.Get() };
			m_projMatrix = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, -m_far.Get(), m_far.Get());
		}
	}

}