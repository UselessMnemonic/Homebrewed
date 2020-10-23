#include <string.h>
#include <stdio.h>
#include <3ds.h>

#include "runtime/BootstrapLoader.h"
#include "runtime/heap/ClassArea.h"
#include "runtime/Class.h"
#include "util/print/ClassPrinter.h"

int main(int argc, char** argv)
{
	freopen("stdout.txt", "w", stdout);
	freopen("stderr.txt", "w", stderr);
	gfxInitDefault();
	consoleInit(GFX_TOP, NULL);

	// load example classes
	JRESULT r = 0;
	CLASS *main_clazz = ClassArea_AllocClass();

	r = Bootstrap_LoadClassFromFile("bin/main/Main.class", main_clazz);
	if (r != JRESULT_OK)
	{
		fprintf(stderr, "Unexpected error: %d", r);
	}
	else
	{
		PrintClass(main_clazz);
	}

	// Main loop
	while (aptMainLoop())
	{
		gspWaitForVBlank();
		hidScanInput();

		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break; // break in order to return to hbmenu

		// Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();
	}

	gfxExit();
	return 0;
}
