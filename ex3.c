#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*************************************************/
/*                                               */
/*                sucre syntaxique               */
/*                                               */
/*************************************************/
#define ISNOT !=
#define NOT !
#define AND &&
#define OR ||
#define then
typedef enum { false, true } bool;

/*************************************************/
/*                                               */
/*          definition type image               */
/*                                               */
/*************************************************/
typedef struct bloc_image
        { bool toutnoir;
          struct bloc_image * fils[4];
        } bloc_image;
typedef bloc_image *image;


/*************************************************/
/*                                               */
/*          Fonction/Procédure exo3              */
/*                                               */
/*************************************************/

/*------------------ Constructions d'images -------------------------------*/

/********************/
/*  construit_blanc */
/********************/
image construit_blanc(){
  return NULL;
}

/********************/
/*  construit_noir  */
/********************/
image construit_noir(){
  image img = (image) malloc(sizeof(bloc_image));
  img->toutnoir = true;
  /*for(int i=0; i<4; i++){
    img->fils[i] = NULL;
  }*/
  return img;
}

/***********************/
/*  construit_composee */
/***********************/
image construit_composee(image i1, image i2, image i3, image i4){
  image img = (image) malloc(sizeof(bloc_image));
  img->toutnoir = false;
  img->fils[0] = i1;
  img->fils[1] = i2;
  img->fils[2] = i3;
  img->fils[3] = i4;
  return img;
}

/*------------------ Affichages d'images -------------------------------*/

/*********************/
/*  affichage normal */
/*********************/
void affiche_simple_aux(image img){
  if (img == NULL) printf("B");
  else if (img->toutnoir) printf("N");
  else{
    printf(".");
    for(int i=0; i<4; i++){
      affiche_simple_aux(img->fils[i]);
      printf(" ");
    }
  }
}
void affiche_simple(image img){
  affiche_simple_aux(img);
  printf("\n");
}


/*************************/
/*  affichage profondeur */
/*************************/
void affiche_profondeur_aux(image img, int p){
  if (img == NULL) printf("B%d", p);
  else{
    if (img->toutnoir) printf("N%d", p);
    else{
      printf(". %d", p);
      for(int i=0; i<4; i++){
        affiche_profondeur_aux(img->fils[i], p+1);
        printf(" ");
      }
    }
  }
}

void affiche_profondeur(image img){
  affiche_profondeur_aux(img, 0);
  printf("\n");
}


/*--------------------------------------------------------------*/

/*************************/
/*      est_blanche      */
/*************************/
bool est_blanche(image img){
  if (img == NULL) return true;
  else{
    if (img->toutnoir) return false;
    else{
      return (est_blanche(img->fils[0])
              && est_blanche(img->fils[1])
              && est_blanche(img->fils[2])
              && est_blanche(img->fils[3]));
    }
  }
}

/*************************/
/*       est_noire       */
/*************************/
bool est_noire(image img){
  if (img == NULL) return false;
  else{
    if (img->toutnoir) return true;
    else{
      return (est_noire(img->fils[0])
              && est_noire(img->fils[1])
              && est_noire(img->fils[2])
              && est_noire(img->fils[3]));
    }
  }
}

/*************************/
/*         copie         */
/*************************/
image Copie(image img){
	if (img == NULL) return construit_blanc();
	else if (img->toutnoir) return construit_noir();
	else return construit_composee( img->fils[0],
                                  img->fils[1],
                                  img->fils[2],
                                  img->fils[3]);
}

/*************************/
/*         aire          */
/*************************/
float aire(image img, float i){
  if (img == NULL) return 0;
  else if (img->toutnoir){
    return ((1/i) * (1/i));
  } else return aire(img->fils[0], i*2) +
                aire(img->fils[1], i*2) +
                aire(img->fils[2], i*2) +
                aire(img->fils[3], i*2);
}

/*************************/
/*      meme_dessin      */
/*************************/
bool meme_dessin(image i1, image i2){
  if((i1 == NULL)) {
    return est_blanche(i2);
} else if(i2 == NULL){
  return est_blanche(i1);
} else if (i1->toutnoir){
    return est_noire(i2);
  } else if(i2->toutnoir){
    return est_noire(i1);
  }
  else {
    return (meme_dessin(i1->fils[0],i2->fils[0]) &&
                meme_dessin(i1->fils[1],i2->fils[1]) &&
      		 			meme_dessin(i1->fils[2],i2->fils[2]) &&
                meme_dessin(i1->fils[3],i2->fils[3]));
  }
}

/*************************/
/*       Difference      */
/*************************/
image CopieNeg(image img){
	if (img == NULL) return construit_noir();
	else if (img->toutnoir) return construit_blanc();
	else return construit_composee(
    CopieNeg(img->fils[0]),
    CopieNeg(img->fils[1]),
    CopieNeg(img->fils[2]),
    CopieNeg(img->fils[3]));
}

