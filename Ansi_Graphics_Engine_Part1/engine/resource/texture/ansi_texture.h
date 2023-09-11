#pragma once

#include "common/ansi_common.h"

namespace ansi
{

	/* 텍스처 자원 클래스 */
	class Texture
	{
	public:
		/* 생성자
		* @param id - 텍스처 ID
		* @param width - 너비
		* @param height - 높이
		*/
		explicit Texture(unsigned id, unsigned width, unsigned height);
		/* 소멸자 */
		virtual ~Texture();

		/* Getter - 텍스처 ID */
		unsigned GetId() const { return m_id; }
		/* Getter - 너비 */
		unsigned GetWidth() const { return m_width; }
		/* Getter - 높이 */
		unsigned GetHeight() const { return m_height; }

	private:
		/* 텍스처 ID */
		const unsigned m_id;
		/* 너비 */
		const unsigned m_width;
		/* 높이 */
		const unsigned m_height;

	};

}
