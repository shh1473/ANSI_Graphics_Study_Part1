#pragma once

#include "depth_material/ansi_depth_material.h"

namespace ansi
{

	/* ���� ���� */
	class Shader;
	class Geometry;
	class InputElements;
	class InputParam;

	/* ���� �ڿ� */
	class BuiltIn
	{
	public:
		/* ������ */
		explicit BuiltIn();
		/* �Ҹ��� */
		~BuiltIn();

		/* �ʱ�ȭ �Լ� */
		bool Initialize();

		/* Getter - ���� ��� ���� */
		DepthMaterial * GetDepthMaterial() const { return m_depthMaterial; }
		/* Getter - ȭ�鿡 �´� �簢�� �Է� ���� ���� ���� */
		InputParam * GetScreenAlignedQuadIP() const { return m_screenAlignedQuadIP; }

	private:
		/* ���� ��� ���̴� */
		Shader * m_depthShader{ nullptr };
		/* ���� ��� ���� */
		DepthMaterial * m_depthMaterial{ nullptr };
		/* ȭ�鿡 �´� �簢�� ������Ʈ�� */
		Geometry * m_screenAlignedQuad{ nullptr };
		/* ȭ�鿡 �´� �簢�� �Է� ��� */
		InputElements * m_screenAlignedQuadIE{ nullptr };
		/* ȭ�鿡 �´� �簢�� �Է� ���� ���� ���� */
		InputParam * m_screenAlignedQuadIP{ nullptr };

	};

}
