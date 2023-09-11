#pragma once

#include "common/ansi_common.h"
#include "common/ansi_common_render.h"

namespace ansi
{

	class Texture;

	/* �����ӹ��� �ڿ� Ŭ���� */
	class Framebuffer
	{
	public:
		/* ������ */
		explicit Framebuffer();
		/* �Ҹ��� */
		virtual ~Framebuffer();

		/* �ʱ�ȭ �Լ�
		* @param width - �ʺ�
		* @param height - ����
		* @param flag - �����ӹ��� ���� �÷��� (�⺻: {����} | {����})
		*/
		bool Initialize(float width, float height, unsigned flag = FB_COLOR | FB_DEPTH);

		/* ũ�⸦ ������Ʈ�ϴ� �Լ�
		* @param width - �ʺ�
		* @param height - ����
		*/
		bool UpdateSize(float width, float height);

		/* Getter - �����ӹ��� ID */
		unsigned GetId() const { return m_id; }
		/* Getter - ���� �ؽ�ó */
		unsigned GetColorTextureId() const;
		/* Getter - ���� �ؽ�ó */
		unsigned GetDepthTextureId() const;

	private:
		/* �����ӹ��� ID */
		unsigned m_id;
		/* �����ӹ��� ���� �÷��� */
		unsigned m_flag;
		/* ���� �ؽ�ó */
		Texture * m_colorTexture;
		/* ���� �ؽ�ó */
		Texture * m_depthTexture;

	};

}
