// >========================================================================================<
//  �� ansi_sphere_geometry_generator.h ������ ������ Three.js�� SphereGeometry.js ������
//  OpenGL�� C++�� �°� ������ ���Դϴ�. ���� �ڵ带 ���� �����ôٸ� ������ �ּҸ� �����ϼ���.
//  https://github.com/mrdoob/three.js/blob/master/src/geometries/SphereGeometry.js
//  (�˸�: �ܺο��� ������ ������ �ڵ�� �ּ��� ���� �ʾҽ��ϴ�.)
// >========================================================================================<

#include "ansi_sphere_geometry_generator.h"

namespace ansi
{

	bool SphereGeometryGenerator::Generate(
		float radius, unsigned widthSegments, unsigned heightSegments, unsigned & vertexBufferId, unsigned & indexBufferId, unsigned & vertexCount, unsigned & indexCount)
	{
		CHECK_PRINT_RF((radius > 0.0f) && (widthSegments >= 3) && (heightSegments >= 2), "[Sphere Geometry Generator Error]: Invalid Parameter");

		vertexCount = (widthSegments + 1) * (heightSegments + 1) * 8;
		indexCount = widthSegments * (heightSegments - 1) * 6;

		unsigned currentIndex{ 0 };
		std::vector<float> rawVerticesData;
		std::vector<unsigned> rawIndicesData;
		rawVerticesData.reserve(vertexCount);
		rawIndicesData.reserve(indexCount);

		GenerateSphere(radius, widthSegments, heightSegments, rawVerticesData, rawIndicesData);

		GL_CHECK_RF(glGenBuffers(1, &vertexBufferId));
		GL_CHECK_RF(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId));
		GL_CHECK_RF(glBufferData(GL_ARRAY_BUFFER, rawVerticesData.size() * sizeof(float), rawVerticesData.data(), GL_STATIC_DRAW));

		GL_CHECK_RF(glGenBuffers(1, &indexBufferId));
		GL_CHECK_RF(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId));
		GL_CHECK_RF(glBufferData(GL_ELEMENT_ARRAY_BUFFER, rawIndicesData.size() * sizeof(unsigned), rawIndicesData.data(), GL_STATIC_DRAW));

		return true;
	}

	void SphereGeometryGenerator::GenerateSphere(
		float radius, unsigned widthSegments, unsigned heightSegments, std::vector<float> & rawVerticesData, std::vector<unsigned> & rawIndicesData)
	{
		float uOffset{ 0.0f };
		float u{ 0.0f }, v{ 0.0f };
		float sinPhi{ 0.0f }, cosPhi{ 0.0f }, sinTheta{ 0.0f }, cosTheta{ 0.0f };
		unsigned index{ 0 };
		glm::vec3 position(0.0f);
		std::vector<unsigned> indexRow;
		std::vector<std::vector<unsigned>> indexArray;

		for (unsigned i{ 0 }; i <= heightSegments; ++i)
		{
			v = i / static_cast<float>(heightSegments);

			uOffset = 0.0f;

			if (i == 0)
			{
				uOffset = 0.5f / widthSegments;
			}
			else if (i == heightSegments)
			{
				uOffset = -0.5f / widthSegments;
			}

			for (unsigned j{ 0 }; j <= widthSegments; ++j)
			{
				u = j / static_cast<float>(widthSegments);

				sinPhi = std::sin(u * PI2);
				cosPhi = std::cos(u * PI2);
				sinTheta = std::sin(v * PI);
				cosTheta = std::cos(v * PI);

				position.x = -radius * cosPhi * sinTheta;
				position.y = radius * cosTheta;
				position.z = radius * sinPhi * sinTheta;

				rawVerticesData.push_back(position.x);
				rawVerticesData.push_back(position.y);
				rawVerticesData.push_back(position.z);

				rawVerticesData.push_back(u + uOffset);
				rawVerticesData.push_back(1.0f - v);

				position = glm::normalize(position);

				rawVerticesData.push_back(position.x);
				rawVerticesData.push_back(position.y);
				rawVerticesData.push_back(position.z);

				indexRow.push_back(index++);
			}

			indexArray.push_back(indexRow);
			indexRow.clear();
		}

		unsigned index1{ 0 };
		unsigned index2{ 0 };
		unsigned index3{ 0 };
		unsigned index4{ 0 };

		for (unsigned i{ 0 }; i < heightSegments; ++i)
		{
			for (unsigned j{ 0 }; j < widthSegments; ++j)
			{
				index1 = indexArray[i][static_cast<std::size_t>(j) + 1];
				index2 = indexArray[i][j];
				index3 = indexArray[static_cast<std::size_t>(i) + 1][j];
				index4 = indexArray[static_cast<std::size_t>(i) + 1][static_cast<std::size_t>(j) + 1];

				if (i != 0)
				{
					rawIndicesData.push_back(index1);
					rawIndicesData.push_back(index2);
					rawIndicesData.push_back(index4);
				}
				if (i != heightSegments - 1)
				{
					rawIndicesData.push_back(index2);
					rawIndicesData.push_back(index3);
					rawIndicesData.push_back(index4);
				}
			}
		}
	}

}
