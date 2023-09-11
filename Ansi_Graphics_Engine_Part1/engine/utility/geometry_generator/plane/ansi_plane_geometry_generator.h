// >========================================================================================<
//  �� ansi_plane_geometry_generator.cpp ������ ������ Three.js�� PlaneGeometry.js ������
//  OpenGL�� C++�� �°� ������ ���Դϴ�. ���� �ڵ带 ���� �����ôٸ� ������ �ּҸ� �����ϼ���.
//  https://github.com/mrdoob/three.js/blob/master/src/geometries/PlaneGeometry.js
//  (�˸�: �ܺο��� ������ ������ �ڵ�� �ּ��� ���� �ʾҽ��ϴ�.)
// >========================================================================================<

#pragma once

#include "common/ansi_common.h"

namespace ansi
{

	class PlaneGeometryGenerator
	{
	public:
		static bool Generate(
			float width, float height, unsigned widthSegments, unsigned heightSegments,
			unsigned & vertexBufferId, unsigned & indexBufferId, unsigned & vertexCount, unsigned & indexCount);

	private:
		explicit PlaneGeometryGenerator() = delete;

		static void BuildPlane(
			float width, float height, unsigned divisionX, unsigned divisionY,
			std::vector<float> & rawVerticesData, std::vector<unsigned> & rawIndicesData);

	};

}
