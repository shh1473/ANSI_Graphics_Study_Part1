#include "ansi_texture.h"

namespace ansi
{

	/* 持失切 */
	Texture::Texture(unsigned id, unsigned width, unsigned height) :
		m_id(id),
		m_width(width),
		m_height(height)
	{

	}

	/* 社瑚切 */
	Texture::~Texture()
	{
		GL_CHECK(glDeleteTextures(1, &m_id));
	}

}
