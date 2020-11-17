
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
	return premier(l) == premier(suite(l));
}

bool QueDesZeros (Liste l){
	if (estVide(l)) return TRUE;
	else if (premier(l) == 0) QueDesZeros(suite(l));
		else return FALSE;
}

/*void EliminePositionsPaires (Liste *l){ ( NOT OK )
	int i =0;
	if (! estVide(l)) {
		while(! estVide(l)){
			if (i%2 == 0){
				depile(premier(l));
				i++;
				EliminePositionsPaires(suite(l));
			}
		}
	}
}*/

bool EstPalindrome(Liste l, Liste m){
	if (estVide(m) || estVide(l) ) return TRUE;
	else{ 
		EstPalindrome(l,suite(m));
		if (premier(l) != premier(m)) return FALSE; 
		l = suite(l);

	}
	return TRUE;

}

int MaxZerosConsecutifs_ite(Liste l){ //Version itérative
	int count = 0;
	int max = 0;
	if (estVide(l)) return count;
	while(! estVide(l)){
		if(premier(l) == 0) {
			count++; //Le compteur augmente de un (1) si la liste contient un zero
		}else{
			if(count > max) max = count; //max prend le plus grand nombre de zero consécutif trouvé
			count = 0; //Le compteur est remis à zéro lorsque l'on rencontre un autre chiffre que zero dans la liste
		}
		l = suite(l);
	}
	return max;
}

int MaxZerosConsecutifs_rec(Liste l){ //Version récursive avec sous fonction
	int Aux (Liste l, int count, int max){
		while(! estVide(l)){
			if(premier(l) == 0) {
			count++;
			}else{
				if(count > max) max = count;
			count = 0;
			}
			l = suite(l);
		}
	return max;
	}
	Aux (l,0,0);
	
}

/*************************************************/
/*                                               */
/*           Main                                */
/*                                               */
/*************************************************/

void poup (Liste l)
{
        printf("Double Affichage \n") ;
        affiche_rec(l) ;
        affiche_iter(l) ;

        printf("Longueur en double %d %d \n\n", 
                           longueur_rec(l), 
                           longueur_iter(l) 
               ) ;
}

int main(int argc, char** argv)
{
    Liste l ;

        initVide (&l) ;

          poup(l) ;

             empile(4, &l) ;

          poup(l) ;

             empile(5, &l) ;
             empile(6, &l) ;
             empile(7, &l) ;
             empile(8, &l) ;
             empile(9, &l) ;

          poup(l) ;

        VireDernier_rec  (&l) ;
        VireDernier_iter (&l) ;
        depile(& l) ;

          poup(l) ;

    VideListe(&l);

    //Tests de la fonction DebutDeuxIdentiques
    empile(2, &l) ;
    empile(5, &l) ;
    empile(5, &l) ;
    if ( DebutDeuxIdentiques(l)) printf("ok\n"); else printf("false \n");
    VideListe(&l);

    //Tests de la fonction QueDesZeros
    empile(0, &l) ;
    empile(0, &l) ;
    empile(0, &l) ;
    empile(0, &l) ;
    if ( QueDesZeros(l)) printf("QueDesZeros ok\n"); else printf("false \n");
    VideListe(&l);

    //Tests de la fonction EstPalindrome
    empile(2, &l) ;
    empile(1, &l) ;
    empile(2, &l) ;
    poup(l);

    Liste m;
    initVide(&m);
    empile(2, &m) ;
    empile(1, &m) ;
    empile(2, &m) ;
    poup(m);
    if ( EstPalindrome(l,m)) printf("palindrome ok\n"); else printf("false \n");
    VideListe(&l);
    VideListe(&m);

    //Tests de la fonction MaxZerosConsecutifs
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
    printf("MaxZerosConsecutifs en iteratif de l : %d\n", MaxZerosConsecutifs_ite(l));
    printf("MaxZerosConsecutifs en récursif de l : %d\n", MaxZerosConsecutifs_rec(l));

    empile(4, &m) ;
    empile(8, &m) ;
    empile(2, &m) ;
    empile(9, &m) ;
	printf("MaxZerosConsecutifs en iteratif de m : %d\n", MaxZerosConsecutifs_ite(m));
	printf("MaxZerosConsecutifs en récursif de m : %d\n", MaxZerosConsecutifs_rec(m));
    

    return 0;
}




