#pragma once

#include "common/ansi_common.h"

namespace ansi
{

	/* .shader ���� �δ� Ŭ���� */
	class ShaderLoader
	{
	public:
		/* .shader ������ �ҷ����� �Լ�
		* @param filePath - ���� ���
		* @param shaderId - ������ ���̴� ID
		*/
		static bool Load(const std::string & filePath, unsigned & shaderId);

	private:
		/* ���̴� �ܰ� */
		enum class ShaderStage
		{
			/* ���ؽ� */
			Vertex,
			/* �����׸�Ʈ */
			Fragment,
			/* ���̴� �ܰ� ���� */
			length,
		};

	private:
		/* ������ (������� ����) */
		explicit ShaderLoader() = delete;

		/* ���̴� ������ �Ľ��ϴ� �Լ�
		* @param filePath - ���� ���
		* @param sources - �Ľ̵� �ڵ� �迭 (���̴� �ܰ�� �� ��)
		*/
		static bool ParseShader(const std::string & filePath, std::vector<std::string> & sources);
		/* �Ľ̵� �ڵ带 �������ϴ� �Լ�
		* @param stage - ���̴� �ܰ�
		* @param filePath - ���� ���
		* @param source - �Ľ̵� �ڵ�
		* @param shaderId - ������ ���̴� ID
		*/
		static bool CompileShader(unsigned stage, const std::string & filePath, const std::string & source, unsigned & shaderId);

	};

}
