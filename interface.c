#include "interface.h"

void DisplaySearchSoldier() {
  int matricule, i, j, t;
  char filepath[50];
  bool trouve;
  printf("\033c\n");
  printf("\033[1mle chemin du fichier:");
  scanf(" %99[^\n]", filepath);

  printf("\033[1mTapez le Matricule:");
  scanf(" %d", &matricule);

  printf("\n");
  printf("\033[1mRECHERCHE EN COURS...");

  recherche(filepath, matricule, &trouve, &i, &j, &t);
  if (trouve) {
    printf("\033[1;32mElement Trouve sur le bloc %d, position %d\033[0m\n", i,
           j);
  } else {
    printf("\033[1;31mElement n'existe pas\033[0m\n");
  }

  return;
}
void DisplayAddSoldier() {
  printf("\033c\n");
  bool test;
  int jour, mois, annee;
  char filepath[50];
  Tenreg e;

  printf(
      "\033[1;31mDans le cas ou le matricule existe, aucun insertion va etre "
      "faite\033[0m\n");

  printf("\033[1mEntrez le chemin du fichier:");
  scanf(" %s", filepath);
  printf("\n");

  printf("\033[1mEntrez le matricule a inserer:");
  scanf(" %d", &(e.matricule));
  printf("\n");
  do {
    printf("\033[1mEntrez le jour de naissance:");
    scanf(" %d", &jour);
    printf("\n");
    printf("\033[1mEntrez le mois de naissance:");
    scanf(" %d", &mois);
    printf("\n");
    printf("\033[1mEntrez l'annee de naissance:");
    scanf(" %d", &annee);
    printf("\n");
    test = is_valid_date(jour, mois, annee);
    if (!test) {
      printf("\033[1;31mDate invalid, retapez la date\033[0m\n");
    }
  } while (!test);
  e.dateNaissance = annee + mois * 10000 + jour * 1000000;

  printf("\033[1mEntrez le nom:");
  scanf(" %s", e.nom);
  printf("\n");

  printf("\033[1mEntrez le prenom:");
  scanf(" %s", e.prenom);
  printf("\n");

  printf("\033[1mEntrez la wilaya de naissance:");
  scanf(" %s", e.wilayaNaissance);
  printf("\n");

  printf("\033[1mEntrez le groupe sanguin:");
  scanf(" %s", e.groupeSanguin);
  printf("\n");

  printf("\033[1mEntrez le grade:");
  scanf(" %s", e.grade);
  printf("\n");

  printf("\033[1mEntrez la force armee:");
  scanf(" %s", e.forceArmee);
  printf("\n");

  printf("\033[1mEnrtez la region:");
  scanf(" %s", e.regionMilitaire);
  printf("\n");

  printf("\033[1;32mInsertion EN COURS...\033[0m");
  insertion(filepath, e);
  printf("\033[1;32mC'est bon vous pouvez verrifier le fichier...\033[0m\n\n");
  return;
}
void DisplayDeleteSoldier() {
  printf("\033c\n");
  char filepath[50];
  int matricule;
  printf("\033[1mle chemin du fichier:");
  scanf(" %99[^\n]", filepath);

  printf("\033[1mTapez le Matricule a supprimer:\033[0m");
  scanf(" %d", &matricule);

  printf("\n");
  printf("\033[1;32mSuppression EN COURS...\033[0m\n");

  suppression(filepath, matricule);
  printf("\033[1;32mSuppression fini, verifier le fichier...\033[0m\n");
}
void DisplayRequeteIntervale() {
  printf("\033c\n");
  char filepath[50];
  int matricule1, matricule2;
  printf("\033[1mle chemin du fichier:");
  scanf(" %99[^\n]", filepath);

  do {
    printf("\033[1mTapez le Matricule inferieur:");
    scanf(" %d", &matricule1);
    printf("\033[1mTapez le Matricule superieur:");
    scanf(" %d", &matricule2);
  } while (matricule1 > matricule2);
  printf("\n");

  requeteIntervalle(filepath, matricule1, matricule2);

  return;
}
void DisplayPrintFile() {
  printf("\033c\n");
  char filepath[50];
  printf("\033[1mle chemin du fichier:");
  scanf(" %99[^\n]", filepath);
  printf("\n");
  printFile(filepath);
}

void DisplayCreateNewFile() {
  printf("\033c\n");
  char filepath[50];
  int length;
  printf("\033[1;31mAttention d'utiliser un fichier deja existant\033[0m\n");
  printf(
      "\033[1;31mAttention le fichier index est appelee 'MATRICULE_INDEX.idx' "
      "et donc il va etre mis a jour avec ce fichier\033[0m\n");
  printf("\033[1mle chemin du fichier:");

  scanf(" %99[^\n]", filepath);
  do {
    printf("\033[1mTapez le nombre de soldat:");
    scanf(" %d", &length);
  } while (length >= 1000000);

  chargement_init(filepath, length);
  printf("\033[1;32mCreation fini, verifier le fichier...\033[0m\n");
}

void DisplayChangeRegion() {
  printf("\033c\n");
  char filepath[50];
  int i;
  printf("\033[1mle chemin du fichier:");
  scanf(" %99[^\n]", filepath);
  printf("\033[1mTapez le matricule:");
  scanf(" %d", &i);
  modifierRegion(filepath, i);
}

void display() {
  int choix;
  bool keep;
  printf("\033[1m\t\t\t----------TP2 SFSD----------\n");
  printf("\t\t\t\033[1m     Allag Ahmed Yacine\n");
  printf("\t\t\t\033[1m        BOUDRAA MAHDI\n");
  keep = true;
  do {
    printf("\n");
    printf(
        "----------------------------------------------------------------------"
        "------------------\n\n\n");
    printf(
        "\033[1mCe programme sert a manipuler une simple base de donnee de "
        "l'armee algerienne\n");
    printf(
        "\033[1mIl y a un fichier deja cree -PERSONNEL-ANP_DZ.dat- si vous "
        "voulez tester notre options sur le\n");
    printf(
        "\033[1mSi vous voulez tester sur un nouver fichier, vous pouvez "
        "choisir l'option de creer un nouveau fichier, suivre les etapes et "
        "puis choisir une option\n");
    printf("\033[1mMerci de choisir une option de ces options: \n\n\n");
    printf("\033[1m0. Quitter le programme\n");
    printf("\033[1m1. Recherche d'un soldat par matricule\n");
    printf("\033[1m2. Ajouter un soldat\n");
    printf("\033[1m3. Supprimer un solday depuis matricule\n");
    printf("\033[1m4. Requete intervalle\n");
    printf("\033[1m5. Afficher tous les soldats\n");
    printf("\033[1m6. creer un nouveau fichier\n");
    printf(
        "\033[1m7. Changer la region militaire d'un soldat utilisons son "
        "matricule\n\n\n");
    printf("\033[1mTapez votre choix: ");
    scanf("%d", &choix);
    printf("\n\n\n");
    switch (choix) {
      case 0:
        printf("Merci... Sortir en cours\n");
        keep = false;
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
        DisplayCreateNewFile();
        break;
      case 7:
        DisplayChangeRegion();
        break;
      default:
        printf("Choix invalide. Veuillez saisir un nombre entre 0 et 7.\n");
        break;
    }
  } while (keep);
  return;
}
