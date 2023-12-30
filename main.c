#include "functions.h"
#include <stdio.h>
#include <stdlib.h>  // For srand and rand
#include <time.h>    // For time
#include <string.h>
int main (){
    //chargement_init("hi.bin",10) ;
    /* Tenreg e ; 
    e.matricule = 12 ; 
    strcpy(e.nom,"Allag") ;
    strcpy(e.prenom,"Yacine") ; 
    e.dateNaissance = 1112004 ;
    strcpy(e.wilayaNaissance,"Tebessa") ; 
    strcpy(e.groupeSanguin,"A+") ;
    strcpy(e.grade,"President") ; 
    strcpy(e.forceArmee,"Batman") ; 
    strcpy(e.regionMilitaire,"Alger") ; 
    insertion("hi.bin",e) ;
    printFile("hi.bin") ;  */ 
    INDEX *tabIndex ; 
    int t,i,j;
    bool trouve ; 
    tabIndex = (INDEX*)malloc(sizeof(INDEX)) ;
    chargementIndex("MATRICULE_INDEX.idx",tabIndex) ;
    //printf("%d\n",tabIndex->taille) ;
    //for (int i = 0 ; i<tabIndex->taille ; i++ )
    //{
      //  printf ("%d \t", tabIndex->tableau[i].cle) ; 
    // }
    insertionIndex (tabIndex,12,1,10) ;
    for (int i = 0 ; i<tabIndex->taille ; i++ )
    {
        printf ("%d \t", tabIndex->tableau[i].cle) ; 
    }
    sauvIndex("MATRICULE_INDEX.idx",tabIndex) ;
    return 0;
}
