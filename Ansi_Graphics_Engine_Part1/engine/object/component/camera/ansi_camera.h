#pragma once

#include "common/ansi_common_render.h"
#include "core/render/output_executor/output_param/ansi_output_param.h"
#include "object/component/ansi_component.h"
#include "utility/event_listener/ansi_event_listener.h"
#include "utility/state_checker/ansi_state_checker_math.h"

namespace ansi
{

	/* ���� ���� */
	class OutputParam;
	class Framebuffer;
	class Texture;
	class OrbitControls;

	/* ī�޶� ������Ʈ Ŭ���� */
	class Camera : public Component, public EventListener
	{
	public:
		/* ������
		* @param object - �Ҽӵ� ������Ʈ
		* @param type - ī�޶� ���� (�⺻: �þ� ī�޶�)
		* @param isUseClientSize - â ũ�⸦ �þ� ������ ����� �� ���� (�⺻: true)
		* @param isPerspective - ���ٰ� Ȱ��ȭ ���� (�⺻: true)
		*/
		explicit Camera(Object * object, CameraType type = CameraType::View, bool isUseClientSize = true, bool isPerspective = true);
		/* �Ҹ��� */
		virtual ~Camera();

		/* �� �����Ӹ��� ȣ��Ǵ� ������Ʈ �Լ� */
		bool OnUpdate() override;

		/* ���� �����ӹ��۸� �����ϴ� �Լ�
		* @param flag - �����ӹ��� ���� �÷��� (�⺻: {����} | {����})
		*/
		bool CreateFramebuffer(unsigned flag = FB_COLOR | FB_DEPTH);

		/* Setter - ��ó�� ȿ�� ī�޶����� ���� */
		void SetIsPostEffectCamera(bool isPostEffectCamera) { m_isPostEffectCamera = isPostEffectCamera; }
		/* Setter - ���ٰ� Ȱ��ȭ ���� */
		void SetIsPerspective(bool isPerspective) { m_isPerspective.Set(isPerspective); }
		/* Setter - �� */
		void SetZoom(float zoom) { m_zoom.Set(zoom); }
		/* Setter - �þ߰� */
		void SetFov(float fov) { m_fov.Set(fov); }
		/* Setter - �þ��� �ּ� �Ÿ� */
		void SetNear(float nearZ) { m_near.Set(nearZ); }
		/* Setter - �þ��� �ִ� �Ÿ� */
		void SetFar(float farZ) { m_far.Set(farZ); }
		/* Setter - �ػ� (�ȼ� ����) */
		void SetSize(const glm::vec2 & size);
		/* Setter - ����Ʈ ��ġ ������ (�ȼ� ����) */
		void SetOffset(const glm::ivec2 & offset);
		/* Setter - �ٶ󺸰� �ִ� ��� ��ġ */
		void SetLookAt(const glm::vec3 & lookAt) { m_lookAt.Set(lookAt); }
		/* Setter - �˵��� ��Ʈ�ѷ� */
		void SetOrbitControls(OrbitControls * orbitControls) { m_orbitControls = orbitControls; }

