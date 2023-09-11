#include "ansi_obj_loader.h"

#include "common/ansi_common_render.h"

namespace ansi
{

	/* .shader ������ �ҷ����� �Լ� */
	bool ObjLoader::Load(const std::string & filePath, unsigned & vertexBufferId, unsigned & vertexCount, unsigned & stride, unsigned & flag)
	{
		std::vector<float> rawVerticesData;

		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string error;
		std::string warning;

		/* Tiny Obj Loader ���̺귯���� ����� �Ľ� */
		bool result = tinyobj::LoadObj(&attrib, &shapes, &materials, &warning, &error, filePath.c_str());

		/* ���� �Ǵ� ��� �߻� �� ��� */
		if (!error.empty()) { PRINT(error); }
		if (!warning.empty()) { PRINT(warning); }
		CHECK_RF(result);

		/* ��ġ ��Ҵ� �׻� �����Ƿ� �ش� �뷮���� �ʱ�ȭ */
		stride = 3 * sizeof(float);
		flag = 0;
		/* �ؽ�ó ��ǥ�� �ϳ��� ���� ��� �ؽ�ó ��ǥ ��� �� �÷��� �߰� */
		if (attrib.texcoords.size() > 0) { stride += 2 * sizeof(float); flag |= VA_TEXCOORD; }
		/* ������ �ϳ��� ���� ��� ���� ��� �� �÷��� �߰� */
		if (attrib.normals.size() > 0) { stride += 3 * sizeof(float); flag |= VA_NORMAL; }

		/* ���ؽ� ���� ���� */
		vertexCount = static_cast<unsigned>(shapes[0].mesh.indices.size());

		/* ��� ���ؽ��� �뷮��ŭ �迭 ũ�� ���� */
		rawVerticesData.reserve(static_cast<std::size_t>(vertexCount) * stride / sizeof(float));
		/* �ε����� �������� �Ľ��� ��� �����͸� �ϳ��� �迭�� ���� */
		AssembleVertices(attrib.vertices, attrib.texcoords, attrib.normals, shapes[0].mesh.indices, rawVerticesData);

		/* ���ؽ� ���� ���� */
		CHECK_RF(CreateVertexBuffer(rawVerticesData, vertexBufferId));

		return true;
	}

	/* �ε����� �������� ���ؽ� ��� �����͸� �ϳ��� �迭�� �����ϴ� �Լ� */
	void ObjLoader::AssembleVertices(
		const std::vector<float> & loadedPositions,
		const std::vector<float> & loadedTexCoords,
		const std::vector<float> & loadedNormals,
		const std::vector<tinyobj::index_t> & loadedIndices,
		std::vector<float> & rawVerticesData)
	{
		int index{ 0 };

		/* �ε��� { ��ġ, �ؽ�ó ��ǥ, ���� }�� ����ŭ �ݺ� */
		for (unsigned i{ 0 }; i < loadedIndices.size(); ++i)
		{
			/* vertex_index ���� �� ��° ���ؽ��� ��ġ(�ε��Ҽ��� 3�� ¥��)������ �ǹ��ϹǷ�, 3�� ���� �Ľ��� ��ġ �迭������ �ε����� �˾Ƴ��� */
			index = loadedIndices[i].vertex_index * 3;
			/* ��ġ�� �ݵ�� �����ϹǷ� index�� ������ �� ���� */
			rawVerticesData.push_back(loadedPositions[index]);
			rawVerticesData.push_back(loadedPositions[index + 1]);
			rawVerticesData.push_back(loadedPositions[index + 2]);

			/* texcoord_index ���� �� ��° ���ؽ��� �ؽ�ó ��ǥ(�ε��Ҽ��� 2�� ¥��)������ �ǹ��ϹǷ�, 2�� ���� �Ľ��� �ؽ�ó ��ǥ �迭������ �ε����� �˾Ƴ��� */
			index = loadedIndices[i].texcoord_index * 2;
			/* index�� ������ ���, ���Ͽ� �ؽ�ó ��ǥ �����Ͱ� ���ٴ� �� */
			if (index >= 0)
			{
				rawVerticesData.push_back(loadedTexCoords[index]);
				rawVerticesData.push_back(loadedTexCoords[index + 1]);
			}

			/* normal_index ���� �� ��° ���ؽ��� ����(�ε��Ҽ��� 3�� ¥��)������ �ǹ��ϹǷ�, 3�� ���� �Ľ��� ���� �迭������ �ε����� �˾Ƴ��� */
			index = loadedIndices[i].normal_index * 3;
			/* index�� ������ ���, ���Ͽ� ���� �����Ͱ� ���ٴ� �� */
			if (index >= 0)
			{
				rawVerticesData.push_back(loadedNormals[index]);
				rawVerticesData.push_back(loadedNormals[index + 1]);
				rawVerticesData.push_back(loadedNormals[index + 2]);
			}
		}
	}

	/* ���ؽ� ���۸� �����ϴ� �Լ� */
	bool ObjLoader::CreateVertexBuffer(const std::vector<float> & rawVerticesData, unsigned & vertexBufferId)
	{
		GL_CHECK(glGenBuffers(1, &vertexBufferId));
		GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId));
		GL_CHECK(glBufferData(GL_ARRAY_BUFFER, rawVerticesData.size() * sizeof(float), &rawVerticesData[0], GL_STATIC_DRAW));

		return true;
	}

}
