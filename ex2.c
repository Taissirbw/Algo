#include <stdio.h>
#include <stdlib.h>

/*************************************************/
/*                                               */
/*                sucre syntaxique               */
/*                                               */
/*************************************************/

#define AND &&
#define OR ||
#define ISNOT !=
#define NOT !
#define then

typedef enum { FALSE, TRUE} bool;

/*************************************************/
/*                                               */
/*          definition type liste                */
/*                                               */
/*************************************************/

typedef struct Bloc
{
    int nombre;
    struct Bloc *suivant;
} Bloc;

typedef Bloc *Liste ;

/*************************************************/
/*                                               */
/*                predeclarations                */
/*                                               */
/*************************************************/

/* initialise une Liste à vide */
void initVide(Liste *L);

/* renvoie 1 si la Liste en parametre est vide, 0 sinon */
bool estVide(Liste l);

/* renvoie le premier element de la Liste en parametre */
int premier(Liste l);

/* renvoie une nouvelle Liste correspondant a celle en parametre, avec l'element x ajoute en haut de la pile */
Liste ajoute(int x, Liste l);

/* modifie la Liste en parametre: x est ajoute comme premier element */
void empile(int x, Liste* L);

/* renvoie une nouvelle Liste correspondant a celle en parametre sans son premier element */
Liste suite(Liste l);

/* modifie la Liste en parametre: le premier element est retire */
void depile(Liste* l);

/* affichage simple en recursif et en iteratif */
void affiche_rec(Liste l);
void affiche_iter(Liste l);

/* longueur en recursif et en iteratif */
int longueur_rec (Liste l);
int longueur_iter (Liste l);

/*  Elimination du dernier element en recursif et en iteratif  */
/*  VD est la sousprocedure utilitaire de la version recursive */
void VD (Liste *L);
void VireDernier_rec (Liste *L);
void VireDernier_iter (Liste *L);


/*************************************************/
/*                                               */
/*                briques de base                */
/*                                               */
/*************************************************/


void initVide( Liste *L)
{
    *L = NULL ;
}

bool estVide(Liste l)
{
    return l == NULL ;
}

int premier(Liste l)
{
    return l->nombre ;
}

Liste ajoute(int x, Liste l)
{
    Liste tmp = (Liste) malloc(sizeof(Bloc)) ;
    tmp->nombre = x ;
    tmp->suivant = l ;
    return tmp ;
}

void empile(int x, Liste *L)
{
      *L = ajoute(x,*L) ;
}

Liste suite(Liste l)
{
    return l->suivant ;
}


void depile(Liste *L)
{
    Liste tmp = *L ;
    *L = suite(*L) ;
    free(tmp) ;
}

/*************************************************/
/*                                               */
/*     Affiche, avec les briques de base         */
/*                                               */
/*************************************************/

void affiche_rec(Liste l)
{
    if(estVide(l))
        printf("\n");
    else
    {
        printf("%d ", premier(l));
        affiche_rec(suite(l));
    }
}


void affiche_iter(Liste l)
{
    Liste L2 = l;
    while(!estVide(L2))
    {
        printf("%d ", premier(L2));
        L2 = suite(L2);
    }
    printf("\n");
}

/*************************************************/
/*                                               */
/*     Longueur, sans les briques de base        */
/*                                               */
/*************************************************/

int longueur_rec (Liste l)
{
    if (l == NULL)
         return 0 ;
    else return (1 + longueur_rec(l->suivant)) ;
}


int longueur_iter (Liste l)
{
    Liste P = l;
    int cpt = 0 ;
    while (P ISNOT NULL)
    {   P = P->suivant ;
        cpt++ ;
    }
    return cpt ;
}

/*************************************************/
/*                                               */
/*       VireDernier,                            */
/*               sans les briques de base,       */
/*               ni le "->"                      */
/*                                               */
/*************************************************/

void VD (Liste *L)
          // *L non NULL ie liste non vide
{
     if ( ((**L).suivant) == NULL )
            depile(L) ;   // moralement : depile(& (*L)) ;
     else VD (& ( (**L).suivant )) ;
}

void VireDernier_rec (Liste *L)
{
     if ( (*L) ISNOT NULL )
          VD(L);        // moralement : VD(& (*L)) ;
}

void VireDernier_iter (Liste *L)
{
    if ( (*L) ISNOT NULL)
    {
        while ( ((**L).suivant) ISNOT NULL )
                 L = & ( (**L).suivant ) ;
        free(*L) ;
        *L = NULL ;
     }
}


/*************************************************/
/*                                               */
/*       Libere la memoire                       */
/*                                               */
/*************************************************/

void VideListe(Liste *L)
{
    if(NOT(estVide(*L)))
    {
        depile(L);
        VideListe(L);
    }

}

/*************************************************/
/*                                               */
/*          Fonction/Procédure exo2              */
/*                                               */
/*************************************************/

bool DebutDeuxIdentiques (Liste l){
  if (estVide(l)) return FALSE;
  else if (estVide(suite(l))) return FALSE;
  else return premier(l) == premier(suite(l));
}

bool QueDesZeros (Liste l){
	if (estVide(l)) return TRUE;
	else if (premier(l) == 0) QueDesZeros(suite(l));
		else return FALSE;
}


bool SousEnsemble (Liste l1, Liste l2){ //Fonction très très trèès moche
	if (longueur_rec(l1) > longueur_rec(l2)) return FALSE;
	else if (estVide(l1)) return TRUE;
	else if (estVide(l2)) return FALSE;
	else
		if (premier(l1)==premier(l2)) SousEnsemble(suite(l1),suite(l2));
		else SousEnsemble(l1,suite(l2));

}

/*
List Permutation(int n){
  List ATPTL(int n, List LL){
    if (LL == NULL) return [];
  }
  if n = 0 return [[]];
  else return ATPTL(n, Permutation(n-1));
}
*/

void EliminePositionsPaires (Liste *l){
  void Aux(Liste *l, int i){
    if (! estVide(*l)){
      if (i%2 == 0){
        depile(l);
        Aux(l, 1);
      } else {
        Aux(&((**l).suivant), 0);
      }
     }
  }
  Aux(l, 1);
}

void Begaye(Liste *L){
  if (! estVide(*L)){
    if (premier(*L) > 0){
      Begaye(&((**L).suivant));
      empile(premier(*L), L);
    }else{
      depile(L);
      Begaye(L);
    }
  }
}

int MaxZerosConsecutifs_ite(Liste l){ //Version itérative
	int count = 0;
	int max = 0;
	if (estVide(l)) return count;
	while(! estVide(l)){
		if(premier(l) == 0) {
			count++; //Le compteur augmente de un (1) si la liste contient un zero
			if(count > max) max = count;
		}else{
			if(count > max) max = count; //max prend le plus grand nombre de zero consécutif trouvé
			count = 0; //Le compteur est remis à zéro lorsque l'on rencontre un autre chiffre que zero dans la liste
		}
		l = suite(l);
	}
	return max;
}


int MaxZerosConsecutifs_rec(Liste l){ //Version récursive avec sous fonction (deuxieme version)
	int Aux (Liste l, int count, int max){
		if(estVide(l)) return max;
		else{
			if(premier(l) == 0) {
				if(count+1 > max) max = count+1;
				Aux(suite(l),count+1,max);
			}else{
				if(count > max) max = count;
				Aux(suite(l),0,max);
			}
		}
	}
	Aux (l,0,0);
}

int MaxZerosConsecutifs_out(Liste l){ //Version récursive avec sous fonction avec 2 arg en out (troisieme version)
	int max;
	int count;
	void Aux (Liste l, int *count, int *max){
		*max = 0;
		*count = 0;
		if(!estVide(l)) {

			Aux(suite(l),count,max);
			
			if(premier(l) == 0) {
				*count += 1;
				if(*count > *max){ *max = *count; }
			}else{
				if(*count > *max){ *max = *count; }
				*count = 0;
			}

		}
	
	}
	Aux (l,&count,&max);
	return max;
}

bool EstPalindrome(Liste l){
  Liste p;
  initVide(&p);
  p = l;
  void Aux(Liste *p, Liste l, bool *res){
	   if (estVide(l)) *res = TRUE;
	   else{
		  Aux(p, suite(l), res);
		  if (premier(*p) != premier(l)) *res = FALSE;
      *p = suite(*p);
	   }
  }
  bool res;
  Aux(&p, l, &res);
  VideListe(&p);
  return res;
}


/*************************************************/
/*                                               */
/*           Main                                */
/*                                               */
/*************************************************/
int main(int argc, char** argv){



/**--------------------TEST DES FONCTIONS ET PROCEDURES--------------------**/
    Liste l ;
    initVide(&l) ;
    Liste m;
    initVide(&m);

    /* DebutDeuxIdentiques */
    printf("Test de la fonction DebutDeuxIdentiques \n");
    empile(2, &l) ;
    empile(5, &l) ;
    empile(5, &l) ;
    affiche_rec(l);
    if ( DebutDeuxIdentiques(l)) printf("Vrai \n"); else printf("Faux \n");
    VideListe(&l);

    /* QueDesZeros */
    printf("\nTest de la fonction QueDesZeros \n");
    empile(0, &l) ;
    empile(0, &l) ;
    empile(0, &l) ;
    empile(0, &l) ;
    empile(0, &l) ;
    affiche_rec(l);
    if ( QueDesZeros(l)) printf("Vrai\n"); else printf("Faux \n");
    VideListe(&l);

    /* SousEnsemble */
    printf("\nTests de la fonction SousEnsemble \n" );
    empile(17, &l) ;
    empile(6, &l) ;
    empile(2, &l) ;
    printf("Liste l : \n");
    affiche_rec(l);

    empile(33, &m) ;
    empile(17, &m) ;
    empile(12, &m) ;
    empile(7, &m) ;
    empile(6, &m) ;
    empile(5, &m) ;
    empile(4, &m) ;
    empile(2, &m) ;
    empile(1, &m) ;
    printf("Liste m : \n");
    affiche_rec(m);
    if ( SousEnsemble(l,m)) printf("Vrai \n"); else printf("Faux\n");
    VideListe(&l);
    VideListe(&m);


    /* EliminePositionsPaires */
    printf("\nTest de la fonction EliminePositionsPaires \n");
    empile(2, &l);
    empile(1, &l);
    empile(6, &l);
    empile(8, &l);
    empile(8, &l);
    empile(3, &l);
    printf("Fonction EliminePositionsPaires Avant : \n");
    affiche_rec(l);
    EliminePositionsPaires(&l);
    printf("Fonction EliminePositionsPaires Après : \n");
    affiche_rec(l);
    VideListe(&l);

    /* Begaye */
    printf("\n Test de la fonction Begaye\n");
    empile(8, &l);
    empile(8, &l);
    empile(-2, &l);
    empile(6, &l);
    empile(0, &l);
    empile(1, &l);
    empile(2, &l);
    printf("Fonction Begaye Avant : \n");
    affiche_rec(l);
    Begaye(&l);
    printf("Fonction Begaye Après : \n");
    affiche_rec(l);
    VideListe(&l);

    /* MaxZerosConsecutifs */
    printf("\nTests de la fonction MaxZerosConsecutifs \n");
    empile(9, &l) ;
    empile(7, &l) ;
    empile(0, &l) ;
    empile(0, &l) ;
    empile(0, &l) ;
    empile(8, &l) ;
    empile(0, &l) ;
    empile(7, &l) ;
    empile(0, &l) ;
    empile(0, &l) ;
    empile(0, &l) ;
    empile(0, &l) ;
    affiche_rec(l);
    printf("MaxZerosConsecutifs en iteratif de l : %d\n", MaxZerosConsecutifs_ite(l));
    printf("MaxZerosConsecutifs en récursif de l : %d\n", MaxZerosConsecutifs_rec(l));
    printf("MaxZerosConsecutifs en récursif out de l : %d\n", MaxZerosConsecutifs_out(l));

    empile(4, &m) ;
    empile(8, &m) ;
    empile(2, &m) ;
    empile(9, &m) ;
    affiche_rec(m);
	  printf("MaxZerosConsecutifs en iteratif de m : %d\n", MaxZerosConsecutifs_ite(m));
	  printf("MaxZerosConsecutifs en récursif de m : %d\n", MaxZerosConsecutifs_rec(m));
	  printf("MaxZerosConsecutifs récursif out de m : %d\n", MaxZerosConsecutifs_out(m));


    /* EstPalindrome */
    printf("\nTests de la fonction EstPalindrome \n" );
    empile(2, &l) ;
    empile(1, &l) ;
    empile(5, &l) ;
    empile(5, &l) ;
    empile(1, &l) ;
    empile(2, &l) ;
    printf("Liste l : \n");
    affiche_rec(l);
    if ( EstPalindrome(l)) printf("Vrai \n"); else printf("Faux\n");
    VideListe(&l);



    return 0;
}

/*
void poup (Liste l)
{
        printf("Double Affichage \n") ;
        affiche_rec(l) ;
        affiche_iter(l) ;

        printf("Longueur en double %d %d \n\n",
                           longueur_rec(l),
                           longueur_iter(l)
               ) ;
}*/
