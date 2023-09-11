#pragma once

#include "common/ansi_common_render.h"
#include "object/component/ansi_component.h"

namespace ansi
{

	/* ���� ���� */
	class InputParam;
	class Material;
	class InputElements;

	/* ������ ������Ʈ Ŭ���� */
	class Renderer : public Component
	{
	public:
		/* ������
		* @param object - ������ ������Ʈ
		* @param inputElements - �Է� ���
		* @param material - ����
		* @param type - ������ ����
		*/
		explicit Renderer(Object * object, InputElements * inputElements, Material * material, RendererType type = RendererType::Normal);
		/* �Ҹ��� */
		virtual ~Renderer();

		/* Setter - �׸��� ���� ���� */
		void SetIsCastShadow(bool isCastShadow) { m_isCastShadow = isCastShadow; }

		/* Getter - �׸��� ���� ���� */
		bool GetIsCastShadow() const { return m_isCastShadow; }
		/* Getter - ���� */
		Material * GetMaterial() const { return m_material; }
		/* Getter - �Է� ���� ���� ���� */
		InputParam * GetInput() const { return m_inputParam; }

	private:
		/* ������ ���� */
		const RendererType m_type;
		/* �׸��� ���� ���� */
		bool m_isCastShadow;
		/* ���� */
		Material * m_material;
		/* �Է� ���� ���� ���� */
		InputParam * m_inputParam;

	};

}