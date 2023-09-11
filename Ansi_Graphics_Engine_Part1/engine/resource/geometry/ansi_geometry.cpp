/* 'reinterpret_cast': 'unsigned int'���� �� ū 'unsigned int *'(��)���� ��ȯ ��� ���� */
#pragma warning(disable: 4312)

#include "ansi_geometry.h"

#include "common/ansi_common_render.h"
#include "resource/input_elements/ansi_input_elements.h"
#include "utility/geometry_generator/plane/ansi_plane_geometry_generator.h"
#include "utility/geometry_generator/box/ansi_box_geometry_generator.h"
#include "utility/geometry_generator/sphere/ansi_sphere_geometry_generator.h"
#include "utility/geometry_generator/cylinder/ansi_cylinder_geometry_generator.h"
#include "utility/obj_loader/ansi_obj_loader.h"

namespace ansi
{

	/* ������ */
	Geometry::Geometry()
		: m_vertexCount(0)
		, m_indexCount(0)
		, m_vertexBufferId(0)
		, m_indexBufferId(0)
		, m_stride(8 * sizeof(float))
		, m_flag(VA_TEXCOORD | VA_NORMAL)
		, m_inputElements()
	{

	}

	/* �Ҹ��� */
	Geometry::~Geometry()
	{
		if (m_vertexBufferId) { GL_CHECK(glDeleteBuffers(1, &m_vertexBufferId)); }
		if (m_indexBufferId) { GL_CHECK(glDeleteBuffers(1, &m_indexBufferId)); }
		for (auto & inputElements : m_inputElements) { SAFE_DELETE(inputElements); }
	}

	/* Ư�� ���ؽ� ��ҷθ� �̷��� �Է� ��Ҹ� �����ϴ� �Լ� */
	InputElements * Geometry::CreateInputElements(unsigned flag)
	{
		/* ������Ʈ���� �������� ���� ���·� �Է� ��Ҹ� �����Ϸ� �� ��� �ߴ� */
		CHECK_PRINT_RN(m_vertexCount != 0, "[Geometry Error]: No Geometry Data");

		/* ���ؽ� �迭 ���� */
		unsigned id{ 0 };
		GL_CHECK_RN(glGenVertexArrays(1, &id));
		GL_CHECK_RN(glBindVertexArray(id));
		GL_CHECK_RN(glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId));

		std::vector<unsigned> elementCounts;
		std::vector<unsigned *> offsets;

		/* �⺻������ ��ġ�� �׿� ���� ������ �߰� */
		unsigned offset{ 0 };
		elementCounts.push_back(3);
		offsets.push_back(reinterpret_cast<unsigned *>(offset));
		/* ���� ������ ���� (��ġ ����� �뷮��ŭ) */
		offset += 3 * sizeof(float);

		/* ������ ������Ʈ�� �����Ϳ� �ؽ�ó ��ǥ ��Ұ� �ִ� ��� */
		if (m_flag & VA_TEXCOORD)
		{
			/* �ؽ�ó ��ǥ �÷��׸� ������ ��� */
			if (flag & VA_TEXCOORD)
			{
				/* �ؽ�ó ��ǥ�� �׿� ���� ������ �߰� */
				elementCounts.push_back(2);
				offsets.push_back(reinterpret_cast<unsigned *>(offset));
			}
			/* ���� ������ ���� (�ؽ�ó ��ǥ ����� �뷮��ŭ) */
			offset += 2 * sizeof(float);
		}

		/* ������ ������Ʈ�� �����Ϳ� ���� ��Ұ� �ִ� ��� */
		if (m_flag & VA_NORMAL)
		{
			/* ���� �÷��׸� ������ ��� */
			if (flag & VA_NORMAL)
			{
				/* ������ �׿� ���� ������ �߰� */
				elementCounts.push_back(3);
				offsets.push_back(reinterpret_cast<unsigned *>(offset));
			}
			/* ���� ������ ���� (���� ����� �뷮��ŭ) */
			offset += 3 * sizeof(float);
		}

		/* �⺻ ��ġ ��ҿ� �÷��׷� ������ �߰� ��Ҹ� ������ ���ؽ� �迭 ���� */
		for (unsigned i{ 0 }; i < elementCounts.size(); ++i)
		{
			GL_CHECK_RN(glEnableVertexAttribArray(i));
			GL_CHECK_RN(glVertexAttribPointer(i, elementCounts[i], GL_FLOAT, GL_FALSE, m_stride, reinterpret_cast<const void *>(offsets[i])));
		}

		/* �Է� ��� ���� */
		m_inputElements.push_back(new InputElements(id, m_indexBufferId, m_vertexCount, m_indexCount));

		return m_inputElements.back();
	}

	/* ��� ������Ʈ���� �����ϴ� �Լ� */
	bool Geometry::GeneratePlane(float width, float height, unsigned widthSegments, unsigned heightSegments)
	{
		CHECK_PRINT_RF(m_vertexCount == 0, "[Geometry Error]: Duplicated Call");
		return PlaneGeometryGenerator::Generate(
			width, height, widthSegments, heightSegments,
			m_vertexBufferId, m_indexBufferId, m_vertexCount, m_indexCount);
	}

	/* ���� ������Ʈ���� �����ϴ� �Լ� */
	bool Geometry::GenerateBox(float width, float height, float depth, unsigned widthSegments, unsigned heightSegments, unsigned depthSegments)
	{
		CHECK_PRINT_RF(m_vertexCount == 0, "[Geometry Error]: Duplicated Call");
		return BoxGeometryGenerator::Generate(
			width, height, depth, widthSegments, heightSegments, depthSegments,
			m_vertexBufferId, m_indexBufferId, m_vertexCount, m_indexCount);
	}

	/* ��ü ������Ʈ���� �����ϴ� �Լ� */
	bool Geometry::GenerateSphere(float radius, unsigned widthSegments, unsigned heightSegments)
	{
		CHECK_PRINT_RF(m_vertexCount == 0, "[Geometry Error]: Duplicated Call");
		return SphereGeometryGenerator::Generate(radius, widthSegments, heightSegments,
			m_vertexBufferId, m_indexBufferId, m_vertexCount, m_indexCount);
	}

	/* ���� ������Ʈ���� �����ϴ� �Լ� */
	bool Geometry::GenerateCylinder(float topRadius, float bottomRadius, float height, unsigned radialSegments, unsigned heightSegments)
	{
		CHECK_PRINT_RF(m_vertexCount == 0, "[Geometry Error]: Duplicated Call");
		return CylinderGeometryGenerator::Generate(topRadius, bottomRadius, height, radialSegments, heightSegments,
			m_vertexBufferId, m_indexBufferId, m_vertexCount, m_indexCount);
	}

	/* ������Ʈ ���Ͽ��� ������Ʈ�� �����͸� ������ �����ϴ� �Լ� */
	bool Geometry::GenerateFromObj(const std::string & filePath)
	{
		CHECK_PRINT_RF(m_vertexCount == 0, "[Geometry Error]: Duplicated Call");
		return ObjLoader::Load(filePath, m_vertexBufferId, m_vertexCount, m_stride, m_flag);
	}

}
