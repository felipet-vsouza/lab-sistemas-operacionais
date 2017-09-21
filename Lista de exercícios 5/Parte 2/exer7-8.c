#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void load_firefox(char *url) {
	char argString[500];
	sprintf(argString, "%s", "firefox --new-window");
	strcat(argString, " ");
	strcat(argString, url);
	system(argString);
}

int main(int argc, char *argv[]) {
	load_firefox(argv[1]);
	return 0;
}
