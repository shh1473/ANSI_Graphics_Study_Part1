#pragma once

#include "common/ansi_common.h"

namespace ansi
{

	/* .obj ���� �δ� Ŭ���� */
	class ObjLoader
	{
	public:
		/* .shader ������ �ҷ����� �Լ�
		* @param filePath - ���� ���
		* @param vertexBufferId - ������ ���ؽ� ���� ID
		* @param vertexCount - ������ ���ؽ� ����
		* @param stride - ������ �� ���ؽ� �� ���� �ּ� ����
		* @param flag - ������ ���ؽ� ��� �÷���
		*/
		static bool Load(const std::string & filePath, unsigned & vertexBufferId, unsigned & vertexCount, unsigned & stride, unsigned & flag);

	private:
		/* ������ (������� ����) */
		explicit ObjLoader() = delete;

		/* �ε����� �������� ���ؽ� ��� �����͸� �ϳ��� �迭�� �����ϴ� �Լ�
		* @param loadedPositions - �Ľ��� ���ؽ� ��ġ ������ �迭
		* @param loadedTexCoords - �Ľ��� ���ؽ� �ؽ��� ��ǥ ������ �迭
		* @param loadedNormals - �Ľ��� ���ؽ� ���� ������ �迭
		* @param loadedIndices - �Ľ��� �ε��� ������ �迭
		* @param rawVerticesData - ������ ���ؽ� ������ �迭
		*/
		static void AssembleVertices(
			const std::vector<float> & loadedPositions,
			const std::vector<float> & loadedTexCoords,
			const std::vector<float> & loadedNormals,
			const std::vector<tinyobj::index_t> & loadedIndices,
			std::vector<float> & rawVerticesData);
		/* ���ؽ� ���۸� �����ϴ� �Լ�
		* @param rawVerticesData - ������ ���ؽ� ������ �迭
		* @param vertexBufferId - ������ ���ؽ� ���� ID
		*/
		static bool CreateVertexBuffer(const std::vector<float> & rawVerticesData, unsigned & vertexBufferId);

	};

}
