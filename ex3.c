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

image construit_blanc(){
  image img = (image) malloc(sizeof(bloc_image));
  img = NULL;
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

void affiche_simple(image img){
  if (img == NULL) printf("B");
  else{
    if (img->toutnoir == true) printf("N");
    else{
      printf(".");
      for(int i=0; i<4; i++){
        affiche_simple(img->fils[i]);
        printf(" ");
      }
    }
  }
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
}

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
	else if (img->toutnoir == true) return construit_composee(construit_noir(),construit_noir(),
								  construit_noir(),construit_noir());
	else return construit_composee(img->fils[0],img->fils[1],img->fils[2],img->fils[3]);
}

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
        
  printf("Copie : ");
  affiche_simple(Copie(carre));

  printf("\nDamnier : ");
  affiche_simple(damnier);

  printf("\nCarré noir : ");
  affiche_simple(carre);

  printf("\nProfondeur : ");
  affiche_profondeur(pif);
  printf("\n");

  affiche_simple(pif_blanche);
  printf("\nest_blanche ? ");
  if (est_blanche(pif_blanche)) printf("Vrai\n");
  else printf("Faux\n");

  affiche_simple(pif_noire);
  printf("\nest_noire ? ");
  if (est_noire(pif_noire)) printf("Vrai\n");
  else printf("Faux\n");

  printf("\n");
}
