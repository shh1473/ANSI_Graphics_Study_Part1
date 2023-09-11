#pragma once

#include "common/ansi_common.h"
#include "common/ansi_common_render.h"

namespace ansi
{

	/* 전방 선언 */
	class InputElements;

	/* 지오메트리 자원 클래스 */
	class Geometry
	{
	public:
		/* 생성자 */
		explicit Geometry();
		/* 소멸자 */
		virtual ~Geometry();

		/* 특정 버텍스 요소로만 이뤄진 입력 요소를 생성하는 함수
		* @param flag - 포함할 버텍스 요소 플래그 (기본: {텍스처 좌표} | {법선})
		* @returns 생성된 입력 요소
		*/
		InputElements * CreateInputElements(unsigned flag = VA_TEXCOORD | VA_NORMAL);

		/* 평면 지오메트리를 생성하는 함수
		* @param width - 너비
		* @param height - 높이
		* @param widthSegments - 너비 분할 수 (기본: 1)
		* @param heightSegments - 높이 분할 수 (기본: 1)
		*/
		bool GeneratePlane(float width, float height, unsigned widthSegments = 1, unsigned heightSegments = 1);
		/* 상자 지오메트리를 생성하는 함수
		* @param width - 너비
		* @param height - 높이
		* @param depth - 깊이
		* @param widthSegments - 너비 분할 수 (기본: 1)
		* @param heightSegments - 높이 분할 수 (기본: 1)
		* @param depthSegments - 깊이 분할 수 (기본: 1)
		*/
		bool GenerateBox(float width, float height, float depth, unsigned widthSegments = 1, unsigned heightSegments = 1, unsigned depthSegments = 1);
		/* 구체 지오메트리를 생성하는 함수
		* @param radius - 반지름
		* @param widthSegments - 너비 분할 수 (기본: 16)
		* @param heightSegments - 높이 분할 수 (기본: 8)
		*/
		bool GenerateSphere(float radius, unsigned widthSegments = 16, unsigned heightSegments = 8);
		/* 원통 지오메트리를 생성하는 함수
		* @param topRadius - 상단 반지름
		* @param bottomRadius - 하단 반지름
		* @param height - 높이
		* @param radialSegments - 뚜껑 분할 수 (기본: 16)
		* @param heightSegments - 높이 분할 수 (기본: 1)
		*/
		bool GenerateCylinder(float topRadius, float bottomRadius, float height, unsigned radialSegments = 16, unsigned heightSegments = 1);
		/* 오브젝트 파일에서 지오메트리 데이터를 가져와 생성하는 함수
		* @param filePath - 오브젝트 파일 경로
		*/
		bool GenerateFromObj(const std::string & filePath);
		
	private:
		/* 버텍스 개수 */
		unsigned m_vertexCount;
		/* 인덱스 개수 */
		unsigned m_indexCount;
		/* 버텍스 버퍼 ID */
		unsigned m_vertexBufferId;
		/* 인덱스 버퍼 ID */
		unsigned m_indexBufferId;
		/* 각 버텍스 간 시작 주소 간격 */
		unsigned m_stride;
		/* 생성한 지오메트리의 버텍스 요소 플래그 */
		unsigned m_flag;
		/* 입력 요소 배열 */
		std::vector<InputElements *> m_inputElements;

	};

}
