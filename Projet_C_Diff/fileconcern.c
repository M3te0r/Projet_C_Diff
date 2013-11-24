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
	unsigned long newline_count = 1;
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

//Renvoie le nombre de caractères dans un fichier
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

//Renvoie un tableau rempli de tous les caractères du fichier
//Caractère par caractère
char* fileToTabs(char* file, int lines)
{
	char* tab = NULL;
	FILE* fileToTab = NULL;
	char c = 0;
	unsigned long numberOfCars = CaractecrsOfFile(file);
	unsigned long i = 0;

	fileToTab = fopen(file,"r");

	tab = malloc((numberOfCars)*sizeof(char*));

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

// Modifie le tableau existant et ajoute les caractères d'une ligne dedans
void ajouterATableauLigneFichier(const char *nomFichier, char *tabLigne, int numLigne, int tailleTableau)
{
	FILE *fichier = NULL;
	int caractereActuel = 0, i = 0;
	long position = 0;
	fichier = fopen(nomFichier, "r");
    position = retourLigneCurseur(nomFichier, numLigne);
    fseek(fichier, position, SEEK_SET);
	if (fichier != NULL)
	{
		for(i=0; i<tailleTableau; i++)
		{
		    caractereActuel = fgetc(fichier);
			tabLigne[i] = caractereActuel;
		}
	}
	fclose(fichier);
}

// Retourne la position du curseur au début de la ligne voulue
int retourLigneCurseur(const char *nomFichier, int numLigne)
{
	FILE *fichier = NULL;
	int caractereActuel = 0, nb = 0, nombreBackSlashN = 0;
	fichier = fopen(nomFichier, "r");
	if (fichier != NULL)
	{
        while (nombreBackSlashN != numLigne)
        {
            caractereActuel = fgetc(fichier);
            if (caractereActuel == '\n' || caractereActuel == EOF)
            {
                nombreBackSlashN++;
            }
        }
        nb = ftell(fichier);
	}
	else
	{
		nb = 0;
	}
	fclose(fichier);
	return nb;
}

// Renvoie le nombre de caractères pour une ligne
int nombreCaractereLigne(const char *nomFichier, int numLigne)
{
	FILE *fichier = NULL;
	int caractereActuel = 0, nb = 0;
	long position = 0;
	fichier = fopen(nomFichier, "r");
    position = retourLigneCurseur(nomFichier, numLigne);
    fseek(fichier, position, SEEK_SET);
	if (fichier != NULL)
	{
        while(caractereActuel != '\n')
        {
            if (caractereActuel == '\n' || caractereActuel == EOF)
            {
                break;
            }
            caractereActuel = fgetc(fichier);
            nb++;
        }
	}
	else
	{
		nb = 1;
	}
	fclose(fichier);
	return nb-1;
}

// Affichage de la ligne voulue
void afficheLigne(const char *nomFichier, int numLigne)
{
	FILE *fichier = NULL;
	int caractereActuel = 0, i = 0;
	long position = 0;
	fichier = fopen(nomFichier, "r");
    position = retourLigneCurseur(nomFichier, numLigne);
    fseek(fichier, position, SEEK_SET);
	if (fichier != NULL)
	{
		while (caractereActuel != '\n' || caractereActuel == EOF)
        {
            if (caractereActuel == EOF)
            {
                break;
            }
            caractereActuel = fgetc(fichier);
            // On affiche tous les caractères sauf les '\n' (retour à la ligne)
            if (caractereActuel != '\n')
            {
                printf("%c", caractereActuel);
            }
        }
	}
	fclose(fichier);
}

// Algorithme qui compare 2 fichiers ligne par ligne
void compare(const char *nomDuFichier1, const char *nomDuFichier2)
{
	FILE *fichier1 = NULL, *fichier2 = NULL;
	fichier1 = fopen(nomDuFichier1, "r");
	fichier2 = fopen(nomDuFichier2, "r");
	int taille1 = 0, taille2 = 0, i = 0, j = 0, nbLigneFic1 = 1, nbLigneFic2 = 1, tailleTableau = 0, nbLigneGlobale = 0;
    long position1 = 0, position2 = 0;

	if (fichier1 != NULL && fichier2 != NULL)
	{
		// Nombre de lignes du fichier 1
		nbLigneFic1 = linesOfFile(nomDuFichier1);
		// Nombre de lignes du fichier 2
		nbLigneFic2 = linesOfFile(nomDuFichier2);
		if (nbLigneFic1 > nbLigneFic2)
        {
            nbLigneGlobale = nbLigneFic1;
        }
        else
        {
            nbLigneGlobale = nbLigneFic2;
        }

		for (j=0; j<nbLigneGlobale; j++)
		{
            // Initialisation
			char *tabLigne1 = NULL;
			char *tabLigne2 = NULL;
			taille1 = 0, taille2 = 0;

            // Taille de caracteres des lignes courantes
			taille1 = nombreCaractereLigne(nomDuFichier1, j);
			taille2 = nombreCaractereLigne(nomDuFichier2, j);

			// Taille commune des 2 tableaux
			if (taille1 > taille2)
			{
				tailleTableau = taille1;
			}
			else
			{
				tailleTableau = taille2;
			}

            // Allocation d'une mémoire pour les deux tableaux
			tabLigne1 = malloc(tailleTableau * sizeof(int));
			tabLigne2 = malloc(tailleTableau * sizeof(int));

			// Retour des curseurs au début de la ligne
			position1 = retourLigneCurseur(nomDuFichier1, j);
			fseek(fichier1, position1, SEEK_SET);
			position2 = retourLigneCurseur(nomDuFichier2, j);
			fseek(fichier2, position2, SEEK_SET);

            // Ajout de la ligne courante dans le tableau (pour le fichier 1 et le fichier 2)
			ajouterATableauLigneFichier(nomDuFichier1, tabLigne1, j, tailleTableau);
			ajouterATableauLigneFichier(nomDuFichier2, tabLigne2, j, tailleTableau);

			int different = 0;
			for (i = 0; i < tailleTableau; i++)
			{
				if (tabLigne1[i] != tabLigne2[i])
				{
					different = 1;
				}
			}
			if (different)
			{
				// Affichage de ligne fichier 1 et ligne fichier 2
				afficheLigne(nomDuFichier1, j);
				printf("\n---\n");
				afficheLigne(nomDuFichier2, j);
				printf("\n\n");
			}
			free(tabLigne1);
			free(tabLigne2);
		}
		fclose(fichier1);
		fclose(fichier2);
	}
	else
	{
		printf("Erreur de lecture du fichier %s ou le fichier %s", nomDuFichier1, nomDuFichier2);
	}
}

/*Fonction ignoreCase
Renvoie 1 si c1!=c2 même en ignorant la casse
Renvoie 0 si c1==c2 en ignorant la casse
+32 et -32 = Table ACSII maj vers min ou min vers maj


A intégrer dans le diff principal si option -i pour chaque caractère*/
int ignoreCase(char c1, char c2)
{
	if (c1==c2)
	{
		return 1;
	}

	if (((c1 >= 65 && c1 <= 90) || (c1 >= 97 && c1 <= 122)) && ((c2 >= 65 && c2 <= 90) || (c2 >= 97 && c2 <= 122)))
	{
		if ((c1 == c2 + 32) || (c1 == c2 - 32))
		{
			return 0;

		}
		else
		{
			return 1;
		}

	}
	else
	{
		return 1;
	}
}