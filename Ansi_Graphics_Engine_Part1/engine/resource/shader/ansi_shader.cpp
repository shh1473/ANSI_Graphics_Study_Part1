#include "ansi_shader.h"

namespace ansi
{

	/* ������ */
	Shader::Shader(unsigned id)
		: m_id(id)
	{

	}

	/* �Ҹ��� */
	Shader::~Shader()
	{
		GL_CHECK(glDeleteProgram(m_id));
	}

}
