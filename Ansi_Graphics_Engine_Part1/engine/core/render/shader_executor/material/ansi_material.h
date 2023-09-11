#pragma once

#include "common/ansi_common.h"
#include "common/ansi_common_render.h"

namespace ansi
{

	/* ���� ���� */
	class Transform;

	/* ���� Ŭ���� */
	class Material
	{
	public:
		/* ������
		* @param shaderId - ���̴� ID
		*/
		explicit Material(unsigned shaderId);

		/* �� �����Ӹ��� ȣ��Ǵ� ������ ������Ʈ �Լ� */
		virtual bool OnUpdateUniforms();

		/* Setter - ������Ʈ Ʈ������ */
		void SetTransform(Transform * transform) { m_transform = transform; }
		/* Setter - ���̴� ID */
		void SetShaderId(unsigned shaderId) { m_shaderId = shaderId; }
		/* Setter - �ؽ�ó ID */
		void SetTextureId(unsigned index, unsigned textureId) { m_textureIds[index] = textureId; }
		/* Setter - �ؽ�ó ���� */
		void SetTextureType(unsigned index, TextureType textureType) { m_textureTypes[index] = textureType; }
		/* Setter - ���ݻ籤 ���� */
		void SetSpecularIntensity(float specularIntensity) { m_specularIntensity = specularIntensity; }
		/* Setter - ���ݻ籤 ���̶���Ʈ */
		void SetSpecularPower(float specularPower) { m_specularPower = specularPower; }
		/* Setter - ���ݻ� ���� */
		void SetColor(const glm::vec3 & color) { m_diffuseColor.r = color.r; m_diffuseColor.g = color.g; m_diffuseColor.b = color.b; }
		/* Setter - ������ */
		void SetAlpha(float alpha) { m_diffuseColor.a = alpha; }
		/* Setter - ���� �׽�Ʈ Ȱ��ȭ ���� */
		void SetIsEnableDepthTest(bool isEnableDepthTest) { m_isEnableDepthTest = isEnableDepthTest; }
		/* Setter - ���� ���� Ȱ��ȭ ���� */
		void SetIsEnableDepthWrite(bool isEnableDepthWrite) { m_isEnableDepthWrite = isEnableDepthWrite; }
		/* Setter - ���� �� �Լ� */
		void SetDepthFunc(CompareFunc depthFunc) { m_depthFunc = depthFunc; }
		/* Setter - �ﰢ�� ä��� ��� */
		void SetFillMode(FillMode fillMode) { m_fillMode = fillMode; }
		/* Setter - �ﰢ�� �ø� ��� */
		void SetCullMode(CullMode cullMode) { m_cullMode = cullMode; }
		/* Setter - �ﰢ�� �ո� ���� ���� */
		void SetFrontFace(FrontFace frontFace) { m_frontFace = frontFace; }

		/* Getter - ������Ʈ Ʈ������ */
		Transform * GetTransform() const { return m_transform; }
		/* Getter - ���̴� ID */
		unsigned GetShaderId() const { return m_shaderId; }
		/* Getter - �ؽ�ó ID */
		unsigned GetTextureId(unsigned index) { return m_textureIds[index]; }
		/* Getter - �ؽ�ó ���� */
		TextureType GetTextureType(unsigned index) { return m_textureTypes[index]; }
		/* Getter - ���ݻ籤 ���� */
		float GetSpecularIntensity() const { return m_specularIntensity; }
		/* Getter - ���ݻ籤 ���̶���Ʈ */
		float GetSpecularPower() const { return m_specularPower; }
		/* Getter - ���ݻ� ���� */
		const glm::vec4 & GetDiffuseColor() const { return m_diffuseColor; }
		/* Getter - ���� �׽�Ʈ Ȱ��ȭ ���� */
		bool GetIsEnableDepthTest() const { return m_isEnableDepthTest; }
		/* Getter - ���� ���� Ȱ��ȭ ���� */
		bool GetIsEnableDepthWrite() const { return m_isEnableDepthWrite; }
		/* Getter - ���� �� �Լ� */
		CompareFunc GetDepthFunc() const { return m_depthFunc; }
		/* Getter - �ﰢ�� ä��� ��� */
		FillMode GetFillMode() const { return m_fillMode; }
		/* Getter - �ﰢ�� �ø� ��� */
		CullMode GetCullMode() const { return m_cullMode; }
		/* Getter - �ﰢ�� �ո� ���� ���� */
		FrontFace GetFrontFace() const { return m_frontFace; }

	protected:
		/* ���� 1�� ������ ����
		* @param name �̸�
		* @param value ��
		*/
		bool SetUniform1i(const std::string & name, int value);
		/* �ε��Ҽ��� 1�� ������ ����
		* @param name �̸�
		* @param value ��
		*/
		bool SetUniform1f(const std::string & name, float value);
		/* �ε��Ҽ��� 1�� �迭 ������ ����
		* @param name �̸�
		* @param count ����
		* @param startAddress �迭 ���� �ּ�
		*/
		bool SetUniform1fv(const std::string & name, int count, float * startAddress);
		/* �ε��Ҽ��� 2�� ������ ����
		* @param name �̸�
		* @param value ��
		*/
		bool SetUniform2f(const std::string & name, const glm::vec2 & value);
		/* �ε��Ҽ��� 2�� �迭 ������ ����
		* @param name �̸�
		* @param count ����
		* @param startAddress �迭 ���� �ּ� (ù ��° ������ x ����� �ּ�)
		*/
		bool SetUniform2fv(const std::string & name, int count, float * startAddress);
		/* �ε��Ҽ��� 3�� ������ ����
		* @param name �̸�
		* @param value ��
		*/
		bool SetUniform3f(const std::string & name, const glm::vec3 & value);
		/* �ε��Ҽ��� 3�� �迭 ������ ����
		* @param name �̸�
		* @param count ����
		* @param startAddress �迭 ���� �ּ� (ù ��° ������ x ����� �ּ�)
		*/
		bool SetUniform3fv(const std::string & name, int count, float * startAddress);
		/* �ε��Ҽ��� 4�� ������ ����
		* @param name �̸�
		* @param value ��
		*/
		bool SetUniform4f(const std::string & name, const glm::vec4 & value);
		/* �ε��Ҽ��� 4�� �迭 ������ ����
		* @param name �̸�
		* @param count ����
		* @param startAddress �迭 ���� �ּ� (ù ��° ������ x ����� �ּ�)
		*/
		bool SetUniform4fv(const std::string & name, int count, float * startAddress);
		/* 4x4 ��� ������ ����
		* @param name �̸�
		* @param value ��
		*/
		bool SetUniform4x4f(const std::string & name, const glm::mat4 & value);
		/* 4x4 ��� �迭 ������ ����
		* @param name �̸�
		* @param count ����
		* @param startAddress �迭 ���� �ּ� (ù ��° ����� 1�� 1�� ����� �ּ�)
		*/
		bool SetUniform4x4fv(const std::string & name, int count, float * startAddress);

	private:
		/* ������ �̸��� �޾� ��ġ�� ��ȯ�ϴ� �Լ�
		* @param name �̸�
		* @returns ��ġ
		*/
		int GetUniformLocation(const std::string & name);

	private:
		/* ������Ʈ Ʈ������ */
		Transform * m_transform;
		/* ���̴� ID */
		unsigned m_shaderId;
		/* �ؽ�ó ID �迭 */
		unsigned m_textureIds[MaxTextureCount];
		/* �ؽ�ó ���� �迭 */
		TextureType m_textureTypes[MaxTextureCount];
		/* ���ݻ籤 ���� */
		float m_specularIntensity;
		/* ���ݻ籤 ���̶���Ʈ */
		float m_specularPower;
		/* ���ݻ� ���� */
		glm::vec4 m_diffuseColor;
		/* ���� �׽�Ʈ Ȱ��ȭ ���� */
		bool m_isEnableDepthTest;
		/* ���� ���� Ȱ��ȭ ���� */
		bool m_isEnableDepthWrite;
		/* ���� �� �Լ� */
		CompareFunc m_depthFunc;
		/* �ﰢ�� ä��� ��� */
		FillMode m_fillMode;
		/* �ﰢ�� �ø� ��� */
		CullMode m_cullMode;
		/* �ﰢ�� �ո� ���� ���� */
		FrontFace m_frontFace;
		/* ������ ��ġ ĳ�� ���̺� */
		std::unordered_map<std::string, int> m_uniformLocationCache;

	};

}
