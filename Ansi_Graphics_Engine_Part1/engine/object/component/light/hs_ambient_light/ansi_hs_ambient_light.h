#pragma once

#include "object/component/ansi_component.h"

namespace ansi
{

	/* 반구형 앰비언트 라이트 컴포넌트 클래스 */
	class HSAmbientLight : public Component
	{
	public:
		/* 생성자
		* @param object - 소유자 오브젝트
		* @param upColor - 위쪽 색상
		* @param downColor - 아래쪽 색상
		*/
		explicit HSAmbientLight(Object * object, const glm::vec3 & upColor = glm::vec3(1.0f), const glm::vec3 & downColor = glm::vec3(1.0f));

		/* Setter - 위쪽 색상 */
		void SetUpColor(const glm::vec3 & color) { m_upColor = color; m_colorRange = m_upColor - m_downColor; }
		/* Setter - 아래쪽 색상 */
		void SetDownColor(const glm::vec3 & color) { m_downColor = color; m_colorRange = m_upColor - m_downColor; }

		/* Getter - 아래쪽 색상 */
		const glm::vec3 & GetDownColor() const { return m_downColor; }
		/* Getter - 색상 범위 ({위쪽 색상} - {아래쪽 색상}) */
		const glm::vec3 & GetColorRange() const { return m_colorRange; }

	private:
		/* 위쪽 색상 */
		glm::vec3 m_upColor;
		/* 아래쪽 색상 */
		glm::vec3 m_downColor;
		/* 색상 범위 ({위쪽 색상} - {아래쪽 색상}) */
		glm::vec3 m_colorRange;

	};

}
