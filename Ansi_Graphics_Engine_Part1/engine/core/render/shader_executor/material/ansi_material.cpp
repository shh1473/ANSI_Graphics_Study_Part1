#include "ansi_material.h"

#include "resource/shader/ansi_shader.h"

namespace ansi
{

	/* 생성자 */
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

	/* 매 프레임마다 호출되는 유니폼 업데이트 함수 */
	bool Material::OnUpdateUniforms()
	{
		// 비어있음 (오버라이딩 필요)
		return true;
	}

	/* 정수 1개 유니폼 설정 */
	bool Material::SetUniform1i(const std::string & name, int value)
	{
		GL_CHECK(glUniform1iv(GetUniformLocation(name), 1, &value));
		return true;
	}

	/* 부동소수점 1개 유니폼 설정 */
	bool Material::SetUniform1f(const std::string & name, float value)
	{
		GL_CHECK(glUniform1fv(GetUniformLocation(name), 1, &value));
		return true;
	}

	/* 부동소수점 1개 배열 유니폼 설정 */
	bool Material::SetUniform1fv(const std::string & name, int count, float * startAddress)
	{
		GL_CHECK(glUniform1fv(GetUniformLocation(name), count, startAddress));
		return true;
	}

	/* 부동소수점 2개 유니폼 설정 */
	bool Material::SetUniform2f(const std::string & name, const glm::vec2 & value)
	{
		GL_CHECK(glUniform2fv(GetUniformLocation(name), 1, &value.x));
		return true;
	}

	/* 부동소수점 2개 배열 유니폼 설정 */
	bool Material::SetUniform2fv(const std::string & name, int count, float * startAddress)
	{
		GL_CHECK(glUniform2fv(GetUniformLocation(name), count, startAddress));
		return true;
	}

	/* 부동소수점 3개 유니폼 설정 */
	bool Material::SetUniform3f(const std::string & name, const glm::vec3 & value)
	{
		GL_CHECK(glUniform3fv(GetUniformLocation(name), 1, &value.x));
		return true;
	}

	/* 부동소수점 3개 배열 유니폼 설정 */
	bool Material::SetUniform3fv(const std::string & name, int count, float * startAddress)
	{
		GL_CHECK(glUniform3fv(GetUniformLocation(name), count, startAddress));
		return true;
	}

	/* 부동소수점 4개 유니폼 설정 */
	bool Material::SetUniform4f(const std::string & name, const glm::vec4 & value)
	{
		GL_CHECK(glUniform4fv(GetUniformLocation(name), 1, &value.x));
		return true;
	}

	/* 부동소수점 4개 배열 유니폼 설정 */
	bool Material::SetUniform4fv(const std::string & name, int count, float * startAddress)
	{
		GL_CHECK(glUniform4fv(GetUniformLocation(name), count, startAddress));
		return true;
	}

	/* 4x4 행렬 유니폼 설정 */
	bool Material::SetUniform4x4f(const std::string & name, const glm::mat4 & value)
	{
		GL_CHECK(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &value[0][0]));
		return true;
	}

	/* 4x4 행렬 배열 유니폼 설정 */
	bool Material::SetUniform4x4fv(const std::string & name, int count, float * startAddress)
	{
		GL_CHECK(glUniformMatrix4fv(GetUniformLocation(name), count, GL_FALSE, startAddress));
		return true;
	}

	/* 유니폼 이름을 받아 위치를 반환하는 함수 */
	int Material::GetUniformLocation(const std::string & name)
	{
		/* 이미 캐시 테이블에 등록한 경우, 캐시된 위치를 사용 */
		if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end()) { return m_uniformLocationCache[name]; }

		/* 유니폼 위치 가져오기 */
		int location = glGetUniformLocation(m_shaderId, name.c_str());
		/* 해당 이름에 해당하는 유니폼이 없을 경우, 에러 메시지 출력 */
		CHECK_PRINT(location != -1, "[Uniform Error]: Can't find \"" + name + "\" uniform in shader");
		/* 캐시 테이블에 등록 */
		m_uniformLocationCache[name] = location;

		return location;
	}

}
