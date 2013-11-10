#include "Header.h"
#include <stdio.h>
#include <stdlib.h>

//Options fonctions of the diff command

void help_option()
{
	printf("Usage: diff [OPTION]... FICHIERS\n");
	printf("Comparer les fichiers ligne par ligne.\n");

	//suite des détails d'options
}

// fonction strcomp source wiki

int strcomp(const char* s1, const char* s2)
{
	while ((*s1++ == *s2++) && (*s1 != '\0'));
	return (*((unsigned char *)--s1) < *((unsigned char *)--s2)) ? -1 : (*(unsigned char *)s1 != *(unsigned char *)s2);
}

int myStrlen(char *s)
{
	char *start;
	start = s;
	while (*s != 0)
	{
		++s;
	}
	return s - start;
}

/*Count lines
There is no need to define the max length  of a line
*/
int linesOfFile(char* file)
{
	FILE* fileParam = NULL;
	int  c;
	unsigned long newline_count = 0;
	fileParam = fopen(file, "r");

	if (fileParam!=NULL)
	{
		/* count the newline characters */
		while ((c = fgetc(fileParam)) != EOF) {
			if (c == '\n')
				newline_count++;
		}
		fclose(fileParam);

		return newline_count;


	}
	else
	{
		printf("Impossible de lire le fichier");
		return -1;
	}

}

int CaractecrsOfFile(char* file)
{
	FILE* fileParam = NULL;
	int  c = 0;
	int cars = 0;
	fileParam = fopen(file, "r");

	if (fileParam != NULL)
	{
		/* count the numbers of characters */
		while ((c = fgetc(fileParam)) != EOF) {
				cars++;
		}
		fclose(fileParam);

		return cars;


	}
	else
	{
		printf("Impossible de lire le fichier");
		return -1;
	}

}


char** fileToTabs(char* file, int lines)
{
	char** tab = NULL;
	FILE* fileToTab = NULL;
	char c = 0;
	unsigned long numberOfCars = CaractecrsOfFile(file);
	unsigned long i = 0;

	fileToTab = fopen(file,"r");

	tab = (char**)malloc((numberOfCars)*sizeof(char*));

	if (tab==NULL)
	{
		printf("Can not alloc");
		exit(0);
	}

	if (fileToTab!=NULL)
	{
		while ((c = fgetc(fileToTab)) != EOF) {
			tab[i] = NULL;
			tab[i] = malloc(sizeof(char));
			tab[i] = c;			
			i++;
		}
		fclose(fileToTab);
	}
	else
	{
		printf("Can not open input file");
		exit(0);
	}

	tab[i] = malloc(sizeof(char));
	tab[i] = '\0';

	return tab;

}


