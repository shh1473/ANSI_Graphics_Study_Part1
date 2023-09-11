#pragma once

#include "common/ansi_common_render.h"
#include "core/render/output_executor/output_param/ansi_output_param.h"
#include "object/component/ansi_component.h"
#include "utility/event_listener/ansi_event_listener.h"
#include "utility/state_checker/ansi_state_checker_math.h"

namespace ansi
{

	/* 전방 선언 */
	class OutputParam;
	class Framebuffer;
	class Texture;
	class OrbitControls;

	/* 카메라 컴포넌트 클래스 */
	class Camera : public Component, public EventListener
	{
	public:
		/* 생성자
		* @param object - 소속된 오브젝트
		* @param type - 카메라 종류 (기본: 시야 카메라)
		* @param isUseClientSize - 창 크기를 시야 범위로 사용할 지 여부 (기본: true)
		* @param isPerspective - 원근감 활성화 여부 (기본: true)
		*/
		explicit Camera(Object * object, CameraType type = CameraType::View, bool isUseClientSize = true, bool isPerspective = true);
		/* 소멸자 */
		virtual ~Camera();

		/* 매 프레임마다 호출되는 업데이트 함수 */
		bool OnUpdate() override;

		/* 전용 프레임버퍼를 생성하는 함수
		* @param flag - 프레임버퍼 장착 플래그 (기본: {색상} | {깊이})
		*/
		bool CreateFramebuffer(unsigned flag = FB_COLOR | FB_DEPTH);

		/* Setter - 후처리 효과 카메라인지 여부 */
		void SetIsPostEffectCamera(bool isPostEffectCamera) { m_isPostEffectCamera = isPostEffectCamera; }
		/* Setter - 원근감 활성화 여부 */
		void SetIsPerspective(bool isPerspective) { m_isPerspective.Set(isPerspective); }
		/* Setter - 줌 */
		void SetZoom(float zoom) { m_zoom.Set(zoom); }
		/* Setter - 시야각 */
		void SetFov(float fov) { m_fov.Set(fov); }
		/* Setter - 시야의 최소 거리 */
		void SetNear(float nearZ) { m_near.Set(nearZ); }
		/* Setter - 시야의 최대 거리 */
		void SetFar(float farZ) { m_far.Set(farZ); }
		/* Setter - 해상도 (픽셀 단위) */
		void SetSize(const glm::vec2 & size);
		/* Setter - 뷰포트 위치 오프셋 (픽셀 단위) */
		void SetOffset(const glm::ivec2 & offset);
		/* Setter - 바라보고 있는 대상 위치 */
		void SetLookAt(const glm::vec3 & lookAt) { m_lookAt.Set(lookAt); }
		/* Setter - 궤도형 컨트롤러 */
		void SetOrbitControls(OrbitControls * orbitControls) { m_orbitControls = orbitControls; }

