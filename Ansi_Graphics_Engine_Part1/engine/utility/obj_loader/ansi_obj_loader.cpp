#include "ansi_obj_loader.h"

#include "common/ansi_common_render.h"

namespace ansi
{

	/* .shader 파일을 불러오는 함수 */
	bool ObjLoader::Load(const std::string & filePath, unsigned & vertexBufferId, unsigned & vertexCount, unsigned & stride, unsigned & flag)
	{
		std::vector<float> rawVerticesData;

		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string error;
		std::string warning;

		/* Tiny Obj Loader 라이브러리를 사용해 파싱 */
		bool result = tinyobj::LoadObj(&attrib, &shapes, &materials, &warning, &error, filePath.c_str());

		/* 에러 또는 경고 발생 시 출력 */
		if (!error.empty()) { PRINT(error); }
		if (!warning.empty()) { PRINT(warning); }
		CHECK_RF(result);

		/* 위치 요소는 항상 있으므로 해당 용량으로 초기화 */
		stride = 3 * sizeof(float);
		flag = 0;
		/* 텍스처 좌표가 하나라도 있을 경우 텍스처 좌표 등록 및 플래그 추가 */
		if (attrib.texcoords.size() > 0) { stride += 2 * sizeof(float); flag |= VA_TEXCOORD; }
		/* 법선이 하나라도 있을 경우 법선 등록 및 플래그 추가 */
		if (attrib.normals.size() > 0) { stride += 3 * sizeof(float); flag |= VA_NORMAL; }

		/* 버텍스 개수 설정 */
		vertexCount = static_cast<unsigned>(shapes[0].mesh.indices.size());

		/* 모든 버텍스의 용량만큼 배열 크기 예약 */
		rawVerticesData.reserve(static_cast<std::size_t>(vertexCount) * stride / sizeof(float));
		/* 인덱스를 바탕으로 파싱한 모든 데이터를 하나의 배열로 조합 */
		AssembleVertices(attrib.vertices, attrib.texcoords, attrib.normals, shapes[0].mesh.indices, rawVerticesData);

		/* 버텍스 버퍼 생성 */
		CHECK_RF(CreateVertexBuffer(rawVerticesData, vertexBufferId));

		return true;
	}

	/* 인덱스를 바탕으로 버텍스 요소 데이터를 하나의 배열로 조합하는 함수 */
	void ObjLoader::AssembleVertices(
		const std::vector<float> & loadedPositions,
		const std::vector<float> & loadedTexCoords,
		const std::vector<float> & loadedNormals,
		const std::vector<tinyobj::index_t> & loadedIndices,
		std::vector<float> & rawVerticesData)
	{
		int index{ 0 };

		/* 인덱스 { 위치, 텍스처 좌표, 법선 }의 수만큼 반복 */
		for (unsigned i{ 0 }; i < loadedIndices.size(); ++i)
		{
			/* vertex_index 값은 몇 번째 버텍스의 위치(부동소수점 3개 짜리)인지를 의미하므로, 3을 곱해 파싱한 위치 배열에서의 인덱스를 알아내기 */
			index = loadedIndices[i].vertex_index * 3;
			/* 위치는 반드시 존재하므로 index가 음수일 수 없음 */
			rawVerticesData.push_back(loadedPositions[index]);
			rawVerticesData.push_back(loadedPositions[index + 1]);
			rawVerticesData.push_back(loadedPositions[index + 2]);

			/* texcoord_index 값은 몇 번째 버텍스의 텍스처 좌표(부동소수점 2개 짜리)인지를 의미하므로, 2을 곱해 파싱한 텍스처 좌표 배열에서의 인덱스를 알아내기 */
			index = loadedIndices[i].texcoord_index * 2;
			/* index가 음수일 경우, 파일에 텍스처 좌표 데이터가 없다는 뜻 */
			if (index >= 0)
			{
				rawVerticesData.push_back(loadedTexCoords[index]);
				rawVerticesData.push_back(loadedTexCoords[index + 1]);
			}

			/* normal_index 값은 몇 번째 버텍스의 법선(부동소수점 3개 짜리)인지를 의미하므로, 3을 곱해 파싱한 법선 배열에서의 인덱스를 알아내기 */
			index = loadedIndices[i].normal_index * 3;
			/* index가 음수일 경우, 파일에 법선 데이터가 없다는 뜻 */
			if (index >= 0)
			{
				rawVerticesData.push_back(loadedNormals[index]);
				rawVerticesData.push_back(loadedNormals[index + 1]);
				rawVerticesData.push_back(loadedNormals[index + 2]);
			}
		}
	}

	/* 버텍스 버퍼를 생성하는 함수 */
	bool ObjLoader::CreateVertexBuffer(const std::vector<float> & rawVerticesData, unsigned & vertexBufferId)
	{
		GL_CHECK(glGenBuffers(1, &vertexBufferId));
		GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId));
		GL_CHECK(glBufferData(GL_ARRAY_BUFFER, rawVerticesData.size() * sizeof(float), &rawVerticesData[0], GL_STATIC_DRAW));

		return true;
	}

}