image Difference(image i1, image i2){
	image res;
  if(i1 == NULL){
    res = Copie(i2);
  } else if (i2 == NULL) {
    res = Copie(i1);
  } else if (i1->toutnoir){
    res = CopieNeg(i2);
  } else if (i2->toutnoir){
    res = CopieNeg(i1);
  } else
  res = construit_composee( Difference(i1->fils[0],i2->fils[0]),
                            Difference(i1->fils[1],i2->fils[1]),
                            Difference(i1->fils[2],i2->fils[2]),
                            Difference(i1->fils[3],i2->fils[3]));
	return res;
}


/*************************/
/*      rendmemoire      */
/*************************/
void rendmemoire(image *img){
  if (! (*img == NULL) ){
      for (int i = 0; i < 4; ++i){
        rendmemoire(  &((*img)->fils)[i] );
      }
    free(*img);
    *img = NULL;
  }
}


/*************************/
/*        lecture        */
/*************************/
image lecture_aux(){
  char c;
  scanf(" %c", &c);
  if (c == 'B') return construit_blanc();
  else if (c == 'N') return construit_noir();
  else if(c == '.'){
    image i1 = lecture_aux();
    image i2 = lecture_aux();
    image i3 = lecture_aux();
    image i4 = lecture_aux();
    return construit_composee(i1, i2, i3, i4);
  }
  else printf("Entrée invalide, fin de la lecture clavier\n");
  exit(1);
}
image lecture(){
  printf("Lecture Clavier : entrez une image valide à l'aide des caractères '.', 'N' ou 'B' \n");
  return lecture_aux();
}

/*************************/
/*        négatif        */
/*************************/
void Negatif(image *img){
	if(*img == NULL){
    free(*img);
    *img = construit_noir();
  } else if( (*img)->toutnoir ) {
    free(*img);
    *img = construit_blanc();
  }
	else{
		for (int i = 0; i < 4; ++i)
			Negatif(&((*img)->fils[i]));
	}
}

/*************************************************/
/*                Créations d'images             */
/*            pour tester les fonctions et       */
/*             procédures (~ 150 lignes)         */
/*************************************************/

image nv_carre(){
   return construit_composee(
    construit_composee(
      construit_blanc(),
      construit_blanc(),
      construit_blanc(),
      construit_noir()
    ),
    construit_composee(
      construit_blanc(),
      construit_blanc(),
      construit_noir(),
      construit_blanc()
    ),
    construit_composee(
      construit_blanc(),
      construit_noir(),
      construit_blanc(),
      construit_blanc()
    ),
    construit_composee(
      construit_noir(),
      construit_blanc(),
      construit_blanc(),
      construit_blanc())
    );
}

image nv_carre2(){
  image *img;
  *img = construit_composee(
    construit_composee(
      construit_blanc(),
      construit_blanc(),
      construit_blanc(),
      construit_noir()
    ),
    construit_composee(
      construit_blanc(),
      construit_blanc(),
      construit_noir(),
      construit_blanc()
    ),
    construit_composee(
      construit_blanc(),
      construit_noir(),
      construit_blanc(),
      construit_blanc()
    ),
    construit_composee(
      construit_noir(),
      construit_blanc(),
      construit_blanc(),
      construit_blanc()
    )
  );
  Negatif(img);
  return *img;
}

image nv_damier(){
  return construit_composee(
    construit_noir(),
    construit_blanc(),
    construit_noir(),
    construit_blanc()
  );
}

image nv_pif(){
  return construit_composee(
      construit_noir(),
      construit_composee(
            construit_blanc(),
            construit_blanc(),
            construit_noir(),
            construit_blanc()
      ),
      construit_blanc(),
      construit_composee(
            construit_noir(),
            construit_composee(
                    construit_noir(),
                    construit_noir(),
                    construit_blanc(),
                    construit_composee(
                            construit_noir(),
                            construit_blanc(),
                            construit_noir(),
                            construit_noir())
                    ),
            construit_blanc(),
            construit_noir()
          )
  );
}

image nv_pif_blanche(){
  return construit_composee(
      construit_blanc(),
      construit_composee(
            construit_blanc(),
            construit_blanc(),
            construit_blanc(),
            construit_blanc()
      ),
      construit_blanc(),
      construit_composee(
            construit_blanc(),
            construit_composee(
                    construit_blanc(),
                    construit_blanc(),
                    construit_blanc(),
                    construit_composee(
                            construit_blanc(),
                            construit_blanc(),
                            construit_blanc(),
                            construit_blanc())
                    ),
            construit_blanc(),
            construit_blanc()
          )
  );
}

image nv_pif_noire(){
  return construit_composee(
      construit_noir(),
      construit_composee(
            construit_noir(),
            construit_noir(),
            construit_noir(),
            construit_noir()
      ),
      construit_noir(),
      construit_composee(
            construit_noir(),
            construit_composee(
                    construit_noir(),
                    construit_noir(),
                    construit_noir(),
                    construit_composee(
                            construit_noir(),
                            construit_noir(),
                            construit_noir(),
                            construit_noir())
                    ),
            construit_noir(),
            construit_noir()
          )
  );
}

