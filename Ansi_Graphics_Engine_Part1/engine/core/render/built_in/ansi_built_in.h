#pragma once

#include "depth_material/ansi_depth_material.h"

namespace ansi
{

	/* 전방 선언 */
	class Shader;
	class Geometry;
	class InputElements;
	class InputParam;

	/* 내장 자원 */
	class BuiltIn
	{
	public:
		/* 생성자 */
		explicit BuiltIn();
		/* 소멸자 */
		~BuiltIn();

		/* 초기화 함수 */
		bool Initialize();

		/* Getter - 깊이 기록 재질 */
		DepthMaterial * GetDepthMaterial() const { return m_depthMaterial; }
		/* Getter - 화면에 맞는 사각형 입력 관련 상태 집합 */
		InputParam * GetScreenAlignedQuadIP() const { return m_screenAlignedQuadIP; }

	private:
		/* 깊이 기록 셰이더 */
		Shader * m_depthShader{ nullptr };
		/* 깊이 기록 재질 */
		DepthMaterial * m_depthMaterial{ nullptr };
		/* 화면에 맞는 사각형 지오메트리 */
		Geometry * m_screenAlignedQuad{ nullptr };
		/* 화면에 맞는 사각형 입력 요소 */
		InputElements * m_screenAlignedQuadIE{ nullptr };
		/* 화면에 맞는 사각형 입력 관련 상태 집합 */
		InputParam * m_screenAlignedQuadIP{ nullptr };

	};

}
