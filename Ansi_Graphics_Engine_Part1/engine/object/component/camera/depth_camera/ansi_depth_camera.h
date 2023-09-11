#pragma once

#include "object/component/camera/ansi_camera.h"

namespace ansi
{

	/* ���� ��� ī�޶� ������Ʈ Ŭ���� */
	class DepthCamera : public Camera
	{
	public:
		/* ������
		* @param object - ������ ������Ʈ
		*/
		explicit DepthCamera(Object * object);

		/* �� �����Ӹ��� ȣ��Ǵ� ������Ʈ �Լ� */
		bool OnUpdate() override;

	};

}
