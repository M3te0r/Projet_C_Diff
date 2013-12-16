#include <stdio.h>
#include <stdlib.h>
//Functions prototypes
int strcomp1(const char* s1, const char* s2);
//Prototypes des fonctions de opérant sur les fichiers
FILE* OpenAFile(char* nomFichier, int optionOpen);
unsigned long linesOfFile(char* file);
unsigned long linesOfTab(char *tab, unsigned long* length);
unsigned long CaractersOfFile(char* file);
char* fileToTabs(char* file, int optionSpe, int optionN);
char* fileToTabsOptionT(char* file, int optionSpe);
char* pointFile(FILE* file);

int compteLigneFichier(char *nomFichier);
int retourLigneCurseur(char *nomFichier, int numLigne);
int nombreCaractereLigne(char *nomFichier, int numLigne);
unsigned long GetFileSize(char *file, int optionSpe);

void diff(char* oldFile, char* newFile, int lengthOldFile, int lengthNewFile, int nbCommonLines, int displayOption, const char* firstFileName, const char* secondFileName, const char *chaineArgs, int ldisplayOption);
void length_line_from_idx(const char* tab1, const  char* tab2, int id1, int id2, int* lengths);
int compare_line(int* lengths, int idOld, int idNew, char* oldFile, char* newFile);


//Prototypes des fonctions pour les options
void help_option();
int ignoreCase(char c1, char c2);

void briefing(int differ, const char *firstFileName, const char *secondFileName);

void identicalFiles(int same, const char *firstFile, const char *secondFile);
