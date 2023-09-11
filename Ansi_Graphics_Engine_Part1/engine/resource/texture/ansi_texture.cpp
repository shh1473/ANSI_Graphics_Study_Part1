#include "ansi_texture.h"

namespace ansi
{

	/* ������ */
	Texture::Texture(unsigned id, unsigned width, unsigned height) :
		m_id(id),
		m_width(width),
		m_height(height)
	{

	}

	/* �Ҹ��� */
	Texture::~Texture()
	{
		GL_CHECK(glDeleteTextures(1, &m_id));
	}

}
