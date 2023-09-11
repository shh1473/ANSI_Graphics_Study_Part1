#pragma once

#include "common/ansi_common.h"

namespace ansi
{

	/* 이미지 파일 로더 클래스 */
	class TextureLoader
	{
	public:
		/* 이미지 파일을 불러오는 함수
		* @param filePath - 파일 경로
		* @param width - 너비
		* @param height - 높이
		* @param textureId - 생성된 텍스처 ID
		*/
		static bool Load(const std::string & filePath, int & width, int & height, unsigned & textureId);

	private:
		/* 생성자 (사용하지 않음) */
		explicit TextureLoader() = delete;

	};

}
