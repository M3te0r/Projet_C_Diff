#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

/*
**Main of the diff fonction
*
**
*/
int main(int argc, char** argv[])
{

	//if there are less than 2 arguments then the program closes
	if (argc < 2)
	{
		printf("You have entered less than 2(two) arguments, please try again with more arguments");
		return 1;
	}


	/*

	Options init*/

	int argument_i = 0;
	int argument_b = 0;
	int argument_E = 0;
	int argument_v = 0;
	int argument_h = 0;
	int argument_w = 0;
	int argument_N = 0;
	int argument_t = 0;

	int argument_s = 0;
	int argument_q = 0;
	int argument_y = 0;


	//count options

	int i, countOptions = 0;

	for (i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], "-j") == 0 || strcmp(argv[i], "--ignore-case") == 0)
		{
			argument_i = 1;
			countOptions++;

		}
		if (strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--ignore-space-change") == 0)
		{
			argument_b = 1;
			countOptions++;


		}
		if (strcmp(argv[i], "-E") == 0 || strcmp(argv[i], "--ignore-tab-expansion") == 0)
		{
			argument_E = 1;
			countOptions++;

		}
		if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0)
		{
			argument_v = 1;
			//printf de la version
			return 0;

		}
		if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
		{
			argument_h = 1;
			printf("Usage of diff command :\n");
			printf("[OPTIONS] file1 file2\n\n");

		}
	}





}