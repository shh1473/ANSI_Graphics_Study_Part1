#pragma once

#include "common/ansi_common.h"
#include "common/ansi_common_render.h"

namespace ansi
{

	/* 전방 선언 */
	class Transform;

	/* 재질 클래스 */
	class Material
	{
	public:
		/* 생성자
		* @param shaderId - 셰이더 ID
		*/
		explicit Material(unsigned shaderId);

		/* 매 프레임마다 호출되는 유니폼 업데이트 함수 */
		virtual bool OnUpdateUniforms();

		/* Setter - 오브젝트 트랜스폼 */
		void SetTransform(Transform * transform) { m_transform = transform; }
		/* Setter - 셰이더 ID */
		void SetShaderId(unsigned shaderId) { m_shaderId = shaderId; }
		/* Setter - 텍스처 ID */
		void SetTextureId(unsigned index, unsigned textureId) { m_textureIds[index] = textureId; }
		/* Setter - 텍스처 종류 */
		void SetTextureType(unsigned index, TextureType textureType) { m_textureTypes[index] = textureType; }
		/* Setter - 정반사광 강도 */
		void SetSpecularIntensity(float specularIntensity) { m_specularIntensity = specularIntensity; }
		/* Setter - 정반사광 하이라이트 */
		void SetSpecularPower(float specularPower) { m_specularPower = specularPower; }
		/* Setter - 난반사 색상 */
		void SetColor(const glm::vec3 & color) { m_diffuseColor.r = color.r; m_diffuseColor.g = color.g; m_diffuseColor.b = color.b; }
		/* Setter - 불투명도 */
		void SetAlpha(float alpha) { m_diffuseColor.a = alpha; }
		/* Setter - 깊이 테스트 활성화 여부 */
		void SetIsEnableDepthTest(bool isEnableDepthTest) { m_isEnableDepthTest = isEnableDepthTest; }
		/* Setter - 깊이 쓰기 활성화 여부 */
		void SetIsEnableDepthWrite(bool isEnableDepthWrite) { m_isEnableDepthWrite = isEnableDepthWrite; }
		/* Setter - 깊이 비교 함수 */
		void SetDepthFunc(CompareFunc depthFunc) { m_depthFunc = depthFunc; }
		/* Setter - 삼각형 채우기 모드 */
		void SetFillMode(FillMode fillMode) { m_fillMode = fillMode; }
		/* Setter - 삼각형 컬링 모드 */
		void SetCullMode(CullMode cullMode) { m_cullMode = cullMode; }
		/* Setter - 삼각형 앞면 판정 방향 */
		void SetFrontFace(FrontFace frontFace) { m_frontFace = frontFace; }

		/* Getter - 오브젝트 트랜스폼 */
		Transform * GetTransform() const { return m_transform; }
		/* Getter - 셰이더 ID */
		unsigned GetShaderId() const { return m_shaderId; }
		/* Getter - 텍스처 ID */
		unsigned GetTextureId(unsigned index) { return m_textureIds[index]; }
		/* Getter - 텍스처 종류 */
		TextureType GetTextureType(unsigned index) { return m_textureTypes[index]; }
		/* Getter - 정반사광 강도 */
		float GetSpecularIntensity() const { return m_specularIntensity; }
		/* Getter - 정반사광 하이라이트 */
		float GetSpecularPower() const { return m_specularPower; }
		/* Getter - 난반사 색상 */
		const glm::vec4 & GetDiffuseColor() const { return m_diffuseColor; }
		/* Getter - 깊이 테스트 활성화 여부 */
		bool GetIsEnableDepthTest() const { return m_isEnableDepthTest; }
		/* Getter - 깊이 쓰기 활성화 여부 */
		bool GetIsEnableDepthWrite() const { return m_isEnableDepthWrite; }
		/* Getter - 깊이 비교 함수 */
		CompareFunc GetDepthFunc() const { return m_depthFunc; }
		/* Getter - 삼각형 채우기 모드 */
		FillMode GetFillMode() const { return m_fillMode; }
		/* Getter - 삼각형 컬링 모드 */
		CullMode GetCullMode() const { return m_cullMode; }
		/* Getter - 삼각형 앞면 판정 방향 */
		FrontFace GetFrontFace() const { return m_frontFace; }

