#include "ansi_material.h"

#include "resource/shader/ansi_shader.h"

namespace ansi
{

	/* ������ */
	Material::Material(unsigned shaderId)
		: m_transform(nullptr)
		, m_shaderId(shaderId)
		, m_textureIds()
		, m_textureTypes()
		, m_specularIntensity(1.0f)
		, m_specularPower(32.0f)
		, m_diffuseColor(1.0f)
		, m_isEnableDepthTest(true)
		, m_isEnableDepthWrite(true)
		, m_depthFunc(CompareFunc::LessEqual)
		, m_fillMode(FillMode::Solid)
		, m_cullMode(CullMode::Back)
		, m_frontFace(FrontFace::CounterClockWise)
		, m_uniformLocationCache()
	{
		for (unsigned i{ 0 }; i < MaxTextureCount; ++i) {
			m_textureIds[i] = 0;
			m_textureTypes[i] = TextureType::Two;
		}
	}

	/* �� �����Ӹ��� ȣ��Ǵ� ������ ������Ʈ �Լ� */
	bool Material::OnUpdateUniforms()
	{
		// ������� (�������̵� �ʿ�)
		return true;
	}

	/* ���� 1�� ������ ���� */
	bool Material::SetUniform1i(const std::string & name, int value)
	{
		GL_CHECK(glUniform1iv(GetUniformLocation(name), 1, &value));
		return true;
	}

	/* �ε��Ҽ��� 1�� ������ ���� */
	bool Material::SetUniform1f(const std::string & name, float value)
	{
		GL_CHECK(glUniform1fv(GetUniformLocation(name), 1, &value));
		return true;
	}

	/* �ε��Ҽ��� 1�� �迭 ������ ���� */
	bool Material::SetUniform1fv(const std::string & name, int count, float * startAddress)
	{
		GL_CHECK(glUniform1fv(GetUniformLocation(name), count, startAddress));
		return true;
	}

	/* �ε��Ҽ��� 2�� ������ ���� */
	bool Material::SetUniform2f(const std::string & name, const glm::vec2 & value)
	{
		GL_CHECK(glUniform2fv(GetUniformLocation(name), 1, &value.x));
		return true;
	}

	/* �ε��Ҽ��� 2�� �迭 ������ ���� */
	bool Material::SetUniform2fv(const std::string & name, int count, float * startAddress)
	{
		GL_CHECK(glUniform2fv(GetUniformLocation(name), count, startAddress));
		return true;
	}

	/* �ε��Ҽ��� 3�� ������ ���� */
	bool Material::SetUniform3f(const std::string & name, const glm::vec3 & value)
	{
		GL_CHECK(glUniform3fv(GetUniformLocation(name), 1, &value.x));
		return true;
	}

	/* �ε��Ҽ��� 3�� �迭 ������ ���� */
	bool Material::SetUniform3fv(const std::string & name, int count, float * startAddress)
	{
		GL_CHECK(glUniform3fv(GetUniformLocation(name), count, startAddress));
		return true;
	}

	/* �ε��Ҽ��� 4�� ������ ���� */
	bool Material::SetUniform4f(const std::string & name, const glm::vec4 & value)
	{
		GL_CHECK(glUniform4fv(GetUniformLocation(name), 1, &value.x));
		return true;
	}

	/* �ε��Ҽ��� 4�� �迭 ������ ���� */
	bool Material::SetUniform4fv(const std::string & name, int count, float * startAddress)
	{
		GL_CHECK(glUniform4fv(GetUniformLocation(name), count, startAddress));
		return true;
	}

	/* 4x4 ��� ������ ���� */
	bool Material::SetUniform4x4f(const std::string & name, const glm::mat4 & value)
	{
		GL_CHECK(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &value[0][0]));
		return true;
	}

	/* 4x4 ��� �迭 ������ ���� */
	bool Material::SetUniform4x4fv(const std::string & name, int count, float * startAddress)
	{
		GL_CHECK(glUniformMatrix4fv(GetUniformLocation(name), count, GL_FALSE, startAddress));
		return true;
	}

	/* ������ �̸��� �޾� ��ġ�� ��ȯ�ϴ� �Լ� */
	int Material::GetUniformLocation(const std::string & name)
	{
		/* �̹� ĳ�� ���̺� ����� ���, ĳ�õ� ��ġ�� ��� */
		if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end()) { return m_uniformLocationCache[name]; }

		/* ������ ��ġ �������� */
		int location = glGetUniformLocation(m_shaderId, name.c_str());
		/* �ش� �̸��� �ش��ϴ� �������� ���� ���, ���� �޽��� ��� */
		CHECK_PRINT(location != -1, "[Uniform Error]: Can't find \"" + name + "\" uniform in shader");
		/* ĳ�� ���̺� ��� */
		m_uniformLocationCache[name] = location;

		return location;
	}

}
