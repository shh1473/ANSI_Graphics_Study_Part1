#pragma once

#include "common/ansi_common.h"
#include "common/ansi_common_render.h"

namespace ansi
{

	class Texture;

	/* 프레임버퍼 자원 클래스 */
	class Framebuffer
	{
	public:
		/* 생성자 */
		explicit Framebuffer();
		/* 소멸자 */
		virtual ~Framebuffer();

		/* 초기화 함수
		* @param width - 너비
		* @param height - 높이
		* @param flag - 프레임버퍼 장착 플래그 (기본: {색상} | {깊이})
		*/
		bool Initialize(float width, float height, unsigned flag = FB_COLOR | FB_DEPTH);

		/* 크기를 업데이트하는 함수
		* @param width - 너비
		* @param height - 높이
		*/
		bool UpdateSize(float width, float height);

		/* Getter - 프레임버퍼 ID */
		unsigned GetId() const { return m_id; }
		/* Getter - 색상 텍스처 */
		unsigned GetColorTextureId() const;
		/* Getter - 깊이 텍스처 */
		unsigned GetDepthTextureId() const;

	private:
		/* 프레임버퍼 ID */
		unsigned m_id;
		/* 프레임버퍼 장착 플래그 */
		unsigned m_flag;
		/* 색상 텍스처 */
		Texture * m_colorTexture;
		/* 깊이 텍스처 */
		Texture * m_depthTexture;

	};

}
