#pragma once

#include "common/ansi_common.h"
#include "common/ansi_common_render.h"

namespace ansi
{

	/* ���� ���� */
	class Shader;
	class Geometry;
	class Texture;

	/* �ڿ� ����� Ŭ���� */
	class ResourceStorage
	{
	public:
		/* ������ */
		explicit ResourceStorage();
		/* �Ҹ��� */
		~ResourceStorage();

		/* ���̴� �ڿ��� �����ϴ� �Լ�
		* @param filePath - ���� ���
		* @returns ������ ���̴� �ڿ�
		*/
		Shader * CreateShader(const std::string & filePath);
		/* ������Ʈ�� �ڿ��� �����ϴ� �Լ�
		* @returns ������ ������Ʈ�� �ڿ�
		*/
		Geometry * CreateGeometry();
		/* �ؽ�ó �ڿ��� �����ϴ� �Լ�
		* @param filePath - ���� ���
		* @returns ������ �ؽ�ó �ڿ�
		*/
		Texture * CreateTexture(const std::string & filePath);

	private:
		/* ���̴� �ڿ� �迭 */
		std::vector<Shader *> m_shaders;
		/* ������Ʈ�� �ڿ� �迭 */
		std::vector<Geometry *> m_geometries;
		/* �ؽ�ó �ڿ� �迭 */
		std::vector<Texture *> m_textures;

	};

}
