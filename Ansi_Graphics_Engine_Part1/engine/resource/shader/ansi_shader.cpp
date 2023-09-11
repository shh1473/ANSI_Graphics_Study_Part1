#include "ansi_shader.h"

namespace ansi
{

	/* 持失切 */
	Shader::Shader(unsigned id)
		: m_id(id)
	{

	}

	/* 社瑚切 */
	Shader::~Shader()
	{
		GL_CHECK(glDeleteProgram(m_id));
	}

}
