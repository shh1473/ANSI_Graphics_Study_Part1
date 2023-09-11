#include "ansi_renderer.h"

#include "core/render/ansi_render.h"
#include "core/render/input_executor/input_param/ansi_input_param.h"
#include "core/render/shader_executor/material/ansi_material.h"
#include "resource/input_elements/ansi_input_elements.h"
#include "object/ansi_object.h"

namespace ansi
{

	/* 생성자 */
	Renderer::Renderer(Object * object, InputElements * inputElements, Material * material, RendererType type)
		: Component(object)
		, m_type(type)
		, m_isCastShadow(false)
		, m_material(material)
		, m_inputParam(new InputParam())
	{
		/* 렌더 관리자에 등록 */
		Core::GetRender()->AddRenderer(this, m_type);

		/* 입력 요소와 트랜스폼 설정 */
		m_inputParam->SetInputElements(inputElements);
		m_material->SetTransform(object->GetTransform());
	}

	/* 소멸자 */
	Renderer::~Renderer()
	{
		/* 렌더 관리자에서 등록 해제 */
		Core::GetRender()->RemoveRenderer(this, m_type);

		SAFE_DELETE(m_material);
		SAFE_DELETE(m_inputParam);
	}

}
