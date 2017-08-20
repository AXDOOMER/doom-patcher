#include <stdio.h>	// printf, FILE, fopen, fread, fseek, fclose
#include <stdlib.h>	// malloc
#include <string.h>	// strdup

#include "menu.h"
#include "patches.h"

int check(unsigned char *buf, unsigned int array[][PATCHWIDTH], int size, int data)
{
	if (data != 1 && data != 2)
		return -1;

	for (int i = 0; i < size; i++)
	{
		//printf("%02X, %02X\n", buf[array[i][ADDRESS]], array[i][data]);
		if (buf[array[i][ADDRESS]] != array[i][data])
		{
			// different
			return 0;
		}
	}

	// same
	return 1;
}

int menu(unsigned char *exe)
{
	printf("  ===== Hacks for Doom2 v1.9 =====\n\n");

	char* status;
	int length = sizeof(sens) / sizeof(unsigned int) / PATCHWIDTH;
	if (check(exe, sens, length, VANILLA) == 0 && check(exe, sens, length, PATCHED) == 0)
		status = "UNKNOWN";
	if (check(exe, sens, length, VANILLA) == 1)
		status = "VANILLA";
	if (check(exe, sens, length, PATCHED) == 1)
		status = "PATCHED";
	
	printf("     %-40s   [ %s ]\n" , "Max. sensitivity: 9 => 127", status);


	printf("Please enter a number:\n");
	printf("> ");

	int input;
	int result = scanf("%d", &input);

	if (result == 0)
	{
		printf("number: %i\n", input);
	}

	//if (input == 'q' || input == 'Q')
	//	input = 0;


	return input;
}
