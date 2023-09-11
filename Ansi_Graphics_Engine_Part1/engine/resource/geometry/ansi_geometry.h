#pragma once

#include "common/ansi_common.h"
#include "common/ansi_common_render.h"

namespace ansi
{

	/* ���� ���� */
	class InputElements;

	/* ������Ʈ�� �ڿ� Ŭ���� */
	class Geometry
	{
	public:
		/* ������ */
		explicit Geometry();
		/* �Ҹ��� */
		virtual ~Geometry();

		/* Ư�� ���ؽ� ��ҷθ� �̷��� �Է� ��Ҹ� �����ϴ� �Լ�
		* @param flag - ������ ���ؽ� ��� �÷��� (�⺻: {�ؽ�ó ��ǥ} | {����})
		* @returns ������ �Է� ���
		*/
		InputElements * CreateInputElements(unsigned flag = VA_TEXCOORD | VA_NORMAL);

		/* ��� ������Ʈ���� �����ϴ� �Լ�
		* @param width - �ʺ�
		* @param height - ����
		* @param widthSegments - �ʺ� ���� �� (�⺻: 1)
		* @param heightSegments - ���� ���� �� (�⺻: 1)
		*/
		bool GeneratePlane(float width, float height, unsigned widthSegments = 1, unsigned heightSegments = 1);
		/* ���� ������Ʈ���� �����ϴ� �Լ�
		* @param width - �ʺ�
		* @param height - ����
		* @param depth - ����
		* @param widthSegments - �ʺ� ���� �� (�⺻: 1)
		* @param heightSegments - ���� ���� �� (�⺻: 1)
		* @param depthSegments - ���� ���� �� (�⺻: 1)
		*/
		bool GenerateBox(float width, float height, float depth, unsigned widthSegments = 1, unsigned heightSegments = 1, unsigned depthSegments = 1);
		/* ��ü ������Ʈ���� �����ϴ� �Լ�
		* @param radius - ������
		* @param widthSegments - �ʺ� ���� �� (�⺻: 16)
		* @param heightSegments - ���� ���� �� (�⺻: 8)
		*/
		bool GenerateSphere(float radius, unsigned widthSegments = 16, unsigned heightSegments = 8);
		/* ���� ������Ʈ���� �����ϴ� �Լ�
		* @param topRadius - ��� ������
		* @param bottomRadius - �ϴ� ������
		* @param height - ����
		* @param radialSegments - �Ѳ� ���� �� (�⺻: 16)
		* @param heightSegments - ���� ���� �� (�⺻: 1)
		*/
		bool GenerateCylinder(float topRadius, float bottomRadius, float height, unsigned radialSegments = 16, unsigned heightSegments = 1);
		/* ������Ʈ ���Ͽ��� ������Ʈ�� �����͸� ������ �����ϴ� �Լ�
		* @param filePath - ������Ʈ ���� ���
		*/
		bool GenerateFromObj(const std::string & filePath);
		
	private:
		/* ���ؽ� ���� */
		unsigned m_vertexCount;
		/* �ε��� ���� */
		unsigned m_indexCount;
		/* ���ؽ� ���� ID */
		unsigned m_vertexBufferId;
		/* �ε��� ���� ID */
		unsigned m_indexBufferId;
		/* �� ���ؽ� �� ���� �ּ� ���� */
		unsigned m_stride;
		/* ������ ������Ʈ���� ���ؽ� ��� �÷��� */
		unsigned m_flag;
		/* �Է� ��� �迭 */
		std::vector<InputElements *> m_inputElements;

	};

}
