#pragma once

#include "core/render/shader_executor/material/ansi_material.h"
#include "utility/state_checker/ansi_state_checker.h"

namespace ansi
{

	/* ���� ���� */
	class Material;

	/* ���̴� ����� Ŭ���� */
	class ShaderExecutor
	{
	public:
		/* ������ */
		explicit ShaderExecutor();
		/* �Ҹ��� */
		~ShaderExecutor();

		/* OpenGL ���ؽ�Ʈ�� ���̴� ���� ���¸� �����ϴ� �Լ�
		* @param material - ����
		*/
		bool Apply(Material * material);
		/* OpenGL ���ؽ�Ʈ�� ���̴� ���� ���¸� �ʱ�ȭ�ϴ� �Լ� */
		bool Reset();

	private:
		/* �⺻ ���� */
		Material * m_defaultMaterial;
		/* ���� ���� Ȱ��ȭ ���� */
		bool m_isEnableDepthWrite;
		/* ���̴� ID (���� �˻�) */
		StateChecker<unsigned> m_shaderId;
		/* �ؽ�ó ID �迭 (���� �˻�) */
		StateArrayChecker<unsigned, MaxTextureCount> m_textureIds;
		/* �ؽ�ó ���� �迭 (���� �˻�) */
		StateArrayChecker<unsigned, MaxTextureCount> m_textureTypes;
		/* ���� �׽�Ʈ Ȱ��ȭ ���� (���� �˻�) */
		StateChecker<bool> m_isEnableDepthTest;
		/* ���� �� �Լ� (���� �˻�) */
		StateChecker<CompareFunc> m_depthFunc;
		/* �ﰢ�� ä��� ��� (���� �˻�) */
		StateChecker<FillMode> m_fillMode;
		/* �ﰢ�� �ø� ��� (���� �˻�) */
		StateChecker<CullMode> m_cullMode;
		/* �ﰢ�� �ո� ���� ���� (���� �˻�) */
		StateChecker<FrontFace> m_frontFace;

	};

}
