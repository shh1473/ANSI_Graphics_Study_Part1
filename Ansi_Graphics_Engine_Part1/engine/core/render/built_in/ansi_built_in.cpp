#include "ansi_built_in.h"

#include "common/ansi_common_render.h"
#include "core/render/input_executor/input_param/ansi_input_param.h"
#include "resource/shader/ansi_shader.h"
#include "resource/geometry/ansi_geometry.h"
#include "resource/input_elements/ansi_input_elements.h"
#include "utility/shader_loader/ansi_shader_loader.h"

namespace ansi
{

	/* 생성자 */
	BuiltIn::BuiltIn()
	{

	}

	/* 소멸자 */
	BuiltIn::~BuiltIn()
	{
		SAFE_DELETE(m_depthShader);
		SAFE_DELETE(m_depthMaterial);
		SAFE_DELETE(m_screenAlignedQuad);
		SAFE_DELETE(m_screenAlignedQuadIP);
	}

	/* 초기화 함수 */
	bool BuiltIn::Initialize()
	{
		/* 깊이 기록 셰이더 생성 */
		unsigned depthShaderId{ 0 };
		CHECK_RF(ShaderLoader::Load("assets/shader/depth.shader", depthShaderId));
		m_depthShader = new Shader(depthShaderId);
		/* 깊이 기록 재질 생성 */
		m_depthMaterial = new DepthMaterial(m_depthShader->GetId());

		/* 화면에 맞는 사각형 지오메트리 생성 */
		m_screenAlignedQuad = new Geometry();
		m_screenAlignedQuad->GeneratePlane(2.0f, 2.0f);

		/* 화면에 맞는 사각형 입력 요소 생성 */
		m_screenAlignedQuadIE = m_screenAlignedQuad->CreateInputElements(VA_TEXCOORD);

		/* 화면에 맞는 사각형 입력 관련 상태 집합 생성 */
		m_screenAlignedQuadIP = new InputParam();
		m_screenAlignedQuadIP->SetInputElements(m_screenAlignedQuadIE);

		return true;
	}

}
