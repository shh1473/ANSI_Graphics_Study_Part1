#include "ansi_resource_storage.h"

#include "resource/shader/ansi_shader.h"
#include "resource/geometry/ansi_geometry.h"
#include "resource/texture/ansi_texture.h"
#include "utility/shader_loader/ansi_shader_loader.h"
#include "utility/texture_loader/ansi_texture_loader.h"

namespace ansi
{

	/* ������ */
	ResourceStorage::ResourceStorage()
		: m_shaders()
		, m_geometries()
		, m_textures()
	{

	}

	/* �Ҹ��� */
	ResourceStorage::~ResourceStorage()
	{
		for (auto iter = m_shaders.begin(); iter != m_shaders.end(); ++iter) { SAFE_DELETE(*iter); }
		for (auto iter = m_geometries.begin(); iter != m_geometries.end(); ++iter) { SAFE_DELETE(*iter); }
		for (auto iter = m_textures.begin(); iter != m_textures.end(); ++iter) { SAFE_DELETE(*iter); }
	}

	/* ���̴� �ڿ��� �����ϴ� �Լ� */
	Shader * ResourceStorage::CreateShader(const std::string & filePath)
	{
		unsigned shaderId{ 0 };
		if (!ShaderLoader::Load(filePath, shaderId)) { return nullptr; }
		m_shaders.push_back(new Shader(shaderId));

		return m_shaders.back();
	}

	/* ������Ʈ�� �ڿ��� �����ϴ� �Լ� */
	Geometry * ResourceStorage::CreateGeometry()
	{
		m_geometries.push_back(new Geometry());

		return m_geometries.back();
	}

	/* �ؽ�ó �ڿ��� �����ϴ� �Լ� */
	Texture * ResourceStorage::CreateTexture(const std::string & filePath)
	{
		unsigned textureId{ 0 };
		int width{ 0 };
		int height{ 0 };
		if (!TextureLoader::Load(filePath, width, height, textureId)) { return nullptr; }
		m_textures.push_back(new Texture(textureId, static_cast<unsigned>(width), static_cast<unsigned>(height)));

		return m_textures.back();
	}

}
