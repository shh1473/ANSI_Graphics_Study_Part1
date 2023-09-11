#include "ansi_shader_loader.h"

namespace ansi
{

	/* .shader 파일을 불러오는 함수 */
	bool ShaderLoader::Load(const std::string & filePath, unsigned & shaderId)
	{
		/* 셰이더 프로그램 생성 */
		GL_CHECK_RF(shaderId = glCreateProgram());

		unsigned shaderStageIndex{ 0 };
		std::vector<unsigned> ids(static_cast<unsigned>(ShaderStage::length), 0);
		std::vector<std::string> sources(static_cast<unsigned>(ShaderStage::length), "");

		/* 셰이더 파일 파싱 */
		CHECK_RF(ParseShader(filePath, sources));

		/* 버텍스 셰이더 컴파일 */
		shaderStageIndex = static_cast<unsigned>(ShaderStage::Vertex);
		CHECK_RF(CompileShader(GL_VERTEX_SHADER, filePath, sources[shaderStageIndex], ids[shaderStageIndex]));
		/* 버텍스 셰이더 장착 */
		GL_CHECK(glAttachShader(shaderId, ids[shaderStageIndex]));

		/* 프래그먼트 셰이더 컴파일 */
		shaderStageIndex = static_cast<unsigned>(ShaderStage::Fragment);
		CHECK_RF(CompileShader(GL_FRAGMENT_SHADER, filePath, sources[shaderStageIndex], ids[shaderStageIndex]));
		/* 프래그먼트 셰이더 장착 */
		GL_CHECK(glAttachShader(shaderId, ids[shaderStageIndex]));

		/* 장착한 셰이더를 프로그램에 연결 */
		GL_CHECK(glLinkProgram(shaderId));
		/* 셰이더 프로그램 검증 */
		GL_CHECK(glValidateProgram(shaderId));

		/* 프로그램 연결 후 장착했던 셰이더는 제거 */
		for (unsigned i{ 0 }; i < ids.size(); ++i)
		{
			if (ids[i] != 0) { GL_CHECK(glDeleteShader(ids[i])); }
		}

		return true;
	}

	/* 셰이더 파일을 파싱하는 함수 */
	bool ShaderLoader::ParseShader(const std::string & filePath, std::vector<std::string> & sources)
	{
		std::ifstream fileStream(filePath);
		std::string line;
		std::stringstream shaderStreams[static_cast<unsigned>(ShaderStage::length)];
		ShaderStage stage{ ShaderStage::Vertex };

		/* 파일 열기 */
		CHECK_PRINT_RF(fileStream.good(), "[Shader Error]: Can't find \"" + filePath + "\" file");
		/* 파일의 끝까지 반복 */
		while (getline(fileStream, line))
		{
			/* "shader_vertex"가 등장할 경우, 버텍스 셰이더 단계로 변경 */
			if (line.find("shader_vertex") != std::string::npos) { stage = ShaderStage::Vertex; }
			/* "shader_fragment"가 등장할 경우, 프래그먼트 셰이더 단계로 변경 */
			else if (line.find("shader_fragment") != std::string::npos) { stage = ShaderStage::Fragment; }
			/* 현재 셰이더 단계에 대응되는 셰이더 코드 스트림에 파싱한 문자열을 추가 */
			else { shaderStreams[static_cast<unsigned>(stage)] << line << '\n'; }
		}

		/* 완성된 셰이더 코드 스트림을 문자열로 저장 */
		for (unsigned i{ 0 }; i < static_cast<unsigned>(ShaderStage::length); ++i) { sources[i] = shaderStreams[i].str(); }

		return true;
	}

	/* 파싱된 코드를 컴파일하는 함수 */
	bool ShaderLoader::CompileShader(unsigned stage, const std::string & filePath, const std::string & source, unsigned & shaderId)
	{
		/* 셰이더 생성 */
		CHECK_RF(shaderId = glCreateShader(stage));

		const char * src{ source.c_str() };
		/* 셰이더 코드 설정 */
		GL_CHECK(glShaderSource(shaderId, 1, &src, nullptr));
		/* 셰이더 코드 컴파일 */
		GL_CHECK(glCompileShader(shaderId));

		int result{ 0 };
		/* 컴파일 결과 가져오기 */
		GL_CHECK(glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result));
		/* 컴파일이 실패했을 경우 */
		if (result == GL_FALSE)
		{
			int length{ 0 };
			/* 컴파일 로그 길이 가져오기 */
			GL_CHECK(glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length));
			/* 컴파일 로그 길이만큼의 문자열 생성 */
			char * message{ new char[length] };

			/* 컴파일 로그 내용 가져오기 */
			GL_CHECK(glGetShaderInfoLog(shaderId, length, &length, message));
			switch (stage)
			{
				case GL_VERTEX_SHADER: { PRINT_FL("[Shader Error]: Vertex Compilation, (" + filePath + ")"); break; }
				case GL_FRAGMENT_SHADER: { PRINT_FL("[Shader Error]: Fragment Compilation, (" + filePath + ")"); break; }
			}
			PRINT(message);

			/* 컴파일 로그 내용 제거 */
			SAFE_DELETE_ARRAY(message);
			/* 컴파일에 실패한 셰이더 제거 */
			GL_CHECK(glDeleteShader(shaderId));

			return false;
		}

		return true;
	}

}
