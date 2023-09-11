#pragma once

#include "common/ansi_common.h"
#include "utility/state_checker/ansi_state_checker.h"

namespace ansi
{

	/* 3���� ���� ���� ���� �˻� Ŭ���� */
	class StateCheckerVec3 : public StateChecker<glm::vec3>
	{
	public:
		/* ������
		* @param scalar - �ʱ�ȭ ��
		*/
		explicit StateCheckerVec3(float scalar = 0.0f) { m_curValue = m_oldValue = glm::vec3(scalar); }

		/* Setter - ���� �� */
		void Set(const glm::vec3 & vec3) { m_curValue = vec3; }
		/* Setter - ���� �� */
		void Set(float x, float y, float z) { m_curValue.x = x; m_curValue.y = y; m_curValue.z = z; }
		/* Setter - ���� ���� X ��� */
		void SetX(float x) { m_curValue.x = x; }
		/* Setter - ���� ���� Y ��� */
		void SetY(float y) { m_curValue.y = y; }
		/* Setter - ���� ���� Z ��� */
		void SetZ(float z) { m_curValue.z = z; }

		/* Adder - ���� �� */
		void Add(const glm::vec3 & vec3) { m_curValue += vec3; }
		/* Adder - ���� �� */
		void Add(float x, float y, float z) { m_curValue.x += x; m_curValue.y += y; m_curValue.z += z; }
		/* Adder - ���� ���� X ��� */
		void AddX(float x) { m_curValue.x += x; }
		/* Adder - ���� ���� Y ��� */
		void AddY(float y) { m_curValue.y += y; }
		/* Adder - ���� ���� Z ��� */
		void AddZ(float z) { m_curValue.z += z; }

	};

}
