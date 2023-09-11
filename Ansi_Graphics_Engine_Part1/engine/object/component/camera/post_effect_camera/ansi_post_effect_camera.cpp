#include "ansi_post_effect_camera.h"

#include "resource/framebuffer/ansi_framebuffer.h"

namespace ansi
{

	PostEffectCamera::PostEffectCamera(Object * object, bool isUseClientSize)
		: Camera(object, CameraType::View, isUseClientSize)
	{
		SetIsPostEffectCamera(true);
	}

	PostEffectCamera::~PostEffectCamera()
	{
		for (unsigned i{ 0 }; i < m_effects.size(); ++i) { SAFE_DELETE(m_effects[i]); }
	}

	bool PostEffectCamera::Initialize()
	{
		return CreateFramebuffer();
	}

	PostEffect * PostEffectCamera::AddEffect(PostEffect * effect, bool isCreateFramebuffer)
	{
		m_effects.push_back(effect);
		if (isCreateFramebuffer) { effect->CreateFramebuffer(GetWidth(), GetHeight()); }

		return effect;
	}

	void PostEffectCamera::OnWindowResize(const glm::vec2 & size)
	{
		Camera::OnWindowResize(size);

		/* â ũ�⿡ ���� ī�޶��� ���, �ػ� ������Ʈ (â�� �ּ�ȭ�� ���, �ػ󵵷� 0.0f�� ���޵ǹǷ� �ݿ����� ����) */
		if (GetIsUseClientSize() && (size.x > 0.0f) && (size.y > 0.0f))
		{
			/* ��ó�� ȿ������ �����ӹ��� ������Ʈ */
			for (unsigned i{ 0 }; i < m_effects.size(); ++i)
			{
				if (m_effects[i]->GetFramebuffer())
				{
					m_effects[i]->GetFramebuffer()->UpdateSize(GetWidth(), GetHeight());
				}
			}
		}
	}

}
