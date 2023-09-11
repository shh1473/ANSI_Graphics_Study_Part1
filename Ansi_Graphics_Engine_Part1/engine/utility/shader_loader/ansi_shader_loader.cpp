#include "ansi_shader_loader.h"

namespace ansi
{

	/* .shader ������ �ҷ����� �Լ� */
	bool ShaderLoader::Load(const std::string & filePath, unsigned & shaderId)
	{
		/* ���̴� ���α׷� ���� */
		GL_CHECK_RF(shaderId = glCreateProgram());

		unsigned shaderStageIndex{ 0 };
		std::vector<unsigned> ids(static_cast<unsigned>(ShaderStage::length), 0);
		std::vector<std::string> sources(static_cast<unsigned>(ShaderStage::length), "");

		/* ���̴� ���� �Ľ� */
		CHECK_RF(ParseShader(filePath, sources));

		/* ���ؽ� ���̴� ������ */
		shaderStageIndex = static_cast<unsigned>(ShaderStage::Vertex);
		CHECK_RF(CompileShader(GL_VERTEX_SHADER, filePath, sources[shaderStageIndex], ids[shaderStageIndex]));
		/* ���ؽ� ���̴� ���� */
		GL_CHECK(glAttachShader(shaderId, ids[shaderStageIndex]));

		/* �����׸�Ʈ ���̴� ������ */
		shaderStageIndex = static_cast<unsigned>(ShaderStage::Fragment);
		CHECK_RF(CompileShader(GL_FRAGMENT_SHADER, filePath, sources[shaderStageIndex], ids[shaderStageIndex]));
		/* �����׸�Ʈ ���̴� ���� */
		GL_CHECK(glAttachShader(shaderId, ids[shaderStageIndex]));

		/* ������ ���̴��� ���α׷��� ���� */
		GL_CHECK(glLinkProgram(shaderId));
		/* ���̴� ���α׷� ���� */
		GL_CHECK(glValidateProgram(shaderId));

		/* ���α׷� ���� �� �����ߴ� ���̴��� ���� */
		for (unsigned i{ 0 }; i < ids.size(); ++i)
		{
			if (ids[i] != 0) { GL_CHECK(glDeleteShader(ids[i])); }
		}

		return true;
	}

	/* ���̴� ������ �Ľ��ϴ� �Լ� */
	bool ShaderLoader::ParseShader(const std::string & filePath, std::vector<std::string> & sources)
	{
		std::ifstream fileStream(filePath);
		std::string line;
		std::stringstream shaderStreams[static_cast<unsigned>(ShaderStage::length)];
		ShaderStage stage{ ShaderStage::Vertex };

		/* ���� ���� */
		CHECK_PRINT_RF(fileStream.good(), "[Shader Error]: Can't find \"" + filePath + "\" file");
		/* ������ ������ �ݺ� */
		while (getline(fileStream, line))
		{
			/* "shader_vertex"�� ������ ���, ���ؽ� ���̴� �ܰ�� ���� */
			if (line.find("shader_vertex") != std::string::npos) { stage = ShaderStage::Vertex; }
			/* "shader_fragment"�� ������ ���, �����׸�Ʈ ���̴� �ܰ�� ���� */
			else if (line.find("shader_fragment") != std::string::npos) { stage = ShaderStage::Fragment; }
			/* ���� ���̴� �ܰ迡 �����Ǵ� ���̴� �ڵ� ��Ʈ���� �Ľ��� ���ڿ��� �߰� */
			else { shaderStreams[static_cast<unsigned>(stage)] << line << '\n'; }
		}

		/* �ϼ��� ���̴� �ڵ� ��Ʈ���� ���ڿ��� ���� */
		for (unsigned i{ 0 }; i < static_cast<unsigned>(ShaderStage::length); ++i) { sources[i] = shaderStreams[i].str(); }

		return true;
	}

	/* �Ľ̵� �ڵ带 �������ϴ� �Լ� */
	bool ShaderLoader::CompileShader(unsigned stage, const std::string & filePath, const std::string & source, unsigned & shaderId)
	{
		/* ���̴� ���� */
		CHECK_RF(shaderId = glCreateShader(stage));

		const char * src{ source.c_str() };
		/* ���̴� �ڵ� ���� */
		GL_CHECK(glShaderSource(shaderId, 1, &src, nullptr));
		/* ���̴� �ڵ� ������ */
		GL_CHECK(glCompileShader(shaderId));

		int result{ 0 };
		/* ������ ��� �������� */
		GL_CHECK(glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result));
		/* �������� �������� ��� */
		if (result == GL_FALSE)
		{
			int length{ 0 };
			/* ������ �α� ���� �������� */
			GL_CHECK(glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length));
			/* ������ �α� ���̸�ŭ�� ���ڿ� ���� */
			char * message{ new char[length] };

			/* ������ �α� ���� �������� */
			GL_CHECK(glGetShaderInfoLog(shaderId, length, &length, message));
			switch (stage)
			{
				case GL_VERTEX_SHADER: { PRINT_FL("[Shader Error]: Vertex Compilation, (" + filePath + ")"); break; }
				case GL_FRAGMENT_SHADER: { PRINT_FL("[Shader Error]: Fragment Compilation, (" + filePath + ")"); break; }
			}
			PRINT(message);

			/* ������ �α� ���� ���� */
			SAFE_DELETE_ARRAY(message);
			/* �����Ͽ� ������ ���̴� ���� */
			GL_CHECK(glDeleteShader(shaderId));

			return false;
		}

		return true;
	}

}