/*************************************************/
/*                                               */
/*           Main                                */
/*                                               */
/*************************************************/
int main(int argc, char const *argv[]) {
  image damier = nv_damier();
  image carre = nv_carre();
  image carre2 = nv_carre2();
  image pif = nv_pif();
  image pif_blanche = nv_pif_blanche();
  image pif_noire = nv_pif_noire();
  image simple_noire = construit_noir();
  image simple_blanche = construit_blanc();

  printf("Damier : ");
  affiche_simple(damier);

  printf("Carré noir : ");
  affiche_simple(carre);

  printf("Profondeur : \n");
  affiche_profondeur(pif);

  printf("\nTest est_blanche et est_noire : \n");
  affiche_simple(pif_blanche);
  printf("est_blanche ? ");
  if (est_blanche(pif_blanche)) printf("Vrai\n");
  else printf("Faux\n");

  affiche_simple(pif_noire);
  printf("est_noire ? ");
  if (est_noire(construit_noir())) printf("Vrai\n");
  else printf("Faux\n");
  if (est_noire(pif_noire)) printf("Vrai\n");
  else printf("Faux\n");



  printf("\nTest Copie : \n");
  printf("Pif\n");
  affiche_simple(pif);
  printf("En voici sa copie : \n");
  affiche_simple(Copie(pif));
  printf("Simple Noire\n");
  affiche_simple(simple_noire);
  printf("En voici sa copie : \n");
  affiche_simple(Copie(simple_noire));

  printf("\n\nTest aire : %f\n", aire(lecture(), 1));


  printf("\nTest Meme dessin : \n");
  if (meme_dessin(lecture(),lecture())) printf("Vrai\n");
  else printf("Faux\n");
  if (meme_dessin(lecture(),lecture())) printf("Vrai\n");
  else printf("Faux\n");
  if (meme_dessin(lecture(),lecture())) printf("Vrai\n");
  else printf("Faux\n");
  if (meme_dessin(lecture(),lecture())) printf("Vrai\n");
  else printf("Faux\n");
  printf("Carre et carre : ");
  if (meme_dessin(carre,carre)) printf("Vrai\n");
  else printf("Faux\n");
  printf("Carre et damnier : ");
  if (meme_dessin(carre,damier)) printf("Vrai\n");
  else printf("Faux\n");
  printf("pif noire et pif blanche : ");
  if (meme_dessin(pif_noire, pif_blanche)) printf("Vrai\n");
  else printf("Faux\n");
  printf("pif noire et pif noire : ");
  if (meme_dessin(pif_noire, pif_noire)) printf("Vrai\n");
  else printf("Faux\n");
  printf("pif noire et simple noire : ");
  if (meme_dessin(pif_noire, simple_noire)) printf("Vrai\n");
  else printf("Faux\n");
  printf("pif blanche et simple blanche : ");
  if (meme_dessin(pif_blanche, simple_blanche)) printf("Vrai\n");
  else printf("Faux\n");

  /* Résultats pas toujours convaincants*/

  printf("\nDifference : ");
  printf("Noire et damnier : ");
  affiche_simple(Difference(simple_noire,damier));
  printf("Damier et Noire : ");
  affiche_simple(Difference(damier, simple_noire));
  printf("Blanche et damnier : ");
  affiche_simple(Difference(simple_blanche,damier));
  printf("Damier et Blanche : ");
  affiche_simple(Difference(damier, simple_blanche));
  printf("Carre et damnier : ");
  affiche_simple(Difference(carre,damier));
  printf("Carre et carre2 : ");
  affiche_simple(Difference(carre,carre2));
  printf("Carre et carre : ");
  affiche_simple(Difference(carre, carre));
  printf("pif et simple noire : ");
  affiche_simple(Difference(pif, simple_noire));
  printf("pif noire et simple noire : ");
  affiche_simple(Difference(pif_noire, simple_noire));
  printf("pif noire et pif blanche : ");
  affiche_simple(Difference(pif_noire, pif_blanche));


  /*printf("Test Lecture Clavier : \n");
  image lue = lecture();
  printf("Voici l'image lue : \n");
  affiche_simple(lue);
  affiche_profondeur(lue);*/

  printf("Negatif avant : ");
  affiche_simple(carre);
  printf("Negatif apres : ");
  Negatif(&carre);
  affiche_simple(carre);

  /* ne fonctionne pas. */
  printf("Rend mémoire : \n" );
  //printf("Simple Noire : \n" );
rendmemoire(&simple_noire);
  //printf("Simple blanche : \n" );
rendmemoire(&simple_blanche);
  //printf("Pif : \n" );
  rendmemoire(&pif);
    //printf("Damier : \n" );
    //affiche_simple(damier);
  rendmemoire(&damier);
  //affiche_simple(damier);
    //printf("Carré : \n" );
    //affiche_simple(carre);
  rendmemoire(&carre);
  //affiche_simple(carre);
    //printf("Carré 2 : \n" );
  rendmemoire(&carre2);
    //printf("PifBlanche : \n" );
  rendmemoire(&pif_blanche);
    //printf("Pif Noire : \n" );
  rendmemoire(&pif_noire);

  //printf("Affichage rend mémoire : \n" );
  //affiche_simple(pif);

}
