// >========================================================================================<
//  �� ansi_cylinder_geometry_generator.h ������ ������ Three.js�� CylinderGeometry.js ������
//  OpenGL�� C++�� �°� ������ ���Դϴ�. ���� �ڵ带 ���� �����ôٸ� ������ �ּҸ� �����ϼ���.
//  https://github.com/mrdoob/three.js/blob/master/src/geometries/CylinderGeometry.js
//  (�˸�: �ܺο��� ������ ������ �ڵ�� �ּ��� ���� �ʾҽ��ϴ�.)
// >========================================================================================<

#pragma once

#include "common/ansi_common.h"

namespace ansi
{

	class CylinderGeometryGenerator
	{
	public:
		static bool Generate(
			float topRadius, float bottomRadius, float height, unsigned radialSegments, unsigned heightSegments,
			unsigned & vertexBufferId, unsigned & indexBufferId, unsigned & vertexCount, unsigned & indexCount);

	private:
		explicit CylinderGeometryGenerator() = delete;

		static void GenerateTorso(float topRadius, float bottomRadius, float height, unsigned radialSegments, unsigned heightSegments,
			unsigned & currentIndex, std::vector<float> & rawVerticesData, std::vector<unsigned> & rawIndicesData);
		static void GenerateCap(bool isTop, float topRadius, float bottomRadius, float height, unsigned radialSegments,
			unsigned & currentIndex, std::vector<float> & rawVerticesData, std::vector<unsigned> & rawIndicesData);

	};

}