		/* Getter - â ũ�⸦ �þ� ������ ����� �� ���� */
		bool GetIsUseClientSize() const { return m_isUseClientSize; }
		/* Getter - ��ó�� ȿ�� ī�޶����� ���� */
		bool GetIsPostEffectCamera() const { return m_isPostEffectCamera; }
		/* Getter - ���ٰ� Ȱ��ȭ ���� */
		bool GetIsPerspective() const { return m_isPerspective.Get(); }
		/* Getter - �̹� �����ӿ� �� ����� ����Ǿ����� ���� */
		bool GetIsChangedViewMatrix() const { return m_isChangedViewMatrix; }
		/* Getter - �̹� �����ӿ� ���� ����� ����Ǿ����� ���� */
		bool GetIsChangedProjMatrix() const { return m_isChangedProjMatrix; }
		/* Getter - ī�޶� ���� */
		CameraType GetType() const { return m_type; }
		/* Getter - ���� ���� */
		const glm::vec3 & GetUp() const { return m_up; }
		/* Getter - ������ ���� */
		const glm::vec3 & GetRight() const { return m_right; }
		/* Getter - �� ��� */
		const glm::mat4 & GetViewMatrix() const { return m_viewMatrix; }
		/* Getter - ���� ��� */
		const glm::mat4 & GetProjMatrix() const { return m_projMatrix; }
		/* Getter - �� ���� ��� */
		const glm::mat4 & GetViewProjMatrix() const { return m_viewProjMatrix; }
		/* Getter - �� */
		float GetZoom() const { return m_zoom.Get(); }
		/* Getter - �þ߰� */
		float GetFov() const { return m_fov.Get(); }
		/* Getter - ��Ⱦ�� */
		float GetAspectRatio() const { return m_aspectRatio; }
		/* Getter - �þ��� �ּ� �Ÿ� */
		float GetNear() const { return m_near.Get(); }
		/* Getter - �þ��� �ִ� �Ÿ� */
		float GetFar() const { return m_far.Get(); }
		/* Getter - ���� �ػ� (�ȼ� ����) */
		float GetWidth() const { return m_width.Get(); }
		/* Getter - ���� �ػ� (�ȼ� ����) */
		float GetHeight() const { return m_height.Get(); }
		/* Getter - �ػ� (�ȼ� ����) */
		glm::vec2 GetSize() const { return glm::vec2(m_width.Get(), m_height.Get()); }
		/* Getter - �ٶ󺸰� �ִ� ��� ��ġ */
		const glm::vec3 & GetLookAt() const { return m_lookAt.Get(); }
		/* Getter - ��� ���� ���� ���� */
		OutputParam * GetOutput() const { return m_outputParam; }
		/* Getter - ���� �����ӹ��� */
		Framebuffer * GetFramebuffer() const { return m_framebuffer; }
		
	protected:
		/* â ũ�⸦ ������ ��� ȣ��Ǵ� �Լ� */
		void OnWindowResize(const glm::vec2 & size) override;

	private:
		/* �� ����� ������Ʈ�ϴ� �Լ� */
		void UpdateViewMatrix();
		/* ���� ����� ������Ʈ�ϴ� �Լ� */
		void UpdateProjMatrix();

	private:
		/* â ũ�⸦ �þ� ������ ����� �� ���� */
		bool m_isUseClientSize;
		/* ��ó�� ȿ�� ī�޶����� ���� */
		bool m_isPostEffectCamera;
		/* �� ����� ������Ʈ�� ������ ���� */
		bool m_isUpdateViewMatrix;
		/* ���� ����� ������Ʈ�� ������ ���� */
		bool m_isUpdateProjMatrix;
		/* �̹� �����ӿ� �� ����� ����Ǿ����� ���� */
		bool m_isChangedViewMatrix;
		/* �̹� �����ӿ� ���� ����� ����Ǿ����� ���� */
		bool m_isChangedProjMatrix;
		/* ��Ⱦ�� */
		float m_aspectRatio;
		/* ī�޶� ���� */
		const CameraType m_type;
		/* ����Ʈ ��ġ ������ (�ȼ� ����) */
		glm::ivec2 m_viewportOffset;
		/* ���� ���� */
		glm::vec3 m_up;
		/* ������ ���� */
		glm::vec3 m_right;
		/* �� ��� */
		glm::mat4 m_viewMatrix;
		/* ���� ��� */
		glm::mat4 m_projMatrix;
		/* �� ���� ��� */
		glm::mat4 m_viewProjMatrix;
		/* ���ٰ� Ȱ��ȭ ���� (���� �˻�) */
		StateChecker<bool> m_isPerspective;
		/* �� (���� �˻�) */
		StateChecker<float> m_zoom;
		/* �þ߰� (���� �˻�) */
		StateChecker<float> m_fov;
		/* �þ��� �ּ� �Ÿ� (���� �˻�) */
		StateChecker<float> m_near;
		/* �þ��� �ִ� �Ÿ� (���� �˻�) */
		StateChecker<float> m_far;
		/* ���� �ػ� (���� �˻�) */
		StateChecker<float> m_width;
		/* ���� �ػ� (���� �˻�) */
		StateChecker<float> m_height;
		/* �ٶ󺸰� �ִ� ��� ��ġ (���� �˻�) */
		StateCheckerVec3 m_lookAt;
		/* ��� ���� ���� ���� */
		OutputParam * m_outputParam;
		/* ���� �����ӹ��� */
		Framebuffer * m_framebuffer;
		/* �˵��� ��Ʈ�ѷ� */
		OrbitControls * m_orbitControls;

	};

}
