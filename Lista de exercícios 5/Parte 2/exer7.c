#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

void load_firefox(char *url) {
	printf(url);
	ShellExecute(GetDesktopWindow(), "open", url, NULL, NULL, SW_SHOWDEFAULT);
}

int main( int argc, char *argv[ ] ) {
	load_firefox(argv[1]);
	return 0;
}