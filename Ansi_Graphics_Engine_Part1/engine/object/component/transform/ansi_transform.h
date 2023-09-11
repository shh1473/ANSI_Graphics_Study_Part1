#pragma once

#include "object/component/ansi_component.h"
#include "utility/state_checker/ansi_state_checker_math.h"

namespace ansi
{

	/* Ʈ������ ������Ʈ Ŭ���� */
	class Transform : public Component
	{
	public:
		/* ������
		* @param object - ������ ������Ʈ
		*/
		explicit Transform(Object * object);

		/* �� �����Ӹ��� ȣ��Ǵ� ���� ������Ʈ �Լ� */
		bool OnLateUpdate() override;

		/* Ʈ�������� �ʱ�ȭ�ϴ� �Լ� */
		void Reset();

		/* ������ ���� ���Ϳ� �� Ʈ�������� ȸ���� �������� ���� ���� (�⺻: +Z ���� ����)
		* @param direction - ������ ���� ����
		*/
		glm::vec3 GetLookAt(const glm::vec3 & direction = glm::vec3(0.0f, 0.0f, 1.0f)) const;

		/* Setter - ��ġ */
		void SetPosition(const glm::vec3 & position) { m_position.Set(position); }
		/* Setter - ��ġ */
		void SetPosition(float x, float y, float z) { m_position.Set(x, y, z); }
		/* Setter - ��ġ�� X ��� */
		void SetPositionX(float x) { m_position.SetX(x); }
		/* Setter - ��ġ�� Y ��� */
		void SetPositionY(float y) { m_position.SetY(y); }
		/* Setter - ��ġ�� Z ��� */
		void SetPositionZ(float z) { m_position.SetZ(z); }
		/* Setter - ���Ϸ��� ȸ�� ���� */
		void SetEulerOrder(EulerOrder order) { m_eulerOrder = order; }
		/* Setter - ȸ��, ���Ϸ��� ȸ�� ���� (�⺻: XYZ) */
		void SetRotation(const glm::vec3 & rotation) { m_rotation.Set(rotation); }
		/* Setter - ȸ��, ���Ϸ��� ȸ�� ���� (�⺻: XYZ) */
		void SetRotation(float x, float y, float z) { m_rotation.Set(x, y, z); }
		/* Setter - ȸ���� X ��� */
		void SetRotationX(float x) { m_rotation.SetX(x); }
		/* Setter - ȸ���� Y ��� */
		void SetRotationY(float y) { m_rotation.SetY(y); }
		/* Setter - ȸ���� Z ��� */
		void SetRotationZ(float z) { m_rotation.SetZ(z); }
		/* Setter - ũ�� */
		void SetScale(const glm::vec3 & scale) { m_scale.Set(scale); }
		/* Setter - ũ�� */
		void SetScale(float x, float y, float z) { m_scale.Set(x, y, z); }
		/* Setter - ũ�� */
		void SetScale(float scale) { m_scale.Set(scale, scale, scale); }
		/* Setter - ũ���� X ��� */
		void SetScaleX(float x) { m_scale.SetX(x); }
		/* Setter - ũ���� Y ��� */
		void SetScaleY(float y) { m_scale.SetY(y); }
		/* Setter - ũ���� Z ��� */
		void SetScaleZ(float z) { m_scale.SetZ(z); }

		/* Adder - ��ġ */
		void AddPosition(const glm::vec3 & position) { m_position.Add(position); }
		/* Adder - ��ġ */
		void AddPosition(float x, float y, float z) { m_position.Add(x, y, z); }
		/* Adder - ��ġ�� X ��� */
		void AddPositionX(float x) { m_position.AddX(x); }
		/* Adder - ��ġ�� Y ��� */
		void AddPositionY(float y) { m_position.AddY(y); }
		/* Adder - ��ġ�� Z ��� */
		void AddPositionZ(float z) { m_position.AddZ(z); }
		/* Adder - ȸ�� */
		void AddRotation(const glm::vec3 & rotation) { m_rotation.Add(rotation); }
		/* Adder - ȸ�� */
		void AddRotation(float x, float y, float z) { m_rotation.Add(x, y, z); }
		/* Adder - ȸ���� X ��� */
		void AddRotationX(float x) { m_rotation.AddX(x); }
		/* Adder - ȸ���� Y ��� */
		void AddRotationY(float y) { m_rotation.AddY(y); }
		/* Adder - ȸ���� Z ��� */
		void AddRotationZ(float z) { m_rotation.AddZ(z); }
		/* Adder - ũ�� */
		void AddScale(const glm::vec3 & scale) { m_scale.Add(scale); }
		/* Adder - ũ�� */
		void AddScale(float x, float y, float z) { m_scale.Add(x, y, z); }
		/* Adder - ũ���� X ��� */
		void AddScaleX(float x) { m_scale.AddX(x); }
		/* Adder - ũ���� Y ��� */
		void AddScaleY(float y) { m_scale.AddY(y); }
		/* Adder - ũ���� Z ��� */
		void AddScaleZ(float z) { m_scale.AddZ(z); }

		/* Getter - �̹� �����ӿ� ���� ����� ����Ǿ����� ���� */
		bool GetIsChangedMatrix() const { return m_isChangedMatrix; }
		/* Getter - ���Ϸ��� ȸ�� ���� */
		EulerOrder GetEulerOrder() const { return m_eulerOrder; }
		/* Getter - ��ġ */
		const glm::vec3 & GetPosition() const { return m_position.Get(); }
		/* Getter - ȸ�� */
		const glm::vec3 & GetRotation() const { return m_rotation.Get(); }
		/* Getter - ũ�� */
		const glm::vec3 & GetScale() const { return m_scale.Get(); }
		/* Getter - ���� ��ǥ���� ���� ��ġ (�θ��� Ʈ�������� ��� �ݿ��� ��ġ) */
		const glm::vec3 & GetWorldPosition() const { return m_worldPosition; }
		/* Getter - ���� ��� */
		const glm::mat4 & GetWorldMatrix() const { return m_worldMatrix; }
		/* Getter - �θ��� ���� ��� */
		const glm::mat4 & GetParentMatrix() const { return m_parentMatrix; }

	private:
		/* �̹� �����ӿ� ���� ����� ����Ǿ����� ���� */
		bool m_isChangedMatrix;
		/* ���Ϸ��� ȸ�� ���� */
		EulerOrder m_eulerOrder;
		/* ���� ��ǥ���� ���� ��ġ */
		glm::vec3 m_worldPosition;
		/* ���� ��� */
		glm::mat4 m_localMatrix;
		/* ���� ��� */
		glm::mat4 m_worldMatrix;
		/* �θ��� ���� ��� */
		glm::mat4 m_parentMatrix;
		/* ��ġ (���� �˻�) */
		StateCheckerVec3 m_position;
		/* ȸ�� (���� �˻�) */
		StateCheckerVec3 m_rotation;
		/* ũ�� (���� �˻�) */
		StateCheckerVec3 m_scale;

	};

}