#pragma once

#include "object/component/ansi_component.h"
#include "utility/state_checker/ansi_state_checker_math.h"

namespace ansi
{

	/* 트랜스폼 컴포넌트 클래스 */
	class Transform : public Component
	{
	public:
		/* 생성자
		* @param object - 소유자 오브젝트
		*/
		explicit Transform(Object * object);

		/* 매 프레임마다 호출되는 지연 업데이트 함수 */
		bool OnLateUpdate() override;

		/* 트랜스폼을 초기화하는 함수 */
		void Reset();

		/* 임의의 방향 벡터에 본 트랜스폼의 회전을 적용했을 때의 방향 (기본: +Z 방향 벡터)
		* @param direction - 임의의 방향 벡터
		*/
		glm::vec3 GetLookAt(const glm::vec3 & direction = glm::vec3(0.0f, 0.0f, 1.0f)) const;

		/* Setter - 위치 */
		void SetPosition(const glm::vec3 & position) { m_position.Set(position); }
		/* Setter - 위치 */
		void SetPosition(float x, float y, float z) { m_position.Set(x, y, z); }
		/* Setter - 위치의 X 요소 */
		void SetPositionX(float x) { m_position.SetX(x); }
		/* Setter - 위치의 Y 요소 */
		void SetPositionY(float y) { m_position.SetY(y); }
		/* Setter - 위치의 Z 요소 */
		void SetPositionZ(float z) { m_position.SetZ(z); }
		/* Setter - 오일러각 회전 순서 */
		void SetEulerOrder(EulerOrder order) { m_eulerOrder = order; }
		/* Setter - 회전, 오일러각 회전 순서 (기본: XYZ) */
		void SetRotation(const glm::vec3 & rotation) { m_rotation.Set(rotation); }
		/* Setter - 회전, 오일러각 회전 순서 (기본: XYZ) */
		void SetRotation(float x, float y, float z) { m_rotation.Set(x, y, z); }
		/* Setter - 회전의 X 요소 */
		void SetRotationX(float x) { m_rotation.SetX(x); }
		/* Setter - 회전의 Y 요소 */
		void SetRotationY(float y) { m_rotation.SetY(y); }
		/* Setter - 회전의 Z 요소 */
		void SetRotationZ(float z) { m_rotation.SetZ(z); }
		/* Setter - 크기 */
		void SetScale(const glm::vec3 & scale) { m_scale.Set(scale); }
		/* Setter - 크기 */
		void SetScale(float x, float y, float z) { m_scale.Set(x, y, z); }
		/* Setter - 크기 */
		void SetScale(float scale) { m_scale.Set(scale, scale, scale); }
		/* Setter - 크기의 X 요소 */
		void SetScaleX(float x) { m_scale.SetX(x); }
		/* Setter - 크기의 Y 요소 */
		void SetScaleY(float y) { m_scale.SetY(y); }
		/* Setter - 크기의 Z 요소 */
		void SetScaleZ(float z) { m_scale.SetZ(z); }

		/* Adder - 위치 */
		void AddPosition(const glm::vec3 & position) { m_position.Add(position); }
		/* Adder - 위치 */
		void AddPosition(float x, float y, float z) { m_position.Add(x, y, z); }
		/* Adder - 위치의 X 요소 */
		void AddPositionX(float x) { m_position.AddX(x); }
		/* Adder - 위치의 Y 요소 */
		void AddPositionY(float y) { m_position.AddY(y); }
		/* Adder - 위치의 Z 요소 */
		void AddPositionZ(float z) { m_position.AddZ(z); }
		/* Adder - 회전 */
		void AddRotation(const glm::vec3 & rotation) { m_rotation.Add(rotation); }
		/* Adder - 회전 */
		void AddRotation(float x, float y, float z) { m_rotation.Add(x, y, z); }
		/* Adder - 회전의 X 요소 */
		void AddRotationX(float x) { m_rotation.AddX(x); }
		/* Adder - 회전의 Y 요소 */
		void AddRotationY(float y) { m_rotation.AddY(y); }
		/* Adder - 회전의 Z 요소 */
		void AddRotationZ(float z) { m_rotation.AddZ(z); }
		/* Adder - 크기 */
		void AddScale(const glm::vec3 & scale) { m_scale.Add(scale); }
		/* Adder - 크기 */
		void AddScale(float x, float y, float z) { m_scale.Add(x, y, z); }
		/* Adder - 크기의 X 요소 */
		void AddScaleX(float x) { m_scale.AddX(x); }
		/* Adder - 크기의 Y 요소 */
		void AddScaleY(float y) { m_scale.AddY(y); }
		/* Adder - 크기의 Z 요소 */
		void AddScaleZ(float z) { m_scale.AddZ(z); }

		/* Getter - 이번 프레임에 월드 행렬이 변경되었는지 여부 */
		bool GetIsChangedMatrix() const { return m_isChangedMatrix; }
		/* Getter - 오일러각 회전 순서 */
		EulerOrder GetEulerOrder() const { return m_eulerOrder; }
		/* Getter - 위치 */
		const glm::vec3 & GetPosition() const { return m_position.Get(); }
		/* Getter - 회전 */
		const glm::vec3 & GetRotation() const { return m_rotation.Get(); }
		/* Getter - 크기 */
		const glm::vec3 & GetScale() const { return m_scale.Get(); }
		/* Getter - 월드 좌표계의 최종 위치 (부모의 트랜스폼을 모두 반영한 위치) */
		const glm::vec3 & GetWorldPosition() const { return m_worldPosition; }
		/* Getter - 월드 행렬 */
		const glm::mat4 & GetWorldMatrix() const { return m_worldMatrix; }
		/* Getter - 부모의 월드 행렬 */
		const glm::mat4 & GetParentMatrix() const { return m_parentMatrix; }

	private:
		/* 이번 프레임에 월드 행렬이 변경되었는지 여부 */
		bool m_isChangedMatrix;
		/* 오일러각 회전 순서 */
		EulerOrder m_eulerOrder;
		/* 월드 좌표계의 최종 위치 */
		glm::vec3 m_worldPosition;
		/* 로컬 행렬 */
		glm::mat4 m_localMatrix;
		/* 월드 행렬 */
		glm::mat4 m_worldMatrix;
		/* 부모의 월드 행렬 */
		glm::mat4 m_parentMatrix;
		/* 위치 (상태 검사) */
		StateCheckerVec3 m_position;
		/* 회전 (상태 검사) */
		StateCheckerVec3 m_rotation;
		/* 크기 (상태 검사) */
		StateCheckerVec3 m_scale;

	};

}