#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

/*
**Main of the diff fonction
*
**
*/
int main(int argc, char* argv[])
{

	//Checking of the number of arguments
	if (argc < 2)
	{
		printf("diff: opérande manquante après %cdiff%c\n", 174,175);
		printf("diff: Pour en savoir davantage, utilisez: %c diff -h/--help %c.\n", 174,175);
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
	index 10 = --normal
	index 11 = -l || --paginate
	index 12 = -a || --text

	Autres options à envisager...
	*/
	int arguments[13];

	//count options

	int i, countOptions = 0, flag = 0, optionT = 0,optionSpe = 0;
	char* tabFile1;
	char* tabFile2;

	for (i = 1; i < argc; i++)
	{
		flag = 0;

		if (strcomp1(argv[i], "-q") == 0 || strcomp1(argv[i], "--brief") == 0)
		{
			arguments[0] = 1;
			countOptions++;
			flag = 1;
		}
		if (strcomp1(argv[i], "-s") == 0 || strcomp1(argv[i], "--report-identical-files") == 0)
		{
			arguments[1] = 1;
			countOptions++;
			flag = 1;
		}
		if (strcomp1(argv[i], "-y") == 0 || strcomp1(argv[i], "--side-by-side") == 0)
		{
			arguments[2] = 1;
			countOptions++;
			flag = 1;

		}
		if (strcomp1(argv[i], "-t") == 0 || strcomp1(argv[i], "--expand-tables") == 0)
		{
			arguments[3] = 1;
			countOptions++;
			flag = 1;
			optionT = 1;

		}
		if (strcomp1(argv[i], "-N") == 0 || strcomp1(argv[i], "--new-file") == 0)
		{
			arguments[4] = 1;
			countOptions++;
			flag = 1;

		}
		if (strcomp1(argv[i], "-i") == 0 || strcomp1(argv[i], "--ignore-case") == 0)
		{
			arguments[5] = 1;
			countOptions++;
			flag = 1;
		}
		if (strcomp1(argv[i], "-E") == 0 || strcomp1(argv[i], "--ignore-tab-expansion") == 0)
		{
			arguments[6] = 1;
			countOptions++;
			flag = 1;

		}
		if (strcomp1(argv[i], "-h") == 0 || strcomp1(argv[i], "--help") == 0)
		{
			arguments[7] = 1;
			countOptions++;
			flag = 1;
		}
		if (strcomp1(argv[i], "-h") == 0 || strcomp1(argv[i], "--help") == 0)
		{
			flag = 1;
			arguments[8] = 1;
			help_option();
			return 0;
		}
		if (strcomp1(argv[i], "-v") == 0 || strcomp1(argv[i], "--version") == 0)
		{
			flag = 1;
			arguments[9] = 1;
			printf("diff 0.1\nCopyright (C) 2013 ESGI\nCeci est un logiciel libre: vous %ctes libre de le changer et de le redistribuer.",136);
			printf("Il n'y a pas de GARANTIE, dans les limites persmises par la loi\n");
			printf("Version 0.1 pre-alpha\n\nProgramme %ccrit par :\nPequin Mathieu\nBlondeau Guillaume\nFayette Alexandre", 130);
			FILE* esgi = NULL;
			char esgiChain[1000];
			esgi = fopen("esgi_logo.txt", "r");

			if (esgi != NULL)

			{
				while (fgets(esgiChain, 1000, esgi) != NULL)
				{
					printf("%s", esgiChain);

				}

				fclose(esgi);
				printf("\n");
			}
			return 0;
		}

		if (strcomp1(argv[i], "--normal") == 0)
		{
			flag = 1;
			arguments[10] = 1;
			countOptions++;
		}
		if (strcomp1(argv[i], "-l") == 0 || strcomp1(argv[i], "--paginate") == 0)
		{
			flag = 1;
			arguments[11] = 1;
			countOptions++;
		}

		if (strcomp1(argv[i], "-a") == 0 || strcomp1(argv[i], "--text") == 0)
		{
			flag = 1;
			arguments[12] = 1;
			optionSpe = 1;
			countOptions++;
		}

		if ((argv[i][0]=='-') && (flag == 0))
		{
			printf("diff: l'option -- %c %s %c est invalide\n", 174, argv[i], 175);
			printf("diff: Pour en savoir davantage, utilisez: %c diff --help %c.\n", 174, 175);
			return 0;

		}
	}

	if ((arguments[10]==1 && arguments[2]==1))
	{
		printf("diff: options de style de sortie conflictuelles\n");
		printf("diff: Pour en savoir davantage, utilisez: %cdiff --help%c.\n",174,175);
		return 0;

	}

	//Filenames are taken after the option(s)
	argv[1] = argv[countOptions + 1];
	argv[2] = argv[countOptions + 2];
	char* firstFile = argv[1];
	char* secondFile = argv[2];

	unsigned long fileSizeFile1 = GetFileSize(firstFile, optionSpe);
	unsigned long fileSizeFile2 = GetFileSize(secondFile, optionSpe);
	//Taille max du fichier à determiner 
	//100 000 000 octets valeur arbitraire 


	if (fileSizeFile1 > 100000000)
	{
		short overSized1 = 1;
		FILE* file1 = OpenAFile(firstFile, optionSpe);
		//Retour du curseur au début du fichier si déjà opéré dessus
		rewind(file1);

		//modèle d'utilisation :
		//char* cara = pointFile(file1); avec un boucle while != EOF sur les deux fichiers

		fclose(file1);

	}
	if (fileSizeFile2 > 100000000)
	{
		short overSized2 = 1;
		FILE* file2 = OpenAFile(firstFile, optionSpe);
		//Retour du curseur au début du fichier si déjà opéré dessus
		rewind(file2);


		fclose(file2);
	}



	if (optionT==1)
	{
		tabFile1 = fileToTabsOptionT(firstFile,optionSpe);
		tabFile2 = fileToTabsOptionT(secondFile,optionSpe);

	}
	else
	{
		//Appel de fileToTabs pour récupérer les tableaux contenant l'intégralité des fichiers
		tabFile1 = fileToTabs(firstFile,optionSpe);
		tabFile2 = fileToTabs(secondFile,optionSpe);
	}
	//debug affichage tableau, a ne pas faire pour de gros fichiers, sauf tests
	/*unsigned long j = 0;
	while (tabFile1[j]!='\0')
	{
	printf("%c", tabFile1[j]);
	j++;
	}*/
}