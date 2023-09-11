#include "ansi_depth_camera.h"

#include "resource/framebuffer/ansi_framebuffer.h"
#include "resource/texture/ansi_texture.h"
#include "object/ansi_object.h"
#include "object/component/transform/ansi_transform.h"

namespace ansi
{

	/* 생성자 */
	DepthCamera::DepthCamera(Object * object)
		: Camera(object, CameraType::Light, false, false)
	{
		SetFar(GetFar() * 0.5f);
	}

	/* 매 프레임마다 호출되는 업데이트 함수 */
	bool DepthCamera::OnUpdate()
	{
		/* 이번 프레임에 월드 행렬이 변경되었을 경우 */
		if (GetObject()->GetTransform()->GetIsChangedMatrix())
		{
			/* 회전에 따라 보고있는 대상 위치 업데이트 */
			SetLookAt(GetObject()->GetTransform()->GetWorldPosition() + GetObject()->GetTransform()->GetLookAt());
		}

		/* 기본 업데이트 함수 호출 */
		CHECK_RF(Camera::OnUpdate());

		return true;
	}

}
