#pragma once

#include "object/component/ansi_component.h"

namespace ansi
{

	/* ���� ���� */
	class DepthCamera;

	/* �𷺼ų� ����Ʈ ������Ʈ Ŭ���� */
	class DirectionalLight : public Component
	{
	public:
		/* ������ */
		explicit DirectionalLight(Object * object, const glm::vec3 & color = glm::vec3(1.0f));
		/* �Ҹ��� */
		virtual ~DirectionalLight();

		/* �� �����Ӹ��� ȣ��Ǵ� ������Ʈ �Լ� */
		bool OnUpdate() override;

		/* �׸��� ������ ���� �غ�(�����ӹ���, ���� �ؽ�ó ����)�� �ϴ� �Լ�
		* @param resolution - ���� �ؽ�ó �ػ� (�⺻: 1024.0f)
		*/
		bool CastShadow(float resolution = 1024.0f);

		/* Setter - ���� */
		void SetColor(const glm::vec3 & color) { m_color = color; }

		/* Getter - ���� */
		const glm::vec3 & GetColor() const { return m_color; }
		/* Getter - ���� ī�޶� */
		DepthCamera * GetDepthMapCamera() { return m_depthMapCamera; }

	private:
		/* ���� */
		glm::vec3 m_color;
		/* ���� ī�޶� */
		DepthCamera * m_depthMapCamera;

	};

}
