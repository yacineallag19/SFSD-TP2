#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#define MAX 1024 
#define MAX2 1000000


// Les structure qu'on va utiliser
typedef struct Tentete // l'entete
{
    int nombreBloc ; // nombre de bloc dans le fichier
} Tentete;


typedef struct Tenreg // les enregistrement des donnes
{
	int matricule ;
	int dateNaissance;
	char nom[31] ;
	char prenom[31] ;
	char wilayaNaissance[20];
	char groupeSanguin[4] ;
	char grade[25] ;
	char forceArmee[50] ; 
	char regionMilitaire [16] ; 
} Tenreg ;

typedef struct Tbloc // le bloc du fichier
{
	int nb;
	Tenreg tab[MAX] ;

} Tbloc , BUFFER ;


typedef struct enteteIndex
{
	int nombreIbloc ;
} enteteIndex ;

typedef struct indexEnreg // structure d'index
{
	int cle ;
	int numeroBloc ;
	int deplacement ; 
} indexEnreg ;


typedef struct Ibloc
{
	int NbCle ;
	indexEnreg tableauI [1024] ;
} Ibloc ;


typedef struct Tindex
{
	int taille ;
	indexEnreg tableau[MAX2] ;
} Tindex , INDEX ;


// la machine abstraite 
void initEntete(FILE* f) ; // initialiser l'entete
void ouvrir (FILE **f,char *nomfichier,char *mode) ; // ouvrir un fichier 
void fermer (FILE *f) ; // fermer un fichier
bool lireDir (FILE *f , int i ,BUFFER* buf) ; // ecrire le bloc numero i dans buf
bool ecrireDir (FILE *f ,  int i ,BUFFER* buf) ; // ecrire buf dans le bloc numero i
int entete (FILE *f,int i) ; // retourner le nombre de bloc dans le fichier
void affentete (FILE *f, int i , int valeur) ; // modifier l'entete avec valeur
int allocBloc (FILE *f) ; // Retourne le numéro d’un nouveau bloc alloué à FO


// fonction pour la manipulation de l'index
int Ientete(FILE *f) ;
void createIndex(char *nom) ;
void affIentete(FILE *f, int valeur)  ;
bool lireIbloc (FILE *f , int i , Ibloc* buf) ; // lire un bloc d'index
bool ecrireIbloc (FILE *f , int i , Ibloc * buf ) ; // ecrire un bloc d'index
void fillIndex (INDEX *tabIndex , Ibloc *buf , int start , int *end) ; // ecrire le buffer d'index dans le tableau d'index
void getSubArray (INDEX *tabIndex , Ibloc *buf , int start , int *end) ; // charger 1024 des element d'un index dans le buffer index
void chargementIndex (char *path, INDEX *tabIndex) ; // charger le tableau d'index dans tabIndex
void sauvIndex (char *path, INDEX *tabIndex) ; // ecrie la table d'index dans la memoire secondaire
void rechercheIndex (INDEX *tabIndex , int valeur, bool *trouve , int *numBloc , int *posBloc , int *place) ; // faire une recherche dans la table d'index
void insertionIndex (INDEX *tabIndex, int valeur, int numBloc , int posBloc) ;
void suppressionIndex (INDEX *tabIndex , int valeur) ;

// fonctions pour remplir les blocs aleatoirement
int generateNumber (int inf , int sup) ; // generer un nombre aleatoire entre inf et sup
void generateMatricule (BUFFER *buf , INDEX *tabIndex , int numBloc , int position) ; // genere un matricule et l'ecrire dans buffer et misa a jour d'index
void generateNom (BUFFER *buf, int position) ; // genere un nom et l'ecrire dans buffer
void generatePrenom (BUFFER *buf, int position) ; // genere un prenom et l'ecrire dans buffer
void generateDateNaissance (BUFFER *buf , int position) ; // generer une date de naissance et l'ecrire dans buffer
void generateWilayaNaissance (BUFFER *buf,int position) ; // generer une wilaya de naissance et l'ecrire dans buffer
void generateGroupeSanguin (BUFFER *buf,int position) ; // generer un groupe sanguin de l'ecrire dans buffer
void generateGrade (BUFFER *buf,int position) ; // generer un grade de l'ecrire dans buffer
void generateForce (BUFFER *buf,int position) ; // generer une force et l'ecrire dans buffer
void generateRegion (BUFFER* buf,int position) ; // generer une region et l'ecrire dans buffer
void generateSoldat (BUFFER *buf,int position) ; // generer un soldat et l'ecrire dans le buffer 

// Les fonctions du manipulation du fichier 

void chargement_init(char* nomfichier,int n);
void recherche(char* nomfichier, int valeur,bool *trouve,int *i,int *j,int *t)   ;
void insertion(char* nomfichier,Tenreg e) ;
void suppression(char* nomfichier, int mat);
void requeteIntervalle (char* nomfichier, int m1, int m2) ; 
void printSoldier(Tenreg e) ; 
void printFile (char* nomfichier) ; 
void modifierRegion(char* nomfichier, int valeur) ;

bool is_valid_date(int day, int month, int year) ;


#endif
