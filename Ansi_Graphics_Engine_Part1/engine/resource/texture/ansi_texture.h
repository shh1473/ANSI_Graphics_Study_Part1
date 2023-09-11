#pragma once

#include "common/ansi_common.h"

namespace ansi
{

	/* �ؽ�ó �ڿ� Ŭ���� */
	class Texture
	{
	public:
		/* ������
		* @param id - �ؽ�ó ID
		* @param width - �ʺ�
		* @param height - ����
		*/
		explicit Texture(unsigned id, unsigned width, unsigned height);
		/* �Ҹ��� */
		virtual ~Texture();

		/* Getter - �ؽ�ó ID */
		unsigned GetId() const { return m_id; }
		/* Getter - �ʺ� */
		unsigned GetWidth() const { return m_width; }
		/* Getter - ���� */
		unsigned GetHeight() const { return m_height; }

	private:
		/* �ؽ�ó ID */
		const unsigned m_id;
		/* �ʺ� */
		const unsigned m_width;
		/* ���� */
		const unsigned m_height;

	};

}
