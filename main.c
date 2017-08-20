#include <stdio.h>	// printf, FILE, fopen, fread, fseek, fclose
#include <stdlib.h>	// malloc

#define ADDRESS 0
#define VANILLA 1
#define PATCHED 2
#define PATCHWIDTH 3


// Max. sensitivity: 9 => 127
unsigned int sens[][PATCHWIDTH] = {
	{0x00064972, 0x0A, 0x11},
	{0x00064C8F, 0x09, 0x7F},
	{0x00064E14, 0x8D, 0x66},
	{0x00064E15, 0x34, 0x81},
	{0x00064E16, 0xF5, 0xFD},
	{0x00064E17, 0x00, 0x85},
	{0x00064E19, 0x00, 0x75},
	{0x00064E1A, 0x00, 0x4F},
	{0x00064E6B, 0x80, 0x34},
	{0x00064E6C, 0x00, 0xF5},
	{0x00064E70, 0x8D, 0x00},
	{0x00064E71, 0x54, 0xEB},
	{0x00064E72, 0x22, 0xA8},
	{0x00064E73, 0x00, 0x90}
};

int check(unsigned char *buf, unsigned int array[][PATCHWIDTH], int size, int data)
{
	if (data != 1 && data != 2)
		return -1;

	for (int i = 0; i < size; i++)
	{
		printf("%02X, %02X\n", buf[array[i][ADDRESS]], array[i][data]);
		if (buf[array[i][ADDRESS]] != array[i][data])
		{
			// different
			return 0;
		}
	}

	// same
	return 1;
}

int main()
{
	FILE *fp = fopen("DOOM2.EXE", "r");
	unsigned char *buffer;

	if (fp)
	{
		printf("File will now be read... ");

		// Check size
		fseek(fp, 0, SEEK_END);
		int sz = ftell(fp);
		printf("size: %i\n", sz);

		buffer = (unsigned char *) malloc(sz);

		// Go to begining and read
		fseek(fp, 0 , SEEK_SET);
		fread(buffer, sz, 1, fp);

		// This will print 'MZ'
		printf("%c%c\n", buffer[0], buffer[1]);

		int length = sizeof(sens) / sizeof(unsigned int) / 3;
		/*for (int i = 0; i < length; i++)
		{
			printf("%02X\n", buffer[sens[i][0]]);
		}*/

		// Tests (exe   , patch, size , must match)
		if (check(buffer, sens, length, VANILLA) == 1)
			printf("(1) not patched\n");
		if (check(buffer, sens, length, VANILLA) == 0)
			printf("(2) patched\n");
		if (check(buffer, sens, length, PATCHED) == 1)
			printf("(3) patched\n");
		if (check(buffer, sens, length, PATCHED) == 0)
			printf("(4) not patched\n");

		//printf("%02X\n", buffer[0x00064972]);
		//printf("%02X\n", buffer[0x00064C8F]);

		int i = fclose(fp);
		printf("File closed %i\n", i);
	}
	else
	{
		printf("File DOOM2.EXE cound not be opened.\n");
	}

	return 0;
}
