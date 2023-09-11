#pragma warning(disable: 26451)
#pragma warning(disable: 6262)

/* STB - Image File Loader */
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "ansi_texture_loader.h"

namespace ansi
{

	/* 이미지 파일을 불러오는 함수 */
	bool TextureLoader::Load(const std::string & filePath, int & width, int & height, unsigned & textureId)
	{
		int bitsPerPixel;

		/* STB 라이브러리를 이용해 이미지 파일의 데이터 불러오기 */
		stbi_set_flip_vertically_on_load(1);
		auto buffer = stbi_load(filePath.c_str(), &width, &height, &bitsPerPixel, 4);
		CHECK_PRINT_RF(buffer, "[Texture Error]: File Not Found");

		/* 텍스처 생성 */
		GL_CHECK(glGenTextures(1, &textureId));
		GL_CHECK(glBindTexture(GL_TEXTURE_2D, textureId));

		/* 텍스처 속성 설정 */
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

		/* 텍스처의 데이터를 불러온 데이터로 채우기 */
		GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer));
		GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));

		/* 이미지 데이터 메모리 해제 */
		stbi_image_free(buffer);

		return true;
	}

}
