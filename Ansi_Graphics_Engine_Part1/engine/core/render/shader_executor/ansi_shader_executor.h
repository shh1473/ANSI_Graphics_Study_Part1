#pragma once

#include "core/render/shader_executor/material/ansi_material.h"
#include "utility/state_checker/ansi_state_checker.h"

namespace ansi
{

	/* 전방 선언 */
	class Material;

	/* 셰이더 실행기 클래스 */
	class ShaderExecutor
	{
	public:
		/* 생성자 */
		explicit ShaderExecutor();
		/* 소멸자 */
		~ShaderExecutor();

		/* OpenGL 컨텍스트의 셰이더 관련 상태를 적용하는 함수
		* @param material - 재질
		*/
		bool Apply(Material * material);
		/* OpenGL 컨텍스트의 셰이더 관련 상태를 초기화하는 함수 */
		bool Reset();

	private:
		/* 기본 재질 */
		Material * m_defaultMaterial;
		/* 깊이 쓰기 활성화 여부 */
		bool m_isEnableDepthWrite;
		/* 셰이더 ID (상태 검사) */
		StateChecker<unsigned> m_shaderId;
		/* 텍스처 ID 배열 (상태 검사) */
		StateArrayChecker<unsigned, MaxTextureCount> m_textureIds;
		/* 텍스처 종류 배열 (상태 검사) */
		StateArrayChecker<unsigned, MaxTextureCount> m_textureTypes;
		/* 깊이 테스트 활성화 여부 (상태 검사) */
		StateChecker<bool> m_isEnableDepthTest;
		/* 깊이 비교 함수 (상태 검사) */
		StateChecker<CompareFunc> m_depthFunc;
		/* 삼각형 채우기 모드 (상태 검사) */
		StateChecker<FillMode> m_fillMode;
		/* 삼각형 컬링 모드 (상태 검사) */
		StateChecker<CullMode> m_cullMode;
		/* 삼각형 앞면 판정 방향 (상태 검사) */
		StateChecker<FrontFace> m_frontFace;

	};

}
