// >========================================================================================<
//  본 ansi_box_geometry_generator.h 파일의 내용은 Three.js의 BoxGeometry.js 파일을
//  OpenGL과 C++에 맞게 변형한 것입니다. 원본 코드를 보고 싶으시다면 다음의 주소를 참고하세요.
//  https://github.com/mrdoob/three.js/blob/master/src/geometries/BoxGeometry.js
//  (알림: 외부에서 가져와 변형한 코드는 주석을 달지 않았습니다.)
// >========================================================================================<

#pragma once

#include "common/ansi_common.h"

namespace ansi
{

	class BoxGeometryGenerator
	{
	public:
		static bool Generate(
			float width, float height, float depth, unsigned widthSegments, unsigned heightSegments, unsigned depthSegments,
			unsigned & vertexBufferId, unsigned & indexBufferId, unsigned & vertexCount, unsigned & indexCount);

	private:
		explicit BoxGeometryGenerator() = delete;

		static unsigned BuildPlane(
			unsigned uIndex, unsigned vIndex, unsigned wIndex, float uDirection, float vDirection,
			float width, float height, float depth, unsigned divisionX, unsigned divisionY, unsigned currentVertexCount,
			std::vector<float> & rawVerticesData, std::vector<unsigned> & rawIndicesData);

	};

}
