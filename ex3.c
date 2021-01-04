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

image construit_blanc(){
  //image img = (image) malloc(sizeof(bloc_image));
  image img = NULL;
  return img;
}

image construit_noir(){
  image img = (image) malloc(sizeof(bloc_image));
  img->toutnoir = true;
  for(int i=0; i<4; i++){
    img->fils[i] = NULL;
  }
  return img;
}

image construit_composee(image i1, image i2, image i3, image i4){
  image img = (image) malloc(sizeof(bloc_image));
  img->toutnoir = false;
  img->fils[0] = i1;
  img->fils[1] = i2;
  img->fils[2] = i3;
  img->fils[3] = i4;
}

/*------------------ Affichages d'images -------------------------------*/

void affiche_simple(image img){
  void Aux(image img){
    if (img == NULL) printf("B");
    else{
      if (img->toutnoir == true) printf("N");
      else{
        printf(".");
        for(int i=0; i<4; i++){
          Aux(img->fils[i]);
          printf(" ");
        }
      }
    }
  }
  Aux(img);
  printf("\n");
}

void affiche_profondeur(image img){
  void Aux(image img, int p){
    if (img == NULL) printf("B%d", p);
    else{
      if (img->toutnoir == true) printf("N%d", p);
      else{
        printf(". %d", p);
        for(int i=0; i<4; i++){
          Aux(img->fils[i], p+1);
          printf(" ");
        }
      }
    }
  }
  Aux(img, 0);
  printf("\n");
}

/*--------------------------------------------------------------*/

bool est_blanche(image img){
  if (img == NULL) return true;
  else{
    if (img->toutnoir == true) return false;
    else{
      return (est_blanche(img->fils[0]) && est_blanche(img->fils[1])
              && est_blanche(img->fils[2]) && est_blanche(img->fils[3]));
    }
  }
}

bool est_noire(image img){
  if (img == NULL) return false;
  else{
    if (img->toutnoir == true) return true;
    else{
      return (est_noire(img->fils[0]) && est_noire(img->fils[1])
              && est_noire(img->fils[2]) && est_noire(img->fils[3]));
    }
  }
}

image Copie(image img){
	if (img == NULL) return construit_composee(construit_blanc(),construit_blanc(),
						   construit_blanc(),construit_blanc());
	else if (img->toutnoir) return construit_composee(construit_noir(),construit_noir(),
								  construit_noir(),construit_noir());
	else return construit_composee(img->fils[0],img->fils[1],img->fils[2],img->fils[3]);
}

/*
void rendmemoire(image *img){
  if (! (*img == NULL) ){
    //free(&(*img)->toutnoir);
    for (int i = 0; i < 4; ++i){
      rendmemoire(&((*img)->fils[i]));
    }
    free(img);
  }
}
*/

/*image Difference(image i1, image i2){
	image res;

	if(est_noire(i1) && est_noire(i2)) 
		res = construit_blanc();
	else if (est_blanche(i1) && est_blanche(i2))
		res = construit_blanc();
	else if(est_blanche(i1) && est_noire(i2)) 
		res = construit_noir();
	else if (est_noire(i1) && est_blanche(i2))
		res = construit_noir();
	else{ 
		if(i1!=NULL && i2!= NULL){
			res = construit_composee(Difference(i1->fils[0],i2->fils[0]),Difference(i1->fils[1],i2->fils[1]),
		 				Difference(i1->fils[2],i2->fils[2]),Difference(i1->fils[3],i2->fils[3]));
		}
	}
	return res;
}*/

void Negatif(image *img){
	if(est_noire(*img)) *img = construit_blanc();
	else if(est_blanche(*img)) *img = construit_noir();
	else{
		for (int i = 0; i < 4; ++i)
			Negatif(&((*img)->fils[i]));
	}
}

/*************************************************/
/*                Créations d'images             */
/*            pour tester les fonctions et       */
/*                   procédures                  */
/*************************************************/

void nv_carre(image *img){
  *img = construit_composee(construit_composee(construit_blanc(),
                  construit_blanc(), construit_blanc(), construit_noir()),
                construit_composee(construit_blanc(), construit_blanc(),
                                  construit_noir(), construit_blanc()),
                construit_composee(construit_blanc(), construit_noir(),
                                  construit_blanc(), construit_blanc()),
                construit_composee(construit_noir(), construit_blanc(),
                              construit_blanc(), construit_blanc()));
}

void nv_damnier(image *img){
  *img = construit_composee(construit_noir(), construit_blanc(),
                construit_noir(), construit_blanc());
}

void nv_pif(image *img){
  *img = construit_composee(construit_noir(),
      construit_composee(construit_blanc(), construit_blanc(),
      construit_noir(), construit_blanc()),
      construit_blanc(),
          construit_composee(construit_noir(),
              construit_composee(construit_noir(), construit_noir(), construit_blanc(),
                  construit_composee(construit_noir(), construit_blanc(), construit_noir(),
                                      construit_noir())),
                  construit_blanc(), construit_noir()));
}

void nv_pif_blanche(image *img){
  *img = construit_composee(construit_blanc(),
      construit_composee(construit_blanc(), construit_blanc(),
      construit_blanc(), construit_blanc()),
      construit_blanc(),
          construit_composee(construit_blanc(),
              construit_composee(construit_blanc(), construit_blanc(), construit_blanc(),
                  construit_composee(construit_blanc(), construit_blanc(), construit_blanc(),
                                      construit_blanc())),
                  construit_blanc(), construit_blanc()));
}

void nv_pif_noire(image *img){
  construit_composee(construit_noir(),
      construit_composee(construit_noir(), construit_noir(),
      construit_noir(), construit_noir()),
      construit_noir(),
          construit_composee(construit_noir(),
              construit_composee(construit_noir(), construit_noir(), construit_noir(),
                  construit_composee(construit_noir(), construit_noir(), construit_noir(),
                                      construit_noir())),
                  construit_noir(), construit_noir()));
}

/*************************************************/
/*                                               */
/*           Main                                */
/*                                               */
/*************************************************/
void main(int argc, char const *argv[]) {
  image damnier;
  nv_damnier(&damnier);
  image carre;
  nv_carre(&carre);
  image pif;
  nv_pif(&pif);
  image pif_blanche;
  nv_pif_blanche(&pif_blanche);
  image pif_noire;
  nv_pif_noire(&pif_noire);

  printf("Damnier : ");
  affiche_simple(damnier);

  printf("Carré noir : ");
  affiche_simple(carre);

  printf("Profondeur : ");
  affiche_profondeur(pif);

  affiche_simple(pif_blanche);
  printf("est_blanche ? ");
  if (est_blanche(pif_blanche)) printf("Vrai\n");
  else printf("Faux\n");

  affiche_simple(pif_noire);
  printf("est_noire ? ");
  if (est_noire(pif_noire)) printf("Vrai\n");
  else printf("Faux\n");

  //rendmemoire(&pif);

  printf("Copie : \n");
  affiche_simple(pif);
  affiche_simple(Copie(pif));
	
  affiche_simple(Difference(carre,carre));

  printf("Negatif avant : ");
  affiche_simple(carre);
  printf("Negatif apres : ");
  Negatif(&carre);
  affiche_simple(carre);

}
