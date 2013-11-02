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

	//Checking of the number of arguments
	if (argc < 2)
	{
		printf("Invalid number of arguments, please enter at least 2 arguments");
		return 1;
	}


	/*

	Options init*/
	//tab of options where arguments[n] = 0 or 1
	//n is the option
	/*
	index 0 = -q || --brief
	index 1 = -s || --report-identical-files
	index 2 = -y || --side-by-side
	index 3 = -t || --expand-tables
	index 4 = -N || --new-file
	index 5 = -i || --ignore-case
	index 6 = -E || --ignore-tab-expansion
	index 7 = -b || --ignore-space-change
	index 8 = -h || --help
	index 9 = -v || --version
	index 10 = -w || --width
	
	
	*/
	int arguments[11];



	//count options

	int i, countOptions = 0;

	for (i = 0; i < argc; i++)
	{

		if (strcmp(argv[i], "-q") == 0 || strcmp(argv[i], "--brief") == 0)
		{
			arguments[0] = 1;
			countOptions++;
		}
		if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--report-identical-files") == 0)
		{
			arguments[1] = 1;
			countOptions++;
		}
		if (strcmp(argv[i], "-y") == 0 || strcmp(argv[i], "--side-by-side") == 0)
		{
			arguments[2] = 1;
			countOptions++;

		}
		if (strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--expand-tables") == 0)
		{
			arguments[3] = 1;
			countOptions++;

		}
		if (strcmp(argv[i], "-N") == 0 || strcmp(argv[i], "--new-file") == 0)
		{
			arguments[4] = 1;
			countOptions++;

		}
		if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--ignore-case") == 0)
		{
			arguments[5] = 1;
			countOptions++;

		}
		if (strcmp(argv[i], "-E") == 0 || strcmp(argv[i], "--ignore-tab-expansion") == 0)
		{
			arguments[6] = 1;
			countOptions++;

		}
		if (strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--ignore-space-change") == 0)
		{
			arguments[7] = 1;
			countOptions++;
		}
		if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
		{
			arguments[8] = 1;
			countOptions++;
		}
		if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0)
		{
			arguments[9] = 1;
			countOptions++;
		}
		if (strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--width") == 0)
		{
			arguments[10] = 1;
			countOptions++;
		}
		
	}

}


int strcmp(const char* s1, const char* s2)
{
	while ((*s1++ == *s2++) && (*s1 != '\0'));
	return (*((unsigned char *)--s1) < *((unsigned char *)--s2)) ? -1 : (*(unsigned char *)s1 != *(unsigned char *)s2);
}