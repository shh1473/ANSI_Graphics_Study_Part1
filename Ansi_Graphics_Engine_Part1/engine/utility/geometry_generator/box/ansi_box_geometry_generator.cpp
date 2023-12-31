// >========================================================================================<
//  본 ansi_box_geometry_generator.cpp 파일의 내용은 Three.js의 BoxGeometry.js 파일을
//  OpenGL과 C++에 맞게 변형한 것입니다. 원본 코드를 보고 싶으시다면 다음의 주소를 참고하세요.
//  https://github.com/mrdoob/three.js/blob/master/src/geometries/BoxGeometry.js
//  (알림: 외부에서 가져와 변형한 코드는 주석을 달지 않았습니다.)
// >========================================================================================<

#include "ansi_box_geometry_generator.h"

namespace ansi
{

	bool BoxGeometryGenerator::Generate(
		float width, float height, float depth,
		unsigned widthSegments, unsigned heightSegments, unsigned depthSegments,
		unsigned & vertexBufferId, unsigned & indexBufferId, unsigned & vertexCount, unsigned & indexCount)
	{
		CHECK_PRINT_RF((width > 0.0f) && (height > 0.0f) && (depth > 0.0f) && (widthSegments >= 1) && (heightSegments >= 1) && (depthSegments >= 1),
			"[Box Geometry Generator Error]: Invalid Parameter");

		vertexCount = (((widthSegments + 1) * (heightSegments + 1) * 2) +
				((widthSegments + 1) * (depthSegments + 1) * 2) +
				((depthSegments + 1) * (heightSegments + 1) * 2)) * 8;
		indexCount = ((widthSegments * heightSegments * 2) +
			(heightSegments * depthSegments * 2) +
			(depthSegments * widthSegments * 2)) * 6;

		unsigned currentVertexCount{ 0 };
		std::vector<float> rawVerticesData;
		std::vector<unsigned> rawIndicesData;
		rawVerticesData.reserve(vertexCount);
		rawIndicesData.reserve(indexCount);

		currentVertexCount += BuildPlane(0, 1, 2, 1, -1, width, height, depth, widthSegments, heightSegments, currentVertexCount, rawVerticesData, rawIndicesData);
		currentVertexCount += BuildPlane(0, 1, 2, -1, -1, width, height, -depth, widthSegments, heightSegments, currentVertexCount, rawVerticesData, rawIndicesData);
		currentVertexCount += BuildPlane(0, 2, 1, 1, 1, width, depth, height, widthSegments, depthSegments, currentVertexCount, rawVerticesData, rawIndicesData);
		currentVertexCount += BuildPlane(0, 2, 1, 1, -1, width, depth, -height, widthSegments, depthSegments, currentVertexCount, rawVerticesData, rawIndicesData);
		currentVertexCount += BuildPlane(2, 1, 0, -1, -1, depth, height, width, depthSegments, heightSegments, currentVertexCount, rawVerticesData, rawIndicesData);
		currentVertexCount += BuildPlane(2, 1, 0, 1, -1, depth, height, -width, depthSegments, heightSegments, currentVertexCount, rawVerticesData, rawIndicesData);

		GL_CHECK_RF(glGenBuffers(1, &vertexBufferId));
		GL_CHECK_RF(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId));
		GL_CHECK_RF(glBufferData(GL_ARRAY_BUFFER, rawVerticesData.size() * sizeof(float), rawVerticesData.data(), GL_STATIC_DRAW));

		GL_CHECK_RF(glGenBuffers(1, &indexBufferId));
		GL_CHECK_RF(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId));
		GL_CHECK_RF(glBufferData(GL_ELEMENT_ARRAY_BUFFER, rawIndicesData.size() * sizeof(unsigned), rawIndicesData.data(), GL_STATIC_DRAW));

		return true;
	}

	unsigned BoxGeometryGenerator::BuildPlane(
		unsigned uIndex, unsigned vIndex, unsigned wIndex, float uDirection, float vDirection,
		float width, float height, float depth, unsigned segmentsX, unsigned segmentsY, unsigned currentVertexCount,
		std::vector<float> & rawVerticesData, std::vector<unsigned> & rawIndicesData)
	{
		const float segmentWidth{ width / static_cast<float>(segmentsX) };
		const float segmentHeight{ height / static_cast<float>(segmentsY) };
		const float halfWidth{ width * 0.5f };
		const float halfHeight{ height * 0.5f };
		const float halfDepth{ depth * 0.5f };
		unsigned vertexCount{ 0 };
		glm::vec3 tmpVector(0.0f);

		for (unsigned i{ 0 }; i <= segmentsY; ++i)
		{
			for (unsigned j{ 0 }; j <= segmentsX; ++j)
			{
				tmpVector[uIndex] = (j * segmentWidth - halfWidth) * uDirection;
				tmpVector[vIndex] = (i * segmentHeight - halfHeight) * vDirection;
				tmpVector[wIndex] = halfDepth;
				rawVerticesData.push_back(tmpVector.x);
				rawVerticesData.push_back(tmpVector.y);
				rawVerticesData.push_back(tmpVector.z);

				rawVerticesData.push_back(j / static_cast<float>(segmentsX));
				rawVerticesData.push_back(1.0f - (i / static_cast<float>(segmentsY)));

				tmpVector[uIndex] = 0.0f;
				tmpVector[vIndex] = 0.0f;
				tmpVector[wIndex] = (depth > 0.0f) ? 1.0f : -1.0f;
				rawVerticesData.push_back(tmpVector.x);
				rawVerticesData.push_back(tmpVector.y);
				rawVerticesData.push_back(tmpVector.z);

				++vertexCount;
			}
		}

		unsigned index1{ 0 };
		unsigned index2{ 0 };
		unsigned index3{ 0 };
		unsigned index4{ 0 };

		for (unsigned i{ 0 }; i < segmentsY; ++i)
		{
			for (unsigned j{ 0 }; j < segmentsX; ++j)
			{
				index1 = currentVertexCount + j + (segmentsX + 1) * i;
				index2 = currentVertexCount + j + (segmentsX + 1) * (i + 1);
				index3 = currentVertexCount + (j + 1) + (segmentsX + 1) * (i + 1);
				index4 = currentVertexCount + (j + 1) + (segmentsX + 1) * i;

				rawIndicesData.push_back(index1);
				rawIndicesData.push_back(index2);
				rawIndicesData.push_back(index4);
				rawIndicesData.push_back(index2);
				rawIndicesData.push_back(index3);
				rawIndicesData.push_back(index4);
			}
		}

		return vertexCount;
	}

}
