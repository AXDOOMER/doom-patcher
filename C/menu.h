#ifndef _MENU_H_
#define _MENU_H_

#include "patches.h"

int check(unsigned char *buf, unsigned int array[][PATCHWIDTH], int size, int data);

int menu(unsigned char *exe);

typedef struct
{
   char c;
   char* string;
   //unsigned int patch[][PATCHWIDTH];	// to the array of the patch
} menu_entry, entry;

// Menu lookup table
static const menu_entry menus[][3] =
{
	{'1', "Mouve sensitivity hack"/*, sens*/},	// 'sens' should point to the array of the patch
	{'q', "Quit"/*, NULL*/}
};

#endif
