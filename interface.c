#include "interface.h"


void display() 
{
int choix ;
bool keep ;
printf("\033[1m----------TP2 SFSD----------\n");
printf("\t\t\t\t\033[1mAllag Ahmed Yacine\n");
printf("\t\t\t\t\033[1mBOUDRAA MAHDI\n");
keep = true ;
do 
{
  printf("\033[1mCe programme sert a manipuler une simple base de donnee de l'armee algerienne\n");
  printf("\033[1mIl y a un fichier deja cree -- si vous voulez tester notre options sur le\n");
  printf("\033[1mSi vous voulez tester sur un nouver fichier, vous pouvez choisir l'option de creer un nouveau fichier, suivre les etapes et puis choisir une option\n");
  printf("\033[1mMerci de choisir une option de ces options: \n\n\n");
  printf("\033[1m0. Quitter le programme");
  printf("\033[1m1. Recherche d'un soldat par matricule\n");
  printf("\033[1m2. Ajouter un soldat\n");
  printf("\033[1m3. Supprimer un solday depuis matricule\n");
  printf("\033[1m4. Requete intervalle\n");
  printf("\033[1m5. Afficher tous les soldats\n");
  printf("\033[1m6. Changer la region militaire d'un soldat utilisons son matricule\n\n\n");
  printf("\033[1mTapez votre choix: ");
  scanf("%d",&choix) ;
  printf("\n\n\n")
  switch (choice) 
  {
            case 0:
                printf("Merci... Sortir en cours\n");
                keep = false ;
                break;
            case 1:
                DisplaySearchSoldier();
                break;
            case 2:
                DisplayAddSoldier();
                break;
            case 3:
                DisplayDeleteSoldier();
                break;
            case 4:
                DisplayRequeteIntervale();
                break;
            case 5:
                DisplayPrintFile();
                break;
            case 6:
                DisplayChangeRegion();
                break;
            default:
                printf("Choix invalide. Veuillez saisir un nombre entre 0 et 6.\n");
    }



} while (keep)
}