		/* Getter - 창 크기를 시야 범위로 사용할 지 여부 */
		bool GetIsUseClientSize() const { return m_isUseClientSize; }
		/* Getter - 후처리 효과 카메라인지 여부 */
		bool GetIsPostEffectCamera() const { return m_isPostEffectCamera; }
		/* Getter - 원근감 활성화 여부 */
		bool GetIsPerspective() const { return m_isPerspective.Get(); }
		/* Getter - 이번 프레임에 뷰 행렬이 변경되었는지 여부 */
		bool GetIsChangedViewMatrix() const { return m_isChangedViewMatrix; }
		/* Getter - 이번 프레임에 투영 행렬이 변경되었는지 여부 */
		bool GetIsChangedProjMatrix() const { return m_isChangedProjMatrix; }
		/* Getter - 카메라 종류 */
		CameraType GetType() const { return m_type; }
		/* Getter - 위쪽 방향 */
		const glm::vec3 & GetUp() const { return m_up; }
		/* Getter - 오른쪽 방향 */
		const glm::vec3 & GetRight() const { return m_right; }
		/* Getter - 뷰 행렬 */
		const glm::mat4 & GetViewMatrix() const { return m_viewMatrix; }
		/* Getter - 투영 행렬 */
		const glm::mat4 & GetProjMatrix() const { return m_projMatrix; }
		/* Getter - 뷰 투영 행렬 */
		const glm::mat4 & GetViewProjMatrix() const { return m_viewProjMatrix; }
		/* Getter - 줌 */
		float GetZoom() const { return m_zoom.Get(); }
		/* Getter - 시야각 */
		float GetFov() const { return m_fov.Get(); }
		/* Getter - 종횡비 */
		float GetAspectRatio() const { return m_aspectRatio; }
		/* Getter - 시야의 최소 거리 */
		float GetNear() const { return m_near.Get(); }
		/* Getter - 시야의 최대 거리 */
		float GetFar() const { return m_far.Get(); }
		/* Getter - 가로 해상도 (픽셀 단위) */
		float GetWidth() const { return m_width.Get(); }
		/* Getter - 세로 해상도 (픽셀 단위) */
		float GetHeight() const { return m_height.Get(); }
		/* Getter - 해상도 (픽셀 단위) */
		glm::vec2 GetSize() const { return glm::vec2(m_width.Get(), m_height.Get()); }
		/* Getter - 바라보고 있는 대상 위치 */
		const glm::vec3 & GetLookAt() const { return m_lookAt.Get(); }
		/* Getter - 출력 관련 상태 집합 */
		OutputParam * GetOutput() const { return m_outputParam; }
		/* Getter - 전용 프레임버퍼 */
		Framebuffer * GetFramebuffer() const { return m_framebuffer; }
		
	protected:
		/* 창 크기를 변경할 경우 호출되는 함수 */
		void OnWindowResize(const glm::vec2 & size) override;

	private:
		/* 뷰 행렬을 업데이트하는 함수 */
		void UpdateViewMatrix();
		/* 투영 행렬을 업데이트하는 함수 */
		void UpdateProjMatrix();

	private:
		/* 창 크기를 시야 범위로 사용할 지 여부 */
		bool m_isUseClientSize;
		/* 후처리 효과 카메라인지 여부 */
		bool m_isPostEffectCamera;
		/* 뷰 행렬을 업데이트할 것인지 여부 */
		bool m_isUpdateViewMatrix;
		/* 투영 행렬을 업데이트할 것인지 여부 */
		bool m_isUpdateProjMatrix;
		/* 이번 프레임에 뷰 행렬이 변경되었는지 여부 */
		bool m_isChangedViewMatrix;
		/* 이번 프레임에 투영 행렬이 변경되었는지 여부 */
		bool m_isChangedProjMatrix;
		/* 종횡비 */
		float m_aspectRatio;
		/* 카메라 종류 */
		const CameraType m_type;
		/* 뷰포트 위치 오프셋 (픽셀 단위) */
		glm::ivec2 m_viewportOffset;
		/* 위쪽 방향 */
		glm::vec3 m_up;
		/* 오른쪽 방향 */
		glm::vec3 m_right;
		/* 뷰 행렬 */
		glm::mat4 m_viewMatrix;
		/* 투영 행렬 */
		glm::mat4 m_projMatrix;
		/* 뷰 투영 행렬 */
		glm::mat4 m_viewProjMatrix;
		/* 원근감 활성화 여부 (상태 검사) */
		StateChecker<bool> m_isPerspective;
		/* 줌 (상태 검사) */
		StateChecker<float> m_zoom;
		/* 시야각 (상태 검사) */
		StateChecker<float> m_fov;
		/* 시야의 최소 거리 (상태 검사) */
		StateChecker<float> m_near;
		/* 시야의 최대 거리 (상태 검사) */
		StateChecker<float> m_far;
		/* 가로 해상도 (상태 검사) */
		StateChecker<float> m_width;
		/* 세로 해상도 (상태 검사) */
		StateChecker<float> m_height;
		/* 바라보고 있는 대상 위치 (상태 검사) */
		StateCheckerVec3 m_lookAt;
		/* 출력 관련 상태 집합 */
		OutputParam * m_outputParam;
		/* 전용 프레임버퍼 */
		Framebuffer * m_framebuffer;
		/* 궤도형 컨트롤러 */
		OrbitControls * m_orbitControls;

	};

}
