#include "core/window/ansi_window.h"

/* ���α׷� ������ */
int main()
{
	int result{ -1 };

	/* ���α׷� �ٽ� ��ü�� �����ϰ� ���α׷� ���� ���� */
	if (ansi::Core::CreateInstance() && ansi::Core::GetWindow()->Run()) { result = 0; }

	/* ���� �� ���α׷� �ٽ� ��ü ���� */
	ansi::Core::DeleteInstance();

	return result;
}
