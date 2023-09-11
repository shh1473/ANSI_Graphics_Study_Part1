#include "ansi_transform.h"

#include "object/ansi_object.h"

namespace ansi
{

	/* 생성자 */
	Transform::Transform(Object * object)
		: Component(object)
		, m_isChangedMatrix(false)
		, m_eulerOrder(EulerOrder::XYZ)
		, m_worldPosition(0.0f)
		, m_localMatrix(1.0f)
		, m_worldMatrix(1.0f)
		, m_position(0.0f)
		, m_rotation(0.0f)
		, m_scale(1.0f)
		, m_parentMatrix(1.0f)
	{

	}

	/* 매 프레임마다 호출되는 지연 업데이트 함수 */
	bool Transform::OnLateUpdate()
	{
		/* 이번 프레임에 로컬 트랜스폼이 변경되었는지 여부 (월드 행렬 업데이트 필요 여부 확인용) */
		static bool isChangedTransform{ false };
		isChangedTransform = false;

		/* 위치, 회전, 크기 중 하나라도 바뀌었을 경우 */
		if (m_position.Check() || m_rotation.Check() || m_scale.Check())
		{
			isChangedTransform = true;

			/* 위치 적용 */
			m_localMatrix = glm::translate(glm::mat4(1.0f), m_position.Get());
			/* 쿼터니언을 사용해 회전 적용 */
			m_localMatrix *= glm::mat4_cast(EulerToQuat(m_rotation.Get(), m_eulerOrder));
			/* 크기 적용 */
			m_localMatrix *= glm::scale(glm::mat4(1.0f), m_scale.Get());

			m_position.Reset();
			m_rotation.Reset();
			m_scale.Reset();
		}

		/* 로컬 트랜스폼이 변경되었거나, 부모의 월드 행렬이 변경되었을 경우 */
		if (isChangedTransform || (GetObject()->GetParent() && GetObject()->GetParent()->GetTransform()->m_isChangedMatrix))
		{
			m_isChangedMatrix = true;

			/* 월드 행렬을 로컬 행렬로 설정 */
			m_worldMatrix = m_localMatrix;

			/* 부모가 있을 경우, 부모의 월드 행렬을 반영 */
			if (GetObject()->GetParent()) { m_worldMatrix = m_parentMatrix * m_worldMatrix; }

			/* 자식이 있을 경우, 자신의 월드 행렬을 자식들의 부모 월드 행렬로 설정 */
			for (const auto & iter : GetObject()->GetChildren())
			{
				iter.second->GetTransform()->m_parentMatrix = m_worldMatrix;
			}

			/* 월드 행렬에서 위치를 추출하여 설정 */
			m_worldPosition = glm::vec3(m_worldMatrix[3]);
		}
		/* 월드 행렬을 변경할 필요가 없을 경우, 이번 프레임에 변경되지 않았음을 설정 */
		else { m_isChangedMatrix = false; }

		return true;
	}

	/* 트랜스폼을 초기화하는 함수 */
	void Transform::Reset()
	{
		m_position.Set(glm::vec3(0.0f));
		m_rotation.Set(glm::vec3(0.0f));
		m_scale.Set(glm::vec3(1.0f));
	}

	/* 임의의 방향에 본 회전을 적용했을 때의 결과 방향 */
	glm::vec3 Transform::GetLookAt(const glm::vec3 & direction) const
	{
		return glm::normalize(glm::mat3(m_worldMatrix) * direction);
	}

}