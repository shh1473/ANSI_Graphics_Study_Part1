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

		/* �ʱ�ȭ �Լ� */
		bool Initialize();

		PostEffect * AddEffect(PostEffect * effect, bool isCreateFramebuffer = false);

		/* Getter - ��ó�� ȿ�� �迭 */
		const std::vector<PostEffect *> & GetEffects() const { return m_effects; }

	protected:
		/* â ũ�⸦ ������ ��� ȣ��Ǵ� �Լ� */
		void OnWindowResize(const glm::vec2 & size) override;

	private:
		/* ��ó�� ȿ�� �迭 */
		std::vector<PostEffect *> m_effects;

	};

}
