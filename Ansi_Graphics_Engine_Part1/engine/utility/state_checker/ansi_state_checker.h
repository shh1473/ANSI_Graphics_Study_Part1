#pragma once

namespace ansi
{

	/* ���� �˻� ���ø� Ŭ���� */
	template<typename T>
	class StateChecker
	{
	public:
		/* ������ */
		explicit StateChecker()
			: m_isFirstCheck(true)
			, m_curValue()
			, m_oldValue()
		{
		
		}

		/* ���� �ʱ�ȭ�κ��� ��ȭ ���θ� �˻��ϴ� �Լ� */
		bool Check()
		{
			/* ù ��° �˻�� �׻� true ���� ��ȯ */
			if (m_isFirstCheck) { m_isFirstCheck = false; return true; }
			/* ���ĺ��ʹ� ��ȭ ���� ��ȯ */
			return (m_curValue != m_oldValue);
		}

		/* ���� ���� ���� ������ �ʱ�ȭ�ϴ� �Լ� */
		void Reset() { m_oldValue = m_curValue; }

		/* Setter - ���� �� */
		void Set(const T & value) { m_curValue = value; }

		/* Getter - ���� �� */
		const T & Get() const { return m_curValue; }
		/* Getter - ���� ���� �ּ� */
		const T * GetAddress() const { return &m_curValue; }

	protected:
		/* ù ��° �˻� ���� */
		bool m_isFirstCheck;
		/* ���� �� */
		T m_curValue;
		/* ���� �� */
		T m_oldValue;

	};

	/* ���� �˻� �迭 ���ø� Ŭ���� */
	template <typename T, unsigned SIZE>
	class StateArrayChecker
	{
	public:
		/* ������ */
		explicit StateArrayChecker()
			: m_isFirstCheck(true)
			, m_curValues()
			, m_oldValues()
		{
		
		}

		/* ���� �ʱ�ȭ�κ��� ��ȭ ���θ� �˻��ϴ� �Լ� */
		bool Check()
		{
			/* ù ��° �˻�� �׻� true ���� ��ȯ */
			if (m_isFirstCheck) { m_isFirstCheck = false; return true; }
			/* ���ĺ��ʹ� ��ȭ ���� ��ȯ */
			for (int i{ 0 }; i < SIZE; ++i) { if (m_curValues[i] != m_oldValues[i]) { return true; } }

			return false;
		}

		/* ���� ���� ���� ������ �ʱ�ȭ�ϴ� �Լ� */
		void Reset()
		{
			for (int i{ 0 }; i < SIZE; ++i) { m_oldValues[i] = m_curValues[i]; }
		}

		/* Setter - ���� �� */
		void Set(int index, const T & value) { m_curValues[index] = value; }
		/* Setter - ��� ���� �� */
		void SetAll(const T & value) { for (int i{ 0 }; i < SIZE; ++i) { m_curValues[i] = value; } }

		/* Getter - ���� �� */
		const T & Get(unsigned index) const { return m_curValues[index]; }
		/* Getter - ���� ���� �ּ� */
		const T * GetAddress(unsigned index) const { return &m_curValues[index]; }
		/* Getter - ���� �� �迭 */
		const T * GetArray() const { return m_curValues; }

	protected:
		/* ù ��° �˻� ���� */
		bool m_isFirstCheck;
		/* ���� �� �迭 */
		T m_curValues[SIZE];
		/* ���� �� �迭 */
		T m_oldValues[SIZE];

	};

}
