#pragma warning(disable: 26451)
#pragma warning(disable: 6262)

/* STB - Image File Loader */
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "ansi_texture_loader.h"

namespace ansi
{

	/* �̹��� ������ �ҷ����� �Լ� */
	bool TextureLoader::Load(const std::string & filePath, int & width, int & height, unsigned & textureId)
	{
		int bitsPerPixel;

		/* STB ���̺귯���� �̿��� �̹��� ������ ������ �ҷ����� */
		stbi_set_flip_vertically_on_load(1);
		auto buffer = stbi_load(filePath.c_str(), &width, &height, &bitsPerPixel, 4);
		CHECK_PRINT_RF(buffer, "[Texture Error]: File Not Found");

		/* �ؽ�ó ���� */
		GL_CHECK(glGenTextures(1, &textureId));
		GL_CHECK(glBindTexture(GL_TEXTURE_2D, textureId));

		/* �ؽ�ó �Ӽ� ���� */
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

		/* �ؽ�ó�� �����͸� �ҷ��� �����ͷ� ä��� */
		GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer));
		GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));

		/* �̹��� ������ �޸� ���� */
		stbi_image_free(buffer);

		return true;
	}

}
