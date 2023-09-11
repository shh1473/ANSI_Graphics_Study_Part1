#pragma once

#include "common/ansi_common.h"

namespace ansi
{

	/* .obj 파일 로더 클래스 */
	class ObjLoader
	{
	public:
		/* .shader 파일을 불러오는 함수
		* @param filePath - 파일 경로
		* @param vertexBufferId - 생성된 버텍스 버퍼 ID
		* @param vertexCount - 생성된 버텍스 개수
		* @param stride - 생성된 각 버텍스 간 시작 주소 간격
		* @param flag - 생성된 버텍스 요소 플래그
		*/
		static bool Load(const std::string & filePath, unsigned & vertexBufferId, unsigned & vertexCount, unsigned & stride, unsigned & flag);

	private:
		/* 생성자 (사용하지 않음) */
		explicit ObjLoader() = delete;

		/* 인덱스를 바탕으로 버텍스 요소 데이터를 하나의 배열로 조합하는 함수
		* @param loadedPositions - 파싱한 버텍스 위치 데이터 배열
		* @param loadedTexCoords - 파싱한 버텍스 텍스쳐 좌표 데이터 배열
		* @param loadedNormals - 파싱한 버텍스 법선 데이터 배열
		* @param loadedIndices - 파싱한 인덱스 데이터 배열
		* @param rawVerticesData - 조합한 버텍스 데이터 배열
		*/
		static void AssembleVertices(
			const std::vector<float> & loadedPositions,
			const std::vector<float> & loadedTexCoords,
			const std::vector<float> & loadedNormals,
			const std::vector<tinyobj::index_t> & loadedIndices,
			std::vector<float> & rawVerticesData);
		/* 버텍스 버퍼를 생성하는 함수
		* @param rawVerticesData - 조합한 버텍스 데이터 배열
		* @param vertexBufferId - 생성된 버텍스 버퍼 ID
		*/
		static bool CreateVertexBuffer(const std::vector<float> & rawVerticesData, unsigned & vertexBufferId);

	};

}
