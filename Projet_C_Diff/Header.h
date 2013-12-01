//Prototypes des fonctions

//Prototypes des fonctions de comparaison de base
int strcomp1(const char* s1, const char* s2);
int myStrlen(char *s);


//Prototypes des fonctions de opérant sur les fichiers
int linesOfFile(char* file);
int CaractecrsOfFile(char* file);
char* fileToTabs(char* file);

int compteLigneFichier(char *nomFichier);
void ajouterATableauLigneFichier(char *nomFichier, char *tabLigne, int numLigne, int tailleTableau);
int retourLigneCurseur(char *nomFichier, int numLigne);
int nombreCaractereLigne(char *nomFichier, int numLigne);
void afficheLigne(char *nomFichier, int numLigne);
void compare(char *nomDuFichier1,char *nomDuFichier2);
unsigned long GetFileSize(char *file);

//Prototypes des fonctions pour les options
void help_option();
int ignoreCase(char c1, char c2);

void briefing(int differ, char firstFile, char secondFile);

void identicalFiles(int same, char firstFile, char secondFile);