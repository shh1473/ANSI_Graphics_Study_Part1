#include "ansi_directional_light.h"

#include "object/component/camera/depth_camera/ansi_depth_camera.h"

namespace ansi
{

	/* ������ */
	DirectionalLight::DirectionalLight(Object * object, const glm::vec3 & color)
		: Component(object)
		, m_color(color)
		, m_depthMapCamera(nullptr)
	{

	}

	/* �Ҹ��� */
	DirectionalLight::~DirectionalLight()
	{
		SAFE_DELETE(m_depthMapCamera);
	}

	/* �� �����Ӹ��� ȣ��Ǵ� ������Ʈ �Լ� */
	bool DirectionalLight::OnUpdate()
	{
		/* ���� ī�޶� ���� ���(�׸��ڸ� �������� ���� ���) �ߴ� */
		if (!m_depthMapCamera) { return true; }

		/* ���� ī�޶� ������Ʈ */
		CHECK_RF(m_depthMapCamera->OnUpdate());

		return true;
	}

	/* �׸��� ������ ���� �غ�(�����ӹ���, ���� �ؽ�ó ����)�� �ϴ� �Լ� */
	bool DirectionalLight::CastShadow(float resolution)
	{
		/* �̹� ���� ī�޶� ������ ���(�� �Լ��� �ߺ� ȣ������ ���) �ߴ� */
		CHECK_PRINT_RF(!m_depthMapCamera, "[Light Error]: Duplicated Call");

		/* ���� ī�޶� ���� */
		m_depthMapCamera = new DepthCamera(GetObject());
		m_depthMapCamera->SetSize(glm::vec2(resolution));

		/* ���� �ؽ�ó�� ������ ���� �����ӹ��� ���� */
		CHECK_RF(m_depthMapCamera->CreateFramebuffer(FB_DEPTH));

		return true;
	}

}
