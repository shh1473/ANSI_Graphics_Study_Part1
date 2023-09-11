#pragma once

#include "common/ansi_common.h"

namespace ansi
{

	/* �̹��� ���� �δ� Ŭ���� */
	class TextureLoader
	{
	public:
		/* �̹��� ������ �ҷ����� �Լ�
		* @param filePath - ���� ���
		* @param width - �ʺ�
		* @param height - ����
		* @param textureId - ������ �ؽ�ó ID
		*/
		static bool Load(const std::string & filePath, int & width, int & height, unsigned & textureId);

	private:
		/* ������ (������� ����) */
		explicit TextureLoader() = delete;

	};

}
