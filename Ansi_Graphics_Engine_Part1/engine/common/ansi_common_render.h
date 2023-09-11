#pragma once

#include "common/ansi_common.h"

namespace ansi
{

	/* 프레임버퍼 플래그 - 색상 */
	constexpr unsigned FB_COLOR{ 1 << 0 };
	/* 프레임버퍼 플래그 - 깊이 */
	constexpr unsigned FB_DEPTH{ 1 << 1 };

	/* 버텍스 배열 플래그 - 텍스처 좌표 */
	constexpr unsigned VA_TEXCOORD{ 1 << 0 };
	/* 버텍스 배열 플래그 - 법선 */
	constexpr unsigned VA_NORMAL{ 1 << 1 };

	/* 최대 텍스처 사용 가능 개수 */
	constexpr unsigned MaxTextureCount{ 8 };

	/* 카메라 종류 */
	enum class CameraType
	{
		/* 시야 */
		View,
		/* 광원 */
		Light,
		/* 종류의 개수 */
		length,
	};

	/* 렌더러 종류 */
	enum class RendererType
	{
		/* 일반 */
		Normal,
		/* HUD */
		Hud,
		/* 종류의 개수 */
		length,
	};

	/* 텍스처 종류 */
	enum class TextureType
	{
		/* 2차원 */
		Two = GL_TEXTURE_2D,
		/* 3차원 */
		Three = GL_TEXTURE_3D,
		/* 큐브 */
		Cube = GL_TEXTURE_CUBE_MAP,
		/* 2차원 배열 */
		TwoArray = GL_TEXTURE_2D_ARRAY,
	};

	/* 기본 도형 종류 */
	enum class PrimitiveTopology
	{
		/* 점 */
		Points = GL_POINTS,
		/* 2개씩 이어지는 선 */
		Lines = GL_LINES,
		/* 계속 이어지는 선 */
		LineStrip = GL_LINE_STRIP,
		/* 계속 이어지고 시작과 끝이 이어지는 선 */
		LineLoop = GL_LINE_LOOP,
		/* 3개씩 이어지는 삼각형 */
		Triangles = GL_TRIANGLES,
		/* 계속 이어지는 삼각형 */
		TriangleStrip = GL_TRIANGLE_STRIP,
	};

	/* 비교 함수 */
	enum class CompareFunc
	{
		/* 항상 true 값 반환 */
		Always = GL_ALWAYS,
		/* 항상 false 값 반환 */
		Never = GL_NEVER,
		/* 같을 시 true 값 반환 */
		Equal = GL_EQUAL,
		/* 다를 시 true 값 반환 */
		NotEqual = GL_NOTEQUAL,
		/* 작을 시 true 값 반환 */
		Less = GL_LESS,
		/* 작거나 같을 시 true 값 반환 */
		LessEqual = GL_LEQUAL,
		/* 클 시 true 값 반환 */
		Greater = GL_GREATER,
		/* 크거나 같을 시 true 값 반환 */
		GreaterEqual = GL_GEQUAL,
	};

	/* 채우기 모드 */
	enum class FillMode
	{
		/* 점 */
		Point = GL_POINT,
		/* 선 */
		Wireframe = GL_LINE,
		/* 면 */
		Solid = GL_FILL,
	};

	/* 컬링 모드 */
	enum class CullMode
	{
		/* 컬링하지 않음 */
		None = NULL,
		/* 앞면 컬링 */
		Front = GL_FRONT,
		/* 뒷면 컬링 */
		Back = GL_BACK,
		/* 앞면과 뒷면 컬링 */
		FrontAndBack = GL_FRONT_AND_BACK,
	};

	/* 앞면 판정 방향 */
	enum class FrontFace
	{
		/* 시계 방향 */
		ClockWise = GL_CW,
		/* 반시계 방향 */
		CounterClockWise = GL_CCW,
	};

}
