#include "ansi_renderer.h"

#include "core/render/ansi_render.h"
#include "core/render/input_executor/input_param/ansi_input_param.h"
#include "core/render/shader_executor/material/ansi_material.h"
#include "resource/input_elements/ansi_input_elements.h"
#include "object/ansi_object.h"

namespace ansi
{

	/* ������ */
	Renderer::Renderer(Object * object, InputElements * inputElements, Material * material, RendererType type)
		: Component(object)
		, m_type(type)
		, m_isCastShadow(false)
		, m_material(material)
		, m_inputParam(new InputParam())
	{
		/* ���� �����ڿ� ��� */
		Core::GetRender()->AddRenderer(this, m_type);

		/* �Է� ��ҿ� Ʈ������ ���� */
		m_inputParam->SetInputElements(inputElements);
		m_material->SetTransform(object->GetTransform());
	}

	/* �Ҹ��� */
	Renderer::~Renderer()
	{
		/* ���� �����ڿ��� ��� ���� */
		Core::GetRender()->RemoveRenderer(this, m_type);

		SAFE_DELETE(m_material);
		SAFE_DELETE(m_inputParam);
	}

}
