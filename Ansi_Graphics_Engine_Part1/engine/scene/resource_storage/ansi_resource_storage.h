#pragma once

#include "common/ansi_common.h"
#include "common/ansi_common_render.h"

namespace ansi
{

	/* 전방 선언 */
	class Shader;
	class Geometry;
	class Texture;

	/* 자원 저장소 클래스 */
	class ResourceStorage
	{
	public:
		/* 생성자 */
		explicit ResourceStorage();
		/* 소멸자 */
		~ResourceStorage();

		/* 셰이더 자원을 생성하는 함수
		* @param filePath - 파일 경로
		* @returns 생성된 셰이더 자원
		*/
		Shader * CreateShader(const std::string & filePath);
		/* 지오메트리 자원을 생성하는 함수
		* @returns 생성된 지오메트리 자원
		*/
		Geometry * CreateGeometry();
		/* 텍스처 자원을 생성하는 함수
		* @param filePath - 파일 경로
		* @returns 생성된 텍스처 자원
		*/
		Texture * CreateTexture(const std::string & filePath);

	private:
		/* 셰이더 자원 배열 */
		std::vector<Shader *> m_shaders;
		/* 지오메트리 자원 배열 */
		std::vector<Geometry *> m_geometries;
		/* 텍스처 자원 배열 */
		std::vector<Texture *> m_textures;

	};

}
