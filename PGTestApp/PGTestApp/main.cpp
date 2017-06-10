#include <Windows.h>

#include "PG/app/PGAppHost.h"
#include "PGTestAppController.h"

//--------------------------------------------------------
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	PGTestAppController testAppController;

	PG::PGAppHost appHost;
	appHost.runApp(testAppController);

	return 0;
}
