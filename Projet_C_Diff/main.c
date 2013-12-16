#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "Header.h"

#define WIN32
#ifdef LINUX
#include <sys/types.h>
#include <dirent.h>
#endif // WIN32

int main(int argc, char* argv[])
{
	//Checking of the number of arguments
	if (argc < 2)
	{
		printf("diff: opérande manquante après %cdiff%c\n", 174, 175);
		printf("diff: Pour en savoir davantage, utilisez: %c diff -h/--help %c.\n", 174, 175);
		return 1;
	}



	int countCharArgs = 0, indarg = 0, indarg2 = 0, indarg3 = 0;

	for (indarg = 0; indarg<argc; indarg++)
	{
		indarg2 = 0;
		while (argv[indarg][indarg2] != '\0')
		{
			countCharArgs++;
			indarg2++;
		}
		countCharArgs++;
	}

	char *chaineArgs = NULL;
	chaineArgs = calloc(1, countCharArgs + 1);

	for (indarg = 0; indarg<argc; indarg++)
	{
		indarg2 = 0;
		while (argv[indarg][indarg2] != '\0')
		{
			chaineArgs[indarg3] = argv[indarg][indarg2];
			indarg3++;
			indarg2++;

		}
		chaineArgs[indarg3] = ' ';
		indarg3++;
	}

	chaineArgs[indarg3 - 1] = '\0';
	//Simple options
	char *optstring = "qsytNiEbhvlaT";
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
		{ "initial-tab", 0, NULL, 'T' },
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
	index 2 = -t || --expand-tables
	index 3 = -N || --new-file
	index 4 = -i || --ignore-case
	index 5 = -E || --ignore-tab-expansion
	index 6 = -b || --ignore-space-change
	index 7 = -h || --help
	index 8 = -v || --version
	index 9 = --normal
	index 10 = -l || --paginate
	index 11 = -a || --text
	index 12 = -T || --initial-tab

	Autres options à envisager...
	*/
	int arguments[13];

	int i, countOptions = 0, optionT = 0, optionSpe = 0, displayOption = 0, optionN = 0, notFoundFile1 = 0, notFoundFile2 = 0, ldisplayOption = 0;
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
			displayOption = 2;
			break;
		case 's':
			arguments[1] = 1;
			break;
		case 't':
			arguments[2] = 1;
			optionT = 1;
			break;
		case 'N':
			arguments[3] = 1;
			optionN = 1;
			break;
		case 'i':
			arguments[4] = 1;
			break;
		case 'E':
			arguments[5] = 1;
			break;
		case 'b':
			arguments[6] = 1;
			break;
		case 'h':
			arguments[7] = 1;
			help_option();
			return 0;
		case 'v':
			arguments[8] = 1;
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
			arguments[9] = 1;
			break;
		case 'l':
			arguments[10] = 1;
			ldisplayOption = 1;
			break;
		case 'a':
			arguments[11] = 1;
			optionSpe = 1;
			break;
		case 'T':
			arguments[12] = 1;
			displayOption = 1;
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

	/*if ((arguments[10] == 1 && arguments[2] == 1))
	{
		printf("diff: options de style de sortie conflictuelles\n");
		printf("diff: Pour en savoir davantage, utilisez: %cdiff --help%c.\n", 174, 175);
		return 0;
	}*/
	//Filenames are taken after the option(s)
	argv[1] = argv[countOptions + 1];
	argv[2] = argv[countOptions + 2];
	char* firstFile = argv[1];
	char* secondFile = argv[2];
#ifdef LINUX


	char* takeDir1 = NULL;
	char* takeDir2 = NULL;
	i = 0;
	//Position of last '/' to take full path
	int savedCars = 0;
	//Number of characters of full path
	int lengthChem = 0;
	while (firstFile[i] != '\0')
	{
		if (firstFile[i] == '/')
		{

			savedCars = i;
		}
		i++;
	}
	lengthChem = i;
	char *fileName1 = NULL;
	fileName1 = malloc(sizeof(char)*(1 + lengthChem - savedCars));
	int l = 0;
	for (i = savedCars + 1; i <= lengthChem; i++, l++)
	{
		fileName1[l] = firstFile[i];
	}

	takeDir1 = malloc(sizeof(char)*(savedCars + 1));

	for (i = 0; i <= savedCars; i++)
	{
		takeDir1[i] = firstFile[i];
	}


	i = 0;
	savedCars = 0;
	while (secondFile[i] != '\0')
	{
		if (secondFile[i] == '/')
		{

			savedCars = i;
		}
		i++;
	}
	lengthChem = i;
	char *fileName2 = NULL;
	fileName2 = malloc(sizeof(char)*(1 + lengthChem - savedCars));
	l = 0;
	for (i = savedCars + 1; i <= lengthChem; i++, l++)
	{
		fileName2[l] = secondFile[i];
	}
	takeDir2 = malloc(sizeof(char)*(savedCars + 1));

	for (i = 0; i <= savedCars; i++)
	{
		takeDir2[i] = secondFile[i];
	}

	DIR* rep1 = NULL;
	DIR* rep2 = NULL;
	struct dirent* fichierLu = NULL;
	rep1 = opendir(takeDir1);
	rep2 = opendir(takeDir2);
	if (rep1 == NULL || rep2 == NULL)
	{
		printf("Can not open such directory");
		exit(1);
	}
	int fileFound = 0;
	/*
	Check si le fichier est bien dans le dossier*/
	while ((fichierLu = readdir(rep1)) != NULL)
	{
		if (strcomp1(fichierLu->d_name, fileName1) == 0)
		{
			fileFound = 1;
			break;
		}
	}
	if (fileFound == 0 && optionN == 0)
	{

		printf("diff: %s: Aucun fichier ou dossier de ce type\n", fileName1);
		return 1;
	}
	else if(fileFound == 0 && optionN == 1)
	{
		notFoundFile1 = 1;
	}

	fileFound = 0;
	while ((fichierLu = readdir(rep2)) != NULL)
	{
		if (strcomp1(fichierLu->d_name, fileName2) == 0)
		{
			fileFound = 1;
			break;
		}
	}
	if (fileFound == 0 && optionN == 0)
	{

		printf("diff: %s: Aucun fichier ou dossier de ce type\n", fileName2);
		return 1;
	}
	else if (fileFound == 0 && optionN == 1)
	{
		notFoundFile2 = 1;

	}
#endif // LINUX
	unsigned long fileSizeFile1 = 0;
	unsigned long fileSizeFile2 = 0;
	if (notFoundFile1 == 1)
	{
		fileSizeFile1 = 1;
	}
	else
	{
		fileSizeFile1 = GetFileSize(firstFile, optionSpe);
	}

	if (notFoundFile2 == 1)
	{

		fileSizeFile2 = 1;
	}
	else{
		fileSizeFile2 = GetFileSize(secondFile, optionSpe);
	}
	//Taille max du fichier à determiner
	//100 000 000 octets valeur arbitraire
	if (arguments[0] == 1 && (fileSizeFile1 != fileSizeFile2))
	{
		printf("Files %s and %s differ\n", firstFile, secondFile);
		exit(EXIT_SUCCESS);
	}

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
		tabFile1 = fileToTabs(firstFile, optionSpe, optionN);
		tabFile2 = fileToTabs(secondFile, optionSpe, optionN);
	}

	//debug affichage tableau, a ne pas faire pour de gros fichiers, sauf tests
	/*unsigned long j = 0;
	while (tabFile1[j]!='\0')
	{
	printf("%c", tabFile1[j]);
	j++;
	}*/
	unsigned long nb1 = 0;
	unsigned long nb2 = 0;
	int commonLines = 0, other = 0;
	commonLines = linesOfTab(tabFile1, &nb1);

	other = linesOfTab(tabFile2, &nb2);
	if (commonLines > other)
	{
		commonLines = other;
	}
	diff(tabFile1, tabFile2, nb1, nb2, commonLines, displayOption, firstFile, secondFile, chaineArgs, ldisplayOption);
	printf("\n");
	return 0;
}
