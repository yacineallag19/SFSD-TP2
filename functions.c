#include "functions.h"
#include "maps.h"
#include <stdio.h>
#include <string.h>

void initEntete(FILE* f) 
{
	Tentete entete;
	entete.nombreBloc=0;
	fseek(f,0,SEEK_SET);
	fwrite(&entete ,sizeof(Tentete),1,f);
	return ;
}

void ouvrir(FILE **f, char *nomfichier, char *mode) 
{
    if (strcmp(mode, "A") == 0) 
	{
        *f = fopen(nomfichier, "ab+");
    } else if (strcmp(mode, "N") == 0) 
	{
        *f = fopen(nomfichier, "wb+");
        initEntete(*f);
    } else 
	{
        fprintf(stderr, "Invalid mode: %s\n", mode);
        exit(EXIT_FAILURE);
    }
    if (*f == NULL) 
	{
        perror("Error opening the file");
        exit(EXIT_FAILURE);
    }
}


void fermer (FILE *f) // fermer fichier
{
	fclose(f) ;
}

bool lireDir (FILE *f , int i , BUFFER* buf) // ecrire le bloc numero i dans buf
{

    if (f == NULL || i <= 0 || fseek(f, (i - 1) * sizeof(BUFFER) + sizeof(Tentete), SEEK_SET) != 0) {
        return false;
    }

    if (fread(buf, sizeof(BUFFER), 1, f) != 1) {
        return false;  // Check if the read was successful
    }

    return true;

}

bool ecrireDir (FILE *f , int i , BUFFER* buf) // ecrire buf dans le bloc numero i
{
    if (f == NULL || i <= 0 || fseek(f, (i - 1) * sizeof(BUFFER) + sizeof(Tentete), SEEK_SET) != 0) {
        return false;
    }

    if (fwrite(buf, sizeof(BUFFER), 1, f) != 1) {
        return false;  // Check if the write was successful
    }

    return true;
}


int entete(FILE *f, int i ) // recuperer nombre de bloc
{
		Tentete varentete;
		fseek(f,0,SEEK_SET);
		fread(&entete,sizeof(Tentete),1,f);
	    return varentete.nombreBloc ;
}



void affentete(FILE *f, int valeur , int i) // modifier le nombre de bloc par valeur
{
	fseek(f,0,SEEK_SET);
	Tentete varentete;
    fread(&varentete , sizeof(Tentete) , 1 , f);
    varentete.nombreBloc = valeur ;
	fseek(f, 0, SEEK_SET);
    fwrite(&varentete,sizeof(Tentete),1,f) ;
}


int allocBloc(FILE *f) // Retourne le numéro d’un nouveau bloc alloué à F
{
	affentete(f,entete(f,1)+1,1);
	return entete(f,1);	
}


int Ientete(FILE *f) // recuperer nombre de bloc
{
		enteteIndex varentete;
		fseek(f,0,SEEK_SET);
		fread(&varentete,sizeof(enteteIndex),1,f);
	    return varentete.nombreIbloc ;
}



void affIentete(FILE *f, int valeur) // modifier le nombre de bloc par valeur
{
	fseek(f,0,SEEK_SET);
	enteteIndex varentete;
    varentete.nombreIbloc = valeur ;
    fwrite(&varentete,sizeof(enteteIndex),1,f) ;
}


bool lireIbloc (FILE *f , int i , Ibloc* buf) // ecrire le bloc numero i dans buf
{

    if (f == NULL || i <= 0 || fseek(f, (i - 1) * sizeof(Ibloc) + sizeof(enteteIndex), SEEK_SET) != 0) {
        return false;
    }

    if (fread(buf, sizeof(Ibloc), 1, f) != 1) {
        return false;  // Check if the read was successful
    }

    return true;

}

bool ecrireIbloc (FILE *f , int i , Ibloc* buf) // ecrire le bloc numero i dans buf
{

    if (f == NULL || i <= 0 || fseek(f, (i - 1) * sizeof(Ibloc) + sizeof(enteteIndex), SEEK_SET) != 0) {
        return false;
    }

    if (fwrite(buf, sizeof(Ibloc), 1, f) != 1) {
        return false;  // Check if the read was successful
    }

    return true;

}

