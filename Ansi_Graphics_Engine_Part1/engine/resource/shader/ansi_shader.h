#pragma once

#include "common/ansi_common.h"
#include "common/ansi_common_render.h"

namespace ansi
{

	/* ���̴� �ڿ� Ŭ���� */
	class Shader
	{
	public:
		/* ������
		* @param id - ���̴� ID
		*/
		explicit Shader(unsigned id);
		/* �Ҹ��� */
		virtual ~Shader();

		/* Getter - ���̴� ID */
		unsigned GetId() const { return m_id; }

	private:
		/* ���̴� ID */
		const unsigned m_id;

	};

}
