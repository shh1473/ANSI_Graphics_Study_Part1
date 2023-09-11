#include "ansi_transform.h"

#include "object/ansi_object.h"

namespace ansi
{

	/* ������ */
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

	/* �� �����Ӹ��� ȣ��Ǵ� ���� ������Ʈ �Լ� */
	bool Transform::OnLateUpdate()
	{
		/* �̹� �����ӿ� ���� Ʈ�������� ����Ǿ����� ���� (���� ��� ������Ʈ �ʿ� ���� Ȯ�ο�) */
		static bool isChangedTransform{ false };
		isChangedTransform = false;

		/* ��ġ, ȸ��, ũ�� �� �ϳ��� �ٲ���� ��� */
		if (m_position.Check() || m_rotation.Check() || m_scale.Check())
		{
			isChangedTransform = true;

			/* ��ġ ���� */
			m_localMatrix = glm::translate(glm::mat4(1.0f), m_position.Get());
			/* ���ʹϾ��� ����� ȸ�� ���� */
			m_localMatrix *= glm::mat4_cast(EulerToQuat(m_rotation.Get(), m_eulerOrder));
			/* ũ�� ���� */
			m_localMatrix *= glm::scale(glm::mat4(1.0f), m_scale.Get());

			m_position.Reset();
			m_rotation.Reset();
			m_scale.Reset();
		}

		/* ���� Ʈ�������� ����Ǿ��ų�, �θ��� ���� ����� ����Ǿ��� ��� */
		if (isChangedTransform || (GetObject()->GetParent() && GetObject()->GetParent()->GetTransform()->m_isChangedMatrix))
		{
			m_isChangedMatrix = true;

			/* ���� ����� ���� ��ķ� ���� */
			m_worldMatrix = m_localMatrix;

			/* �θ� ���� ���, �θ��� ���� ����� �ݿ� */
			if (GetObject()->GetParent()) { m_worldMatrix = m_parentMatrix * m_worldMatrix; }

			/* �ڽ��� ���� ���, �ڽ��� ���� ����� �ڽĵ��� �θ� ���� ��ķ� ���� */
			for (const auto & iter : GetObject()->GetChildren())
			{
				iter.second->GetTransform()->m_parentMatrix = m_worldMatrix;
			}

			/* ���� ��Ŀ��� ��ġ�� �����Ͽ� ���� */
			m_worldPosition = glm::vec3(m_worldMatrix[3]);
		}
		/* ���� ����� ������ �ʿ䰡 ���� ���, �̹� �����ӿ� ������� �ʾ����� ���� */
		else { m_isChangedMatrix = false; }

		return true;
	}

	/* Ʈ�������� �ʱ�ȭ�ϴ� �Լ� */
	void Transform::Reset()
	{
		m_position.Set(glm::vec3(0.0f));
		m_rotation.Set(glm::vec3(0.0f));
		m_scale.Set(glm::vec3(1.0f));
	}

	/* ������ ���⿡ �� ȸ���� �������� ���� ��� ���� */
	glm::vec3 Transform::GetLookAt(const glm::vec3 & direction) const
	{
		return glm::normalize(glm::mat3(m_worldMatrix) * direction);
	}

}