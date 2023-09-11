#include "core/window/ansi_window.h"

/* 프로그램 진입점 */
int main()
{
	int result{ -1 };

	/* 프로그램 핵심 객체를 생성하고 프로그램 루프 실행 */
	if (ansi::Core::CreateInstance() && ansi::Core::GetWindow()->Run()) { result = 0; }

	/* 종료 시 프로그램 핵심 객체 제거 */
	ansi::Core::DeleteInstance();

	return result;
}