	protected:
		/* 정수 1개 유니폼 설정
		* @param name 이름
		* @param value 값
		*/
		bool SetUniform1i(const std::string & name, int value);
		/* 부동소수점 1개 유니폼 설정
		* @param name 이름
		* @param value 값
		*/
		bool SetUniform1f(const std::string & name, float value);
		/* 부동소수점 1개 배열 유니폼 설정
		* @param name 이름
		* @param count 개수
		* @param startAddress 배열 시작 주소
		*/
		bool SetUniform1fv(const std::string & name, int count, float * startAddress);
		/* 부동소수점 2개 유니폼 설정
		* @param name 이름
		* @param value 값
		*/
		bool SetUniform2f(const std::string & name, const glm::vec2 & value);
		/* 부동소수점 2개 배열 유니폼 설정
		* @param name 이름
		* @param count 개수
		* @param startAddress 배열 시작 주소 (첫 번째 벡터의 x 요소의 주소)
		*/
		bool SetUniform2fv(const std::string & name, int count, float * startAddress);
		/* 부동소수점 3개 유니폼 설정
		* @param name 이름
		* @param value 값
		*/
		bool SetUniform3f(const std::string & name, const glm::vec3 & value);
		/* 부동소수점 3개 배열 유니폼 설정
		* @param name 이름
		* @param count 개수
		* @param startAddress 배열 시작 주소 (첫 번째 벡터의 x 요소의 주소)
		*/
		bool SetUniform3fv(const std::string & name, int count, float * startAddress);
		/* 부동소수점 4개 유니폼 설정
		* @param name 이름
		* @param value 값
		*/
		bool SetUniform4f(const std::string & name, const glm::vec4 & value);
		/* 부동소수점 4개 배열 유니폼 설정
		* @param name 이름
		* @param count 개수
		* @param startAddress 배열 시작 주소 (첫 번째 벡터의 x 요소의 주소)
		*/
		bool SetUniform4fv(const std::string & name, int count, float * startAddress);
		/* 4x4 행렬 유니폼 설정
		* @param name 이름
		* @param value 값
		*/
		bool SetUniform4x4f(const std::string & name, const glm::mat4 & value);
		/* 4x4 행렬 배열 유니폼 설정
		* @param name 이름
		* @param count 개수
		* @param startAddress 배열 시작 주소 (첫 번째 행렬의 1행 1열 요소의 주소)
		*/
		bool SetUniform4x4fv(const std::string & name, int count, float * startAddress);

	private:
		/* 유니폼 이름을 받아 위치를 반환하는 함수
		* @param name 이름
		* @returns 위치
		*/
		int GetUniformLocation(const std::string & name);

	private:
		/* 오브젝트 트랜스폼 */
		Transform * m_transform;
		/* 셰이더 ID */
		unsigned m_shaderId;
		/* 텍스처 ID 배열 */
		unsigned m_textureIds[MaxTextureCount];
		/* 텍스처 종류 배열 */
		TextureType m_textureTypes[MaxTextureCount];
		/* 정반사광 강도 */
		float m_specularIntensity;
		/* 정반사광 하이라이트 */
		float m_specularPower;
		/* 난반사 색상 */
		glm::vec4 m_diffuseColor;
		/* 깊이 테스트 활성화 여부 */
		bool m_isEnableDepthTest;
		/* 깊이 쓰기 활성화 여부 */
		bool m_isEnableDepthWrite;
		/* 깊이 비교 함수 */
		CompareFunc m_depthFunc;
		/* 삼각형 채우기 모드 */
		FillMode m_fillMode;
		/* 삼각형 컬링 모드 */
		CullMode m_cullMode;
		/* 삼각형 앞면 판정 방향 */
		FrontFace m_frontFace;
		/* 유니폼 위치 캐시 테이블 */
		std::unordered_map<std::string, int> m_uniformLocationCache;

	};

}
