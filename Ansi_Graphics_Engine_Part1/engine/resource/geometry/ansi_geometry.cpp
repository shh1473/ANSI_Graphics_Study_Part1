/* 'reinterpret_cast': 'unsigned int'에서 더 큰 'unsigned int *'(으)로의 변환 경고 해제 */
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

	/* 생성자 */
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

	/* 소멸자 */
	Geometry::~Geometry()
	{
		if (m_vertexBufferId) { GL_CHECK(glDeleteBuffers(1, &m_vertexBufferId)); }
		if (m_indexBufferId) { GL_CHECK(glDeleteBuffers(1, &m_indexBufferId)); }
		for (auto & inputElements : m_inputElements) { SAFE_DELETE(inputElements); }
	}

	/* 특정 버텍스 요소로만 이뤄진 입력 요소를 생성하는 함수 */
	InputElements * Geometry::CreateInputElements(unsigned flag)
	{
		/* 지오메트리를 생성하지 않은 상태로 입력 요소를 생성하려 한 경우 중단 */
		CHECK_PRINT_RN(m_vertexCount != 0, "[Geometry Error]: No Geometry Data");

		/* 버텍스 배열 생성 */
		unsigned id{ 0 };
		GL_CHECK_RN(glGenVertexArrays(1, &id));
		GL_CHECK_RN(glBindVertexArray(id));
		GL_CHECK_RN(glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId));

		std::vector<unsigned> elementCounts;
		std::vector<unsigned *> offsets;

		/* 기본적으로 위치와 그에 대한 오프셋 추가 */
		unsigned offset{ 0 };
		elementCounts.push_back(3);
		offsets.push_back(reinterpret_cast<unsigned *>(offset));
		/* 현재 오프셋 증가 (위치 요소의 용량만큼) */
		offset += 3 * sizeof(float);

		/* 생성한 지오메트리 데이터에 텍스처 좌표 요소가 있는 경우 */
		if (m_flag & VA_TEXCOORD)
		{
			/* 텍스처 좌표 플래그를 설정한 경우 */
			if (flag & VA_TEXCOORD)
			{
				/* 텍스처 좌표와 그에 대한 오프셋 추가 */
				elementCounts.push_back(2);
				offsets.push_back(reinterpret_cast<unsigned *>(offset));
			}
			/* 현재 오프셋 증가 (텍스처 좌표 요소의 용량만큼) */
			offset += 2 * sizeof(float);
		}

		/* 생성한 지오메트리 데이터에 법선 요소가 있는 경우 */
		if (m_flag & VA_NORMAL)
		{
			/* 법선 플래그를 설정한 경우 */
			if (flag & VA_NORMAL)
			{
				/* 법선과 그에 대한 오프셋 추가 */
				elementCounts.push_back(3);
				offsets.push_back(reinterpret_cast<unsigned *>(offset));
			}
			/* 현재 오프셋 증가 (법선 요소의 용량만큼) */
			offset += 3 * sizeof(float);
		}

		/* 기본 위치 요소와 플래그로 설정한 추가 요소를 포함해 버텍스 배열 생성 */
		for (unsigned i{ 0 }; i < elementCounts.size(); ++i)
		{
			GL_CHECK_RN(glEnableVertexAttribArray(i));
			GL_CHECK_RN(glVertexAttribPointer(i, elementCounts[i], GL_FLOAT, GL_FALSE, m_stride, reinterpret_cast<const void *>(offsets[i])));
		}

		/* 입력 요소 생성 */
		m_inputElements.push_back(new InputElements(id, m_indexBufferId, m_vertexCount, m_indexCount));

		return m_inputElements.back();
	}

	/* 평면 지오메트리를 생성하는 함수 */
	bool Geometry::GeneratePlane(float width, float height, unsigned widthSegments, unsigned heightSegments)
	{
		CHECK_PRINT_RF(m_vertexCount == 0, "[Geometry Error]: Duplicated Call");
		return PlaneGeometryGenerator::Generate(
			width, height, widthSegments, heightSegments,
			m_vertexBufferId, m_indexBufferId, m_vertexCount, m_indexCount);
	}

	/* 상자 지오메트리를 생성하는 함수 */
	bool Geometry::GenerateBox(float width, float height, float depth, unsigned widthSegments, unsigned heightSegments, unsigned depthSegments)
	{
		CHECK_PRINT_RF(m_vertexCount == 0, "[Geometry Error]: Duplicated Call");
		return BoxGeometryGenerator::Generate(
			width, height, depth, widthSegments, heightSegments, depthSegments,
			m_vertexBufferId, m_indexBufferId, m_vertexCount, m_indexCount);
	}

	/* 구체 지오메트리를 생성하는 함수 */
	bool Geometry::GenerateSphere(float radius, unsigned widthSegments, unsigned heightSegments)
	{
		CHECK_PRINT_RF(m_vertexCount == 0, "[Geometry Error]: Duplicated Call");
		return SphereGeometryGenerator::Generate(radius, widthSegments, heightSegments,
			m_vertexBufferId, m_indexBufferId, m_vertexCount, m_indexCount);
	}

	/* 원통 지오메트리를 생성하는 함수 */
	bool Geometry::GenerateCylinder(float topRadius, float bottomRadius, float height, unsigned radialSegments, unsigned heightSegments)
	{
		CHECK_PRINT_RF(m_vertexCount == 0, "[Geometry Error]: Duplicated Call");
		return CylinderGeometryGenerator::Generate(topRadius, bottomRadius, height, radialSegments, heightSegments,
			m_vertexBufferId, m_indexBufferId, m_vertexCount, m_indexCount);
	}

	/* 오브젝트 파일에서 지오메트리 데이터를 가져와 생성하는 함수 */
	bool Geometry::GenerateFromObj(const std::string & filePath)
	{
		CHECK_PRINT_RF(m_vertexCount == 0, "[Geometry Error]: Duplicated Call");
		return ObjLoader::Load(filePath, m_vertexBufferId, m_vertexCount, m_stride, m_flag);
	}

}
