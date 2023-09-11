#pragma once

#include "common/ansi_common_render.h"
#include "object/component/ansi_component.h"

namespace ansi
{

	/* 전방 선언 */
	class InputParam;
	class Material;
	class InputElements;

	/* 렌더러 컴포넌트 클래스 */
	class Renderer : public Component
	{
	public:
		/* 생성자
		* @param object - 소유자 오브젝트
		* @param inputElements - 입력 요소
		* @param material - 재질
		* @param type - 렌더러 종류
		*/
		explicit Renderer(Object * object, InputElements * inputElements, Material * material, RendererType type = RendererType::Normal);
		/* 소멸자 */
		virtual ~Renderer();

		/* Setter - 그림자 생성 여부 */
		void SetIsCastShadow(bool isCastShadow) { m_isCastShadow = isCastShadow; }

		/* Getter - 그림자 생성 여부 */
		bool GetIsCastShadow() const { return m_isCastShadow; }
		/* Getter - 재질 */
		Material * GetMaterial() const { return m_material; }
		/* Getter - 입력 관련 상태 집합 */
		InputParam * GetInput() const { return m_inputParam; }

	private:
		/* 렌더러 종류 */
		const RendererType m_type;
		/* 그림자 생성 여부 */
		bool m_isCastShadow;
		/* 재질 */
		Material * m_material;
		/* 입력 관련 상태 집합 */
		InputParam * m_inputParam;

	};

}