#pragma once

#include "object/component/ansi_component.h"

namespace ansi
{

	/* �ݱ��� �ں��Ʈ ����Ʈ ������Ʈ Ŭ���� */
	class HSAmbientLight : public Component
	{
	public:
		/* ������
		* @param object - ������ ������Ʈ
		* @param upColor - ���� ����
		* @param downColor - �Ʒ��� ����
		*/
		explicit HSAmbientLight(Object * object, const glm::vec3 & upColor = glm::vec3(1.0f), const glm::vec3 & downColor = glm::vec3(1.0f));

		/* Setter - ���� ���� */
		void SetUpColor(const glm::vec3 & color) { m_upColor = color; m_colorRange = m_upColor - m_downColor; }
		/* Setter - �Ʒ��� ���� */
		void SetDownColor(const glm::vec3 & color) { m_downColor = color; m_colorRange = m_upColor - m_downColor; }

		/* Getter - �Ʒ��� ���� */
		const glm::vec3 & GetDownColor() const { return m_downColor; }
		/* Getter - ���� ���� ({���� ����} - {�Ʒ��� ����}) */
		const glm::vec3 & GetColorRange() const { return m_colorRange; }

	private:
		/* ���� ���� */
		glm::vec3 m_upColor;
		/* �Ʒ��� ���� */
		glm::vec3 m_downColor;
		/* ���� ���� ({���� ����} - {�Ʒ��� ����}) */
		glm::vec3 m_colorRange;

	};

}
