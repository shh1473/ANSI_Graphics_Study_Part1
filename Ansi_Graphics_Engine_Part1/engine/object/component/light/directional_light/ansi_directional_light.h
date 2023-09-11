#pragma once

#include "object/component/ansi_component.h"

namespace ansi
{

	/* 전방 선언 */
	class DepthCamera;

	/* 디렉셔널 라이트 컴포넌트 클래스 */
	class DirectionalLight : public Component
	{
	public:
		/* 생성자 */
		explicit DirectionalLight(Object * object, const glm::vec3 & color = glm::vec3(1.0f));
		/* 소멸자 */
		virtual ~DirectionalLight();

		/* 매 프레임마다 호출되는 업데이트 함수 */
		bool OnUpdate() override;

		/* 그림자 생성을 위한 준비(프레임버퍼, 깊이 텍스처 생성)를 하는 함수
		* @param resolution - 깊이 텍스처 해상도 (기본: 1024.0f)
		*/
		bool CastShadow(float resolution = 1024.0f);

		/* Setter - 색상 */
		void SetColor(const glm::vec3 & color) { m_color = color; }

		/* Getter - 색상 */
		const glm::vec3 & GetColor() const { return m_color; }
		/* Getter - 깊이 카메라 */
		DepthCamera * GetDepthMapCamera() { return m_depthMapCamera; }

	private:
		/* 색상 */
		glm::vec3 m_color;
		/* 깊이 카메라 */
		DepthCamera * m_depthMapCamera;

	};

}
