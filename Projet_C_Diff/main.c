#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "Header.h"

int main(int argc, char* argv[])
{
	//Checking of the number of arguments
	if (argc < 2)
	{
		printf("diff: opérande manquante après %cdiff%c\n", 174, 175);
		printf("diff: Pour en savoir davantage, utilisez: %c diff -h/--help %c.\n", 174, 175);
		return 1;
	}
	//Options Simples
	char *optstring = "qsytNiEbhvla";
	//Structure d'options
	/*la colonne name comprend l'option longue
	has_arg à 0 si l'option ne prend pas d'arguments/sous-options
	flag à NULL pour le renvoie de val
	val = la valeur renvoyée, correspond à l'option simple pour effectuer un switch
	*/
	struct option longopts[] = {

		/*name      has_arg  flag       val*/
		{ "brief", 0, NULL, 'q' },
		{ "report-identical-files", 0, NULL, 's' },
		{ "side-by-side", 0, NULL, 'y' },
		{ "expand-tables", 0, NULL, 't' },
		{ "new-file", 0, NULL, 'N' },
		{ "ignore-case", 0, NULL, 'i' },
		{ "ignore-tab-expansion", 0, NULL, 'E' },
		{ "ignore-space-change", 0, NULL, 'b' },
		{ "help", 0, NULL, 'h' },
		{ "version", 0, NULL, 'v' },
		{ "normal", 0, NULL, 'd' },
		{ "paginate", 0, NULL, 'l' },
		{ "text", 0, NULL, 'a' },
		{ NULL, 0, NULL, 0 },
	};
	int longindex;
	int option;
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

	int i, countOptions = 0, optionT = 0, optionSpe = 0;
	char* tabFile1;
	char* tabFile2;
	/*
	La fonction getopt_long() prend en argument argc, argv, la chaine de car des options courtes,
	la structure d'options longues et un pointeur sur un entier
	Elle renverra la valeur indiqué dans le champ val si l'option est trouvée
	donc le caractère de l'option courte*/
	while ((option = getopt_long(argc, argv, optstring, longopts, &longindex)) != -1)
	{
		switch (option)
		{

		case 'q':
			arguments[0] = 1;
			break;
		case 's':
			arguments[1] = 1;
			break;
		case 'y':
			arguments[2] = 1;
			break;
		case 't':
			arguments[3] = 1;
			optionT = 1;
			break;
		case 'N':
			arguments[4] = 1;
			break;
		case 'i':
			arguments[5] = 1;
			break;
		case 'E':
			arguments[6] = 1;
			break;
		case 'b':
			arguments[7] = 1;
			break;
		case 'h':
			arguments[8] = 1;
			help_option();
			return 0;
		case 'v':
			arguments[9] = 1;
			printf("diff 0.1\nCopyright (C) 2013 ESGI\nCeci est un logiciel libre: vous %ctes libre de le changer et de le redistribuer.", 136);
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
		case 'd':
			arguments[10] = 1;
			break;
		case 'l':
			arguments[11] = 1;
			break;
		case 'a':
			arguments[12] = 1;
			optionSpe = 1;
			break;
		default:
			printf("diff: l'option saisie est invalide\n");
			printf("diff: Pour en savoir davantage, utilisez: %c diff --help/-h %c.\n", 174, 175);
			return 1;
		}
	}

	//Count options to take filenames
	for (i = 1; i<argc; i++)
	{
		if (argv[i][0] == '-')
		{
			countOptions++;
		}
	}

	if ((arguments[10] == 1 && arguments[2] == 1))
	{
		printf("diff: options de style de sortie conflictuelles\n");
		printf("diff: Pour en savoir davantage, utilisez: %cdiff --help%c.\n", 174, 175);
		return 0;
	}

	//Filenames are taken after the option(s)
	argv[1] = argv[countOptions + 1];
	argv[2] = argv[countOptions + 2];
	char* firstFile = argv[1];
	char* secondFile = argv[2];

	printf("File1 = %s", firstFile);
	printf("\nFile2 = %s\n", secondFile);

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
	if (optionT == 1)
	{
		tabFile1 = fileToTabsOptionT(firstFile, optionSpe);
		tabFile2 = fileToTabsOptionT(secondFile, optionSpe);
	}
	else
	{
		//Appel de fileToTabs pour récupérer les tableaux contenant l'intégralité des fichiers
		tabFile1 = fileToTabs(firstFile, optionSpe);
		tabFile2 = fileToTabs(secondFile, optionSpe);
	}
	//debug affichage tableau, a ne pas faire pour de gros fichiers, sauf tests
	/*unsigned long j = 0;
	while (tabFile1[j]!='\0')
	{
	printf("%c", tabFile1[j]);
	j++;
	}*/
}
