#include "ansi_directional_light.h"

#include "object/component/camera/depth_camera/ansi_depth_camera.h"

namespace ansi
{

	/* 생성자 */
	DirectionalLight::DirectionalLight(Object * object, const glm::vec3 & color)
		: Component(object)
		, m_color(color)
		, m_depthMapCamera(nullptr)
	{

	}

	/* 소멸자 */
	DirectionalLight::~DirectionalLight()
	{
		SAFE_DELETE(m_depthMapCamera);
	}

	/* 매 프레임마다 호출되는 업데이트 함수 */
	bool DirectionalLight::OnUpdate()
	{
		/* 깊이 카메라가 없을 경우(그림자를 생성하지 않을 경우) 중단 */
		if (!m_depthMapCamera) { return true; }

		/* 깊이 카메라 업데이트 */
		CHECK_RF(m_depthMapCamera->OnUpdate());

		return true;
	}

	/* 그림자 생성을 위한 준비(프레임버퍼, 깊이 텍스처 생성)를 하는 함수 */
	bool DirectionalLight::CastShadow(float resolution)
	{
		/* 이미 깊이 카메라가 존재할 경우(본 함수를 중복 호출했을 경우) 중단 */
		CHECK_PRINT_RF(!m_depthMapCamera, "[Light Error]: Duplicated Call");

		/* 깊이 카메라 생성 */
		m_depthMapCamera = new DepthCamera(GetObject());
		m_depthMapCamera->SetSize(glm::vec2(resolution));

		/* 깊이 텍스처를 장착한 전용 프레임버퍼 생성 */
		CHECK_RF(m_depthMapCamera->CreateFramebuffer(FB_DEPTH));

		return true;
	}

}
