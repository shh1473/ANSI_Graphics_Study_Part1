#pragma once

#include "common/ansi_common.h"
#include "common/ansi_common_render.h"

namespace ansi
{

	/* ¼ÎÀÌ´õ ÀÚ¿ø Å¬·¡½º */
	class Shader
	{
	public:
		/* »ý¼ºÀÚ
		* @param id - ¼ÎÀÌ´õ ID
		*/
		explicit Shader(unsigned id);
		/* ¼Ò¸êÀÚ */
		virtual ~Shader();

		/* Getter - ¼ÎÀÌ´õ ID */
		unsigned GetId() const { return m_id; }

	private:
		/* ¼ÎÀÌ´õ ID */
		const unsigned m_id;

	};

}
