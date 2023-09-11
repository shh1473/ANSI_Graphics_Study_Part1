// >========================================================================================<
//  �� ansi_plane_geometry_generator.cpp ������ ������ Three.js�� PlaneGeometry.js ������
//  OpenGL�� C++�� �°� ������ ���Դϴ�. ���� �ڵ带 ���� �����ôٸ� ������ �ּҸ� �����ϼ���.
//  https://github.com/mrdoob/three.js/blob/master/src/geometries/PlaneGeometry.js
//  (�˸�: �ܺο��� ������ ������ �ڵ�� �ּ��� ���� �ʾҽ��ϴ�.)
// >========================================================================================<

#include "ansi_plane_geometry_generator.h"

namespace ansi
{

	bool PlaneGeometryGenerator::Generate(
		float width, float height, unsigned widthSegments, unsigned heightSegments,
		unsigned & vertexBufferId, unsigned & indexBufferId, unsigned & vertexCount, unsigned & indexCount)
	{
		CHECK_PRINT_RF((width > 0.0f) && (height > 0.0f) && (widthSegments >= 1) && (heightSegments >= 1), "[Plane Geometry Generator Error]: Invalid Parameter");

		vertexCount = (widthSegments + 1) * (heightSegments + 1) * 8;
		indexCount = (widthSegments * heightSegments) * 6;

		std::vector<float> rawVerticesData;
		std::vector<unsigned> rawIndicesData;
		rawVerticesData.reserve(vertexCount);
		rawIndicesData.reserve(indexCount);
		vertexCount /= 8;

		BuildPlane(width, height, widthSegments, heightSegments, rawVerticesData, rawIndicesData);

		GL_CHECK_RF(glGenBuffers(1, &vertexBufferId));
		GL_CHECK_RF(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId));
		GL_CHECK_RF(glBufferData(GL_ARRAY_BUFFER, rawVerticesData.size() * sizeof(float), rawVerticesData.data(), GL_STATIC_DRAW));

		GL_CHECK_RF(glGenBuffers(1, &indexBufferId));
		GL_CHECK_RF(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId));
		GL_CHECK_RF(glBufferData(GL_ELEMENT_ARRAY_BUFFER, rawIndicesData.size() * sizeof(unsigned), rawIndicesData.data(), GL_STATIC_DRAW));

		return true;
	}

	void PlaneGeometryGenerator::BuildPlane(
		float width, float height, unsigned widthSegments, unsigned heightSegments,
		std::vector<float> & rawVerticesData, std::vector<unsigned> & rawIndicesData)
	{
		const float segmentWidth{ width / static_cast<float>(widthSegments) };
		const float segmentHeight{ height / static_cast<float>(heightSegments) };
		const float halfWidth{ width * 0.5f };
		const float halfHeight{ height * 0.5f };
		float x{ 0.0f }, y{ 0.0f };
		glm::vec3 tmpVector(0.0f);

		for (unsigned i{ 0 }; i <= heightSegments; ++i)
		{
			y = (i * segmentHeight) - halfHeight;

			for (unsigned j{ 0 }; j <= widthSegments; ++j)
			{
				x = (j * segmentWidth) - halfWidth;

				rawVerticesData.push_back(x);
				rawVerticesData.push_back(-y);
				rawVerticesData.push_back(0.0f);

				rawVerticesData.push_back(j / static_cast<float>(widthSegments));
				rawVerticesData.push_back(1.0f - (i / static_cast<float>(heightSegments)));

				rawVerticesData.push_back(0.0f);
				rawVerticesData.push_back(0.0f);
				rawVerticesData.push_back(1.0f);
			}
		}

		unsigned index1{ 0 };
		unsigned index2{ 0 };
		unsigned index3{ 0 };
		unsigned index4{ 0 };

		for (unsigned i{ 0 }; i < heightSegments; ++i)
		{
			for (unsigned j{ 0 }; j < widthSegments; ++j)
			{
				index1 = j + (widthSegments + 1) * i;
				index2 = j + (widthSegments + 1) * (i + 1);
				index3 = (j + 1) + (widthSegments + 1) * (i + 1);
				index4 = (j + 1) + (widthSegments + 1) * i;

				rawIndicesData.push_back(index1);
				rawIndicesData.push_back(index2);
				rawIndicesData.push_back(index4);
				rawIndicesData.push_back(index2);
				rawIndicesData.push_back(index3);
				rawIndicesData.push_back(index4);
			}
		}
	}

}
