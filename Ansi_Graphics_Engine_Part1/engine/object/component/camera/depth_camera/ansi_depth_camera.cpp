#include "ansi_depth_camera.h"

#include "resource/framebuffer/ansi_framebuffer.h"
#include "resource/texture/ansi_texture.h"
#include "object/ansi_object.h"
#include "object/component/transform/ansi_transform.h"

namespace ansi
{

	/* ������ */
	DepthCamera::DepthCamera(Object * object)
		: Camera(object, CameraType::Light, false, false)
	{
		SetFar(GetFar() * 0.5f);
	}

	/* �� �����Ӹ��� ȣ��Ǵ� ������Ʈ �Լ� */
	bool DepthCamera::OnUpdate()
	{
		/* �̹� �����ӿ� ���� ����� ����Ǿ��� ��� */
		if (GetObject()->GetTransform()->GetIsChangedMatrix())
		{
			/* ȸ���� ���� �����ִ� ��� ��ġ ������Ʈ */
			SetLookAt(GetObject()->GetTransform()->GetWorldPosition() + GetObject()->GetTransform()->GetLookAt());
		}

		/* �⺻ ������Ʈ �Լ� ȣ�� */
		CHECK_RF(Camera::OnUpdate());

		return true;
	}

}
