#pragma once

#include "object/component/camera/ansi_camera.h"
#include "object/component/camera/post_effect_camera/ansi_post_effect.h"

namespace ansi
{

	class Framebuffer;

	class PostEffectCamera : public Camera
	{
	public:
		explicit PostEffectCamera(Object * object, bool isUseClientSize = true);
		virtual ~PostEffectCamera();

		/* 초기화 함수 */
		bool Initialize();

		PostEffect * AddEffect(PostEffect * effect, bool isCreateFramebuffer = false);

		/* Getter - 후처리 효과 배열 */
		const std::vector<PostEffect *> & GetEffects() const { return m_effects; }

	protected:
		/* 창 크기를 변경할 경우 호출되는 함수 */
		void OnWindowResize(const glm::vec2 & size) override;

	private:
		/* 후처리 효과 배열 */
		std::vector<PostEffect *> m_effects;

	};

}
