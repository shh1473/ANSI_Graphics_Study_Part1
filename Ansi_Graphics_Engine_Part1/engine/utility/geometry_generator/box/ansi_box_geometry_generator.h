// >========================================================================================<
//  �� ansi_box_geometry_generator.h ������ ������ Three.js�� BoxGeometry.js ������
//  OpenGL�� C++�� �°� ������ ���Դϴ�. ���� �ڵ带 ���� �����ôٸ� ������ �ּҸ� �����ϼ���.
//  https://github.com/mrdoob/three.js/blob/master/src/geometries/BoxGeometry.js
//  (�˸�: �ܺο��� ������ ������ �ڵ�� �ּ��� ���� �ʾҽ��ϴ�.)
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