void fillIndex (INDEX *tabIndex , Ibloc *buf , int start , int *end)
{
	int k = 0 ;
	int j = buf->NbCle ;
	int i = start ;
	while (k<j)
	{
		tabIndex->tableau[i] = buf->tableauI[k];
		tabIndex->taille = tabIndex->taille + 1;
		i++;
		k++;
	}
	*end = i ;
	return ;
}


void getIbuffer (INDEX *tabIndex , Ibloc *buf , int start , int *end)
{
	int k = 0 ;
	int i = start ;
	int j = tabIndex->taille ;
	buf->NbCle = 0 ;
	while ((i<j) && (k<1024))
	{
		buf->tableauI[k] = tabIndex->tableau[i] ;
		buf->NbCle= buf->NbCle+1 ;
		k++ ;
		i++ ;
	}
	if (i == j)
	{
		*end = -1 ;
	}
	else {
		*end = i ;
	}
	return ;
}

void chargementIndex (char *path, INDEX *tabIndex)
{
	int j,debut,fin ;
	FILE *f ;
	ouvrir(&f,path,"A") ;
	Ibloc *buf ;
	buf = (Ibloc*)malloc(sizeof(Ibloc)) ; 
	j = Ientete(f) ;
	debut = 0 ;
	tabIndex->taille = 1 ; 
	for (int i = 1 ; i <= j ; i++ )
	{
		lireIbloc(f,i,buf) ;
		fillIndex(tabIndex,buf,debut,&fin) ;
		debut = fin + 1 ;
	}


}

void sauvIndex (char *path , INDEX *tabIndex)
{
	int j,debut,fin ;
	FILE *f ;
	ouvrir(&f,path,"A") ;
	Ibloc *buf ;
	buf = (Ibloc*)malloc(sizeof(Ibloc)) ; 
	j = tabIndex->taille ;
	if (j%1024 == 0)
	{
		j = j/1024 ;
	}
	else
	{
		j = (j/1024) + 1 ;
	}
	affIentete(f,j) ;
	debut = 0 ;
	for (int i = 1 ; i <= j ; i++ )
	{
		getIbuffer(tabIndex,buf,debut,&fin) ;
		ecrireIbloc(f,i,buf) ;
		if (fin == -1)
		{
			break ;
		}
		debut = fin + 1 ;
	}
    return ;

}

void rechercheIndex (INDEX *tabIndex , int valeur, bool *trouve , int *numBloc , int *posBloc, int *place)
{
	int length = tabIndex->taille ;
	int sup = length - 1 ;
	int inf = 0 ;
	int k,temp , tempPos ;
	*trouve = false ;
	while (inf <= sup)
	{
		k = (sup + inf ) / 2 ;
		temp = tabIndex->tableau[k].cle ; 
		if (temp == valeur)
		{
			*trouve = true;
			*numBloc = tabIndex->tableau[k].numeroBloc ;
	        *posBloc = tabIndex->tableau[k].deplacement ;
	        *place = k ;
			return ; 
		}
		else 
		{
			if (temp > valeur)
			{
				sup = k - 1;
			}
			else 
			{
				inf = k + 1 ;
			}
		}
	}
	*numBloc = -1 ;
	*posBloc = -1 ;
	if (temp < valeur)
	{
		*place = inf ;
	}
	else 
	{
		*place = k ;
	}
}

void insertionIndex (INDEX *tabIndex, int valeur, int numBloc , int posBloc)
{
    bool trouve;
	int i,j,position ;
	rechercheIndex (tabIndex,valeur,&trouve,&i,&j,&position) ;
	if (!trouve)
	{
		int k = tabIndex->taille ;
	    while (k > position)
	    {
	    	tabIndex->tableau[k] = tabIndex->tableau[k-1] ;
	    	k--;
	    }
	    tabIndex->tableau[position].cle = valeur ;
	    tabIndex->tableau[position].numeroBloc = numBloc ;
	    tabIndex->tableau[position].deplacement = posBloc ;
	    tabIndex->taille ++ ;
	    return ;
	}
}

void suppressionIndex (INDEX *tabIndex , int valeur)
{
	bool trouve ;
	int i,j,position ;
	rechercheIndex(tabIndex,valeur,&trouve,&i,&j,&position) ;
	if (trouve)
	{
		int i = position ;
		int k = tabIndex->taille ;
		while (i < k-1) 
		{
			tabIndex->tableau[i] = tabIndex->tableau[i+1] ;
			i++ ;
		}
		tabIndex->taille-- ;
		return ;
	}
}




int generateNumber (int inf , int sup)
{
	return rand() % (sup - inf + 1) + inf ;
}
 

void generateMatricule (BUFFER *buf , INDEX *tabIndex , int numBloc , int position) 
{
	bool notPossible = true ;
	int matr,i,j,t ;
	while (notPossible)
	{
	    matr = generateNumber(111111,999999) ;
	    rechercheIndex (tabIndex,matr,&notPossible,&i,&j,&t) ;
	}
	buf->tab[position].matricule = matr ;
	insertionIndex(tabIndex,matr,numBloc,position) ;
	return ;
}

void generateNom (BUFFER *buf , int position)
{
	int taille = generateNumber(4,30) ; 
	int j ;
	int i = 0 ; 
	while (i < taille)
	{
		j = generateNumber(1,26) ;
		buf->tab[position].nom[i] = letters[j-1] ;
		i++ ;
	}
	return ;
}


void generatePrenom (BUFFER *buf , int position)
{
	int taille = generateNumber(4,30) ; 
	int j ;
	int i = 0 ; 
	while (i < taille)
	{
		j = generateNumber(1,26) ;
		buf->tab[position].prenom[i] = letters[j-1] ;
		i++ ;
	}
	return ;
}

void generateDateNaissance (BUFFER *buf , int position )
{
	int date = 0 ;
	int annee = generateNumber(1942,2005) ;
	date += annee ;
	int mois = generateNumber(1,12) ;
	date += (mois * 10000 ) ;
	int jour ;
	if (mois == 2 )
	{
		if (((annee % 100 != 0) && (annee % 4 == 0) || (annee % 400 == 0)))
		{
			jour = generateNumber(1,29) ;
		}
		else 
		{
			jour = generateNumber(1,28) ;
		}
    }
    else 
    {
    	if (((mois <= 7) && (mois % 2 == 1)) || ((mois >= 8) && (mois % 2 == 0)))
	    {
		   jour = generateNumber(1,31) ;
	    }
	    else if (((mois < 7) && (mois % 2 == 0)) || ((mois > 8) && (mois % 2 == 1)))
	    {
		   jour = generateNumber(1,30) ;
	    }
    }
	date += jour * 1000000 ;
    buf->tab[position].dateNaissance = date ;
    return ;
}

void generateWilayaNaissance (BUFFER *buf , int position )
{
	int i = generateNumber(1,58) ;
	strcpy(buf->tab[position].wilayaNaissance,wilayas[i-1]) ;
	return ;
}

void generateGroupeSanguin (BUFFER *buf,int position) 
{
	int i = generateNumber(1,8) ;
	strcpy(buf->tab[position].groupeSanguin,groupesSanguin[i-1]) ;
	return ;
} 

void generateGrade (BUFFER *buf,int position )
{
	int i = generateNumber(1,19) ;
	strcpy(buf->tab[position].grade,grades[i-1]) ;
	return ;

}

void generateForce (BUFFER *buf,int position) 
{
	int i = generateNumber(1,8) ;
	strcpy(buf->tab[position].forceArmee,forces[i-1]) ;
	return ;
} 

void generateRegion (BUFFER *buf,int position) 
{
	int i = generateNumber(1,6) ;
	strcpy(buf->tab[position].regionMilitaire,regions[i-1]) ;
	return ;
} 



void chargement_init(char* nomfichier,int n)
{
	BUFFER *buf ; 
	INDEX *tabIndex ;
	FILE *f ; 
	tabIndex = (INDEX*)malloc(sizeof(INDEX)) ;
	buf = (BUFFER*)malloc(sizeof(BUFFER)) ;
	ouvrir(&f,nomfichier,"N");
	int i=1, j=0;
	if (f==NULL)
	{
		printf("error opening the file");
	}
	else
	{
		for (int k=1;k<=n;k++)
		{
			generateMatricule(buf,tabIndex,i,j);
			generateDateNaissance(buf,j);
			generateForce(buf,j);
			generateGrade(buf,j);
			generateGroupeSanguin(buf,j);
			generateNom(buf,j);
			generatePrenom(buf,j);
			generateRegion(buf,j);
			generateWilayaNaissance(buf,j);
			if(j==MAX)
			{
				buf->nb=j;
				ecrireDir(f,i,buf);
				j=0;
				i=i+1;
				affentete(f,i,1);
			}
			j++;

		}
		buf->nb=j;
		ecrireDir(f,i,buf);
		affentete(f,i,1);

	}
	sauvIndex("MATRICULE_INDEX.idx",tabIndex) ;
	fermer(f);
}


void insertion(char* nomfichier,Tenreg e,INDEX *tabIndex) 
{
    FILE *f ; 
	ouvrir(&f,nomfichier,"A");
	int i ;
	BUFFER *buf;
	int n=entete(f,1);
	if (n!=0)
	{
		lireDir(f,n,buf);
	}
	else
	{
		n=1;
		affentete(f,1,1);
		buf->nb=0;
	}
	if (buf->nb<MAX)
	{
		buf->tab[buf->nb]=(e);
		buf->nb=buf->nb+1;
		ecrireDir(f,n,buf);
	}
	else
	{
		buf->nb=1;
		buf->tab[0]=e;
		ecrireDir(f,n+1,buf);
		affentete(f,n+1,1);
	}
	insertionIndex(tabIndex,e.matricule,n,buf->nb-1) ;
	fermer(f);

}


void suppression(char* nomfichier, int mat, INDEX *tabIndex)
{
	FILE *f ; 
	BUFFER *buf;
	buf = (BUFFER*)malloc(sizeof(BUFFER)) ;
	BUFFER buf2;
	int i,j,t,n ;
	bool trouve=true;
	ouvrir(&f,nomfichier,"A");
	rechercheIndex(tabIndex,mat,&trouve,&i,&j,&t) ; 
	buf2.nb=0;
	trouve=true;
	if (trouve)
	{
		n=entete(f,1);
		if(i!=n)
		{
			lireDir(f,i,buf);
			lireDir(f,n,&buf2);
			buf->tab[j]=buf2.tab[buf2.nb-1];
			buf2.nb=buf2.nb-1;
			ecrireDir(f,i,buf);
			if (buf2.nb>0)
			{
				ecrireDir(f,n,&buf2);
			}
			else
			{
				affentete(f,n-1,1);
			}
		}
		else
		{
			lireDir(f,n,buf);
			buf->tab[j]=buf->tab[buf->nb-1];
			buf->nb=buf->nb-1;
			if(buf->nb>0)
			{
				ecrireDir(f,n,buf);
			}
			else
			{
				affentete(f,n-1,1);
			}
		}
    suppressionIndex(tabIndex,mat) ; 
	fermer(f);
	}
}


/*void printFile (char *nomfichier)
{
	FILE *f ; 
	BUFFER *buf ; 
	buf = (BUFFER*)malloc(sizeof(BUFFER)) ;
	int n,i,k,j ; 
	ouvrir(&f,nomfichier,"A") ; 
	n = entete(f,1) ; 
	i = 1 ; 
	for (i;i<=12;i++)
	{
		j = 0 ;
		lireDir(f,i,buf) ;
		k =  buf->nb ; 
		for (j;j<=100;j++)
		{
			printf("Matricule: %d \n",buf->tab[j].matricule) ;
			printf("Nom: %s\n",buf->tab[j].nom) ;
			printf("Prenom: %s\n",buf->tab[j].prenom) ;
			printf("Date de naissance: %d\n",buf->tab[j].dateNaissance) ;
			printf("Wilaya: %s\n",buf->tab[j].wilayaNaissance) ;
			printf("group: %s\n",buf->tab[j].groupeSanguin) ;
			printf("grade: %s\n",buf->tab[j].grade) ;
			printf("Force Armee: %s\n",buf->tab[j].forceArmee) ;
			printf("region: %s\n",buf->tab[j].regionMilitaire) ;
		}
	}
	fermer(f) ; 
} */








