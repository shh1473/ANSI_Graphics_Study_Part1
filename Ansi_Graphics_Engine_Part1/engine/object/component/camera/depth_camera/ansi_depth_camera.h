#pragma once

#include "object/component/camera/ansi_camera.h"

namespace ansi
{

	/* 깊이 기록 카메라 컴포넌트 클래스 */
	class DepthCamera : public Camera
	{
	public:
		/* 생성자
		* @param object - 소유자 오브젝트
		*/
		explicit DepthCamera(Object * object);

		/* 매 프레임마다 호출되는 업데이트 함수 */
		bool OnUpdate() override;

	};

}
