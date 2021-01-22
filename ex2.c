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
/*      definition type liste de liste           */
/*                                               */
/*************************************************/

typedef struct ListeDe {
  Liste tete;
  struct ListeDe *suivante;
} ListeDe;

typedef ListeDe *ListeDeListe;

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

/*---------Prédéclaration fonctions et procédures Listes de Listes-----------*/

void initVideDe(ListeDeListe *LL);
bool estVideDe(ListeDeListe ll);
Liste premierDe(ListeDeListe ll);
ListeDeListe ajouteDe(Liste l, ListeDeListe ll);
ListeDeListe suiteDe(ListeDeListe ll);



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
/*          briques de base ListeDe              */
/*                                               */
/*************************************************/

void initVideDe(ListeDeListe *LL){
  *LL = NULL;
}

bool estVideDe(ListeDeListe ll){
  return ll == NULL;
}

Liste premierDe(ListeDeListe ll){
  return ll->tete;
}
ListeDeListe ajouteDe(Liste l, ListeDeListe ll){
  ListeDeListe tmp = (ListeDeListe) malloc(sizeof(Liste)) ;
  tmp->tete = l ;
  tmp->suivante = ll ;
  return tmp;
}

ListeDeListe suiteDe(ListeDeListe ll){
  return ll->suivante;
}

void afficheDe(ListeDeListe ll)
{
    void Aux(ListeDeListe ll, int i){
      if(estVideDe(ll))
          printf("\n");
      else
      {
          printf("%d >> ", i);
          affiche_rec(premierDe(ll));
          Aux(suiteDe(ll), i + 1);
      }
    }
    Aux(ll, 1);
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

/****************************/
/*    DebutDeuxIdentiques   */
/****************************/
bool DebutDeuxIdentiques (Liste l){
  if (estVide(l)) return FALSE;
  else if (estVide(suite(l))) return FALSE;
  else return premier(l) == premier(suite(l));
}

/****************************/
/*        QueDesZeros       */
/****************************/
bool QueDesZeros (Liste l){
	if (estVide(l)) return TRUE;
	else if (premier(l) == 0) QueDesZeros(suite(l));
		else return FALSE;
}

/****************************/
/*       SousEnsemble       */
/****************************/
bool SousEnsemble (Liste l1, Liste l2){
	if (longueur_rec(l1) > longueur_rec(l2)) return FALSE;
	else if (estVide(l1)) return TRUE;
	else if (estVide(l2)) return FALSE;
	else
		if (premier(l1)==premier(l2)) SousEnsemble(suite(l1),suite(l2));
		else SousEnsemble(l1,suite(l2));

}

/****************************/
/*        Permutations      */
/****************************/
ListeDeListe AETTL(int x, ListeDeListe ll){
  if (estVideDe(ll)) return ll;
  else
    return ajouteDe(ajoute(x, premierDe(ll)), AETTL(x, suiteDe(ll)));
}

ListeDeListe ATP(int n, Liste l){
  if (estVide(l)){
    ListeDeListe ll;
    initVideDe(&ll);
    return ajouteDe(ajoute(n, l), ll);
  } else return ajouteDe(ajoute(n, l), AETTL(premier(l), ATP(n, suite(l))));
}

ListeDeListe concatene(ListeDeListe ll1, ListeDeListe ll2){
  if (estVideDe(ll1)) return ll2;
  else return ajouteDe(premierDe(ll1), concatene(suiteDe(ll1), ll2));
}

ListeDeListe ATPTL(int n, ListeDeListe ll){
  if (estVideDe(ll)) return ll;
  else return concatene(ATP(n, premierDe(ll)), ATPTL(n, suiteDe(ll)));
}

ListeDeListe permutation(int n){
  if (n==0){
    ListeDeListe ll;
    initVideDe(&ll);
    Liste l;
    initVide(&l);
    ll = ajouteDe(l, ll);
    return ll;
  } else{
    return ATPTL(n, permutation(n-1));
  }
}

/****************************/
/*  EliminePositionsPaires  */
/****************************/
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

/****************************/
/*          Begaye          */
/****************************/
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


/****************************/
/*    MaxZerosConsecutifs   */
/****************************/
/*--------Première version--------*/
/*        Version itérative       */
/*--------------------------------*/
int MaxZerosConsecutifs_ite(Liste l){
	int count = 0;
	int max = 0;
	if (estVide(l)) return count;
	while(! estVide(l)){
		if(premier(l) == 0) {
			count++; //Le compteur augmente de un (1) si la liste contient un zero
			if(count > max) max = count; //max prend le plus grand nombre de zero consécutif trouvé
		}else{
			count = 0; //Le compteur est remis à zéro lorsque l'on rencontre un autre chiffre que zero dans la liste
		}
		l = suite(l);
	}
	return max;
}

/*-----------------Deuxième Version-----------------*/
/*                 Version récursive                */
/*    Avec sous fonction et deux arguments en in.   */
/*--------------------------------------------------*/
int MaxZerosConsecutifs_rec(Liste l){
	int Aux (Liste l, int count, int max){
		if(estVide(l)) return max;
		else{
			if(premier(l) == 0) {
        count = count + 1;
				if(count > max) max = count;
				Aux(suite(l), count, max);
			}else{
				Aux(suite(l), 0, max);
			}
		}
	}
	Aux (l,0,0);
}

/*----------------Troisième Version-----------------*/
/*                 Version récursive                */
/*    Avec sous fonction et deux arguments en out.  */
/*--------------------------------------------------*/
int MaxZerosConsecutifs_out(Liste l){
	int max;
	int count;
	void Aux (Liste l, int *count, int *max){
		*max = 0;
		*count = 0;
		if(!estVide(l)) {
			Aux(suite(l),count,max);
			if(premier(l) == 0) {
				*count += 1;

			}else{
				*count = 0;
			}
      if(*count > *max) *max = *count;
		}
	}
	Aux (l, &count, &max);
	return max;
}


/****************************/
/*       EstPalindrome      */
/****************************/
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

/****************************/
/*      SommeAvantApres     */
/****************************/
bool SommeAvantApres(Liste l){
  int apres;
  bool res;
  void Aux(Liste l, int avant, int *apres, bool *res){
    if (estVide(l)){
      *res = FALSE;
      *apres = 0;
    }else{
      Aux(suite(l), (avant + premier(l)), apres, res);
      *res = *res || (avant == *apres);
      *apres = *apres + premier(l);
    }
  }
  Aux(l, 0, &apres, &res);
  return res;
}

/*************************************************/
/*                                               */
/*            TESTS                              */
/*                                               */
/*************************************************/

void Test_DebutDeuxIdentiques(Liste l){

    printf("Test de la fonction DebutDeuxIdentiques \n");
    empile(2, &l) ;
    empile(5, &l) ;
    empile(5, &l) ;
    affiche_rec(l);
    if ( DebutDeuxIdentiques(l)) printf("Vrai \n"); else printf("Faux \n");
    VideListe(&l);
    printf("Test de la fonction DebutDeuxIdentiques sur un singleton\n");
    empile(2, &l) ;
    //empile(5, &l) ;
    //empile(5, &l) ;
    affiche_rec(l);
    if ( DebutDeuxIdentiques(l)) printf("Vrai \n"); else printf("Faux \n");
    VideListe(&l);

}

void Test_QueDesZeros(Liste l){

    printf("\nTest de la fonction QueDesZeros \n");
    empile(0, &l) ;
    empile(0, &l) ;
    empile(0, &l) ;
    empile(0, &l) ;
    empile(0, &l) ;
    affiche_rec(l);
    if ( QueDesZeros(l)) printf("Vrai\n"); else printf("Faux \n");
    VideListe(&l);

}

void Test_SousEnsemble(Liste l, Liste m){

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

}

void Test_EliminePositionsPaires(Liste l){

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

}

void Test_Begaye(Liste l){

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

}

void Test_MaxZerosConsecutifs(Liste l, Liste m){

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

}

void Test_EstPalindrome(Liste l){

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

}

void Test_SommeAvantApres(Liste l){

    printf("\nTests de la fonction SommeAvantApres \n" );
    empile(7, &l) ;
    empile(-2, &l) ;
    empile(4, &l) ;
    empile(0, &l) ;
    empile(3, &l) ;
    empile(2, &l) ;
    printf("Liste l : \n");
    affiche_rec(l);
    if ( SommeAvantApres(l)) printf("Vrai \n"); else printf("Faux\n");
    VideListe(&l);

}

/* Fonction de test trop longue, elle sera divisée en plusieur partie plus tard.
Pour l'instant, pour plus de visibilité il vaut mieux commenter les autre test
lorsqu'on fait appel à cette fonction.*/

void Test_Implementation(){
  printf("\nTests de la structure ListeDeListe \n" );
  ListeDeListe ll;
  initVideDe(&ll);
  printf("InitVideDe : ll est vide ? " );
  if (estVideDe(ll)) printf ("Vrai\n");
  else printf("Faux\n");

  Liste l ;
  initVide(&l);
  ll = ajouteDe(l, ll);
  printf("Ajoute une liste vide : ll est vide ? " );
  if (estVideDe(ll)) printf ("Vrai\n");
  else printf("Faux\n");
  empile(7, &l) ;
  empile(-2, &l) ;
  empile(4, &l) ;
  empile(1, &l) ;
  empile(3, &l) ;
  empile(2, &l) ;
  ll = ajouteDe(l, ll);
  empile(-8, &l) ;
  empile(3, &l) ;
  empile(2, &l) ;
  ll = ajouteDe(l, ll);
  printf("AjouteDe : ll est vide après ajout de l ? " );
  if (estVideDe(ll)) printf ("Vrai\n");
  else printf("Faux\n");

  printf("Affichage Liste de Liste : \n");
  afficheDe(ll);

  printf("PremierDe : Premier de ll : \n");
  affiche_rec(premierDe(ll));
}

void Test_Permutation(){

  printf("\nTests de la fonction Permutation \n" );
  Liste l ;
  initVide(&l);	
  ListeDeListe ll;
  initVideDe(&ll);
  empile(-2, &l) ;
  empile(4, &l) ;
  empile(1, &l) ;
  empile(3, &l) ;
  empile(2, &l) ;
  ll = ajouteDe(l, ll);
  empile(-8, &l) ;
  empile(3, &l) ;
  empile(2, &l) ;
  ll = ajouteDe(l, ll);

  printf("AETTL : ajoute 45 en tête de chaque liste de ll : \n");
  afficheDe(AETTL(45, ll));

  printf("ATP : Liste de l avec 0 ajouté à toutes les positions : \n");
  afficheDe(ATP(0, l));

  ListeDeListe mm;
  initVideDe(&mm);

  Liste m ;
  initVide(&m);
  empile(-8, &m) ;
  empile(3, &m) ;
  empile(2, &m) ;
  mm = ajouteDe(m, mm);
  VideListe(&m);
  empile(143, &m) ;
  empile(3, &m) ;
  empile(48, &m) ;
  empile(12, &m) ;
  empile(67, &m) ;
  empile(0, &m) ;
  mm = ajouteDe(m, mm);
  printf("Liste de Liste mm :\n");
  afficheDe(mm);

  printf("Concatene : Concatène les listes de listes ll et mm: \n");
  afficheDe(concatene(ll, mm));

  printf("ATPTL : ajoute 3 à toutes les positions de toutes les listes de mm\n");
  afficheDe(ATPTL(3, mm));

  printf("Permutations : \n");
  afficheDe(permutation(3)); //segfaukt à partir de 9.

  ll = suiteDe(ll);
  printf("SuiteDe : ll est vide après retrait de l ? " );
  if (estVideDe(ll)) printf ("Vrai\n");
  else printf("Faux\n");

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

    Test_DebutDeuxIdentiques(l);

    Test_QueDesZeros(l);

    Test_SousEnsemble(l,m);

    /*Pour l'instant, pour plus de visibilité il vaut mieux commenter
    les autre test lorsqu'on fait appel à Test_Permutation et Test_Implementation.*/
    //Test_Permutation();
    //Test_Implementation();

    Test_EliminePositionsPaires(l);

    Test_Begaye(l);

    Test_MaxZerosConsecutifs(l,m);

    Test_EstPalindrome(l);

    Test_SommeAvantApres(l);


    return 0;
}
