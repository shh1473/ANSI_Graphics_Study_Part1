// >========================================================================================<
//  �� ansi_sphere_geometry_generator.h ������ ������ Three.js�� SphereGeometry.js ������
//  OpenGL�� C++�� �°� ������ ���Դϴ�. ���� �ڵ带 ���� �����ôٸ� ������ �ּҸ� �����ϼ���.
//  https://github.com/mrdoob/three.js/blob/master/src/geometries/SphereGeometry.js
//  (�˸�: �ܺο��� ������ ������ �ڵ�� �ּ��� ���� �ʾҽ��ϴ�.)
// >========================================================================================<

#pragma once

#include "common/ansi_common.h"

namespace ansi
{

	class SphereGeometryGenerator
	{
	public:
		static bool Generate(
			float radius, unsigned widthSegments, unsigned heightSegments, unsigned & vertexBufferId, unsigned & indexBufferId, unsigned & vertexCount, unsigned & indexCount);

	private:
		explicit SphereGeometryGenerator() = delete;

		static void GenerateSphere(float radius, unsigned widthSegments, unsigned heightSegments, std::vector<float> & rawVerticesData, std::vector<unsigned> & rawIndicesData);

	};

}
