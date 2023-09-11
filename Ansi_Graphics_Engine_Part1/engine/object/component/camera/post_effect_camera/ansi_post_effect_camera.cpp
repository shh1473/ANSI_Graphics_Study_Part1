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

		/* 창 크기에 맞춘 카메라일 경우, 해상도 업데이트 (창이 최소화된 경우, 해상도로 0.0f가 전달되므로 반영하지 않음) */
		if (GetIsUseClientSize() && (size.x > 0.0f) && (size.y > 0.0f))
		{
			/* 후처리 효과들의 프레임버퍼 업데이트 */
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
