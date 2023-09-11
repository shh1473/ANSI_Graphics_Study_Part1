#include "ansi_built_in.h"

#include "common/ansi_common_render.h"
#include "core/render/input_executor/input_param/ansi_input_param.h"
#include "resource/shader/ansi_shader.h"
#include "resource/geometry/ansi_geometry.h"
#include "resource/input_elements/ansi_input_elements.h"
#include "utility/shader_loader/ansi_shader_loader.h"

namespace ansi
{

	/* ������ */
	BuiltIn::BuiltIn()
	{

	}

	/* �Ҹ��� */
	BuiltIn::~BuiltIn()
	{
		SAFE_DELETE(m_depthShader);
		SAFE_DELETE(m_depthMaterial);
		SAFE_DELETE(m_screenAlignedQuad);
		SAFE_DELETE(m_screenAlignedQuadIP);
	}

	/* �ʱ�ȭ �Լ� */
	bool BuiltIn::Initialize()
	{
		/* ���� ��� ���̴� ���� */
		unsigned depthShaderId{ 0 };
		CHECK_RF(ShaderLoader::Load("assets/shader/depth.shader", depthShaderId));
		m_depthShader = new Shader(depthShaderId);
		/* ���� ��� ���� ���� */
		m_depthMaterial = new DepthMaterial(m_depthShader->GetId());

		/* ȭ�鿡 �´� �簢�� ������Ʈ�� ���� */
		m_screenAlignedQuad = new Geometry();
		m_screenAlignedQuad->GeneratePlane(2.0f, 2.0f);

		/* ȭ�鿡 �´� �簢�� �Է� ��� ���� */
		m_screenAlignedQuadIE = m_screenAlignedQuad->CreateInputElements(VA_TEXCOORD);

		/* ȭ�鿡 �´� �簢�� �Է� ���� ���� ���� ���� */
		m_screenAlignedQuadIP = new InputParam();
		m_screenAlignedQuadIP->SetInputElements(m_screenAlignedQuadIE);

		return true;
	}

}
