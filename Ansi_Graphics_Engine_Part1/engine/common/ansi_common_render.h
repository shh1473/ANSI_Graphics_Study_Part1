#pragma once

#include "common/ansi_common.h"

namespace ansi
{

	/* �����ӹ��� �÷��� - ���� */
	constexpr unsigned FB_COLOR{ 1 << 0 };
	/* �����ӹ��� �÷��� - ���� */
	constexpr unsigned FB_DEPTH{ 1 << 1 };

	/* ���ؽ� �迭 �÷��� - �ؽ�ó ��ǥ */
	constexpr unsigned VA_TEXCOORD{ 1 << 0 };
	/* ���ؽ� �迭 �÷��� - ���� */
	constexpr unsigned VA_NORMAL{ 1 << 1 };

	/* �ִ� �ؽ�ó ��� ���� ���� */
	constexpr unsigned MaxTextureCount{ 8 };

	/* ī�޶� ���� */
	enum class CameraType
	{
		/* �þ� */
		View,
		/* ���� */
		Light,
		/* ������ ���� */
		length,
	};

	/* ������ ���� */
	enum class RendererType
	{
		/* �Ϲ� */
		Normal,
		/* HUD */
		Hud,
		/* ������ ���� */
		length,
	};

	/* �ؽ�ó ���� */
	enum class TextureType
	{
		/* 2���� */
		Two = GL_TEXTURE_2D,
		/* 3���� */
		Three = GL_TEXTURE_3D,
		/* ť�� */
		Cube = GL_TEXTURE_CUBE_MAP,
		/* 2���� �迭 */
		TwoArray = GL_TEXTURE_2D_ARRAY,
	};

	/* �⺻ ���� ���� */
	enum class PrimitiveTopology
	{
		/* �� */
		Points = GL_POINTS,
		/* 2���� �̾����� �� */
		Lines = GL_LINES,
		/* ��� �̾����� �� */
		LineStrip = GL_LINE_STRIP,
		/* ��� �̾����� ���۰� ���� �̾����� �� */
		LineLoop = GL_LINE_LOOP,
		/* 3���� �̾����� �ﰢ�� */
		Triangles = GL_TRIANGLES,
		/* ��� �̾����� �ﰢ�� */
		TriangleStrip = GL_TRIANGLE_STRIP,
	};

	/* �� �Լ� */
	enum class CompareFunc
	{
		/* �׻� true �� ��ȯ */
		Always = GL_ALWAYS,
		/* �׻� false �� ��ȯ */
		Never = GL_NEVER,
		/* ���� �� true �� ��ȯ */
		Equal = GL_EQUAL,
		/* �ٸ� �� true �� ��ȯ */
		NotEqual = GL_NOTEQUAL,
		/* ���� �� true �� ��ȯ */
		Less = GL_LESS,
		/* �۰ų� ���� �� true �� ��ȯ */
		LessEqual = GL_LEQUAL,
		/* Ŭ �� true �� ��ȯ */
		Greater = GL_GREATER,
		/* ũ�ų� ���� �� true �� ��ȯ */
		GreaterEqual = GL_GEQUAL,
	};

	/* ä��� ��� */
	enum class FillMode
	{
		/* �� */
		Point = GL_POINT,
		/* �� */
		Wireframe = GL_LINE,
		/* �� */
		Solid = GL_FILL,
	};

	/* �ø� ��� */
	enum class CullMode
	{
		/* �ø����� ���� */
		None = NULL,
		/* �ո� �ø� */
		Front = GL_FRONT,
		/* �޸� �ø� */
		Back = GL_BACK,
		/* �ո�� �޸� �ø� */
		FrontAndBack = GL_FRONT_AND_BACK,
	};

	/* �ո� ���� ���� */
	enum class FrontFace
	{
		/* �ð� ���� */
		ClockWise = GL_CW,
		/* �ݽð� ���� */
		CounterClockWise = GL_CCW,
	};

}
