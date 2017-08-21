#include <stdio.h>	// printf, FILE, fopen, fread, fseek, fclose
#include <stdlib.h>	// malloc

#include "menu.h"

#define DOOMSIZE 709905

// RUN USING: gcc main.c menu.c && ./a.out
int main()
{
	// Hacks for Doom2 v1.9

	FILE *fp = fopen("DOOM2.EXE", "r");
	unsigned char *buffer;
	int i = 0;

	if (fp)
	{
		// Check size
		fseek(fp, 0, SEEK_END);
		int sz = ftell(fp);

		if (sz == DOOMSIZE)
		{
			buffer = (unsigned char *) malloc(sz);

			// Go to begining and read
			fseek(fp, 0 , SEEK_SET);
			fread(buffer, sz, 1, fp);
			// This will print 'MZ'
			printf("%c%c\n", buffer[0], buffer[1]);

			while(menu(buffer));
		}
		else
		{
			printf("File DOOM2.EXE is not %i bytes.\n", DOOMSIZE);
		}

		i = fclose(fp);
	}
	else
	{
		printf("Cannot find DOOM2.EXE in the current directory.\n");
	}

	return i;
}

