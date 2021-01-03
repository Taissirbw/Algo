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
        printf(".%d", p);
        for(int i=0; i<4; i++){
          Aux(img->fils[i], p+1);
          printf(" ");
        }
      }
    }
  }
  Aux(img, 0);
}


/*************************************************/
/*                                               */
/*           Main                                */
/*                                               */
/*************************************************/
void main(int argc, char const *argv[]) {
  construit_blanc();
  construit_noir();
  printf("Damnier : ");
  affiche_simple(construit_composee(construit_noir(), construit_blanc(),
                construit_noir(), construit_blanc()));
  printf("\nCarré noir : ");
  affiche_simple(construit_composee(construit_composee(construit_blanc(),
                  construit_blanc(), construit_blanc(), construit_noir()),
                construit_composee(construit_blanc(), construit_blanc(),
                                  construit_noir(), construit_blanc()),
                construit_composee(construit_blanc(), construit_noir(),
                                  construit_blanc(), construit_blanc()),
                construit_composee(construit_noir(), construit_blanc(),
                              construit_blanc(), construit_blanc())));

  printf("\nProfondeur : ");
  affiche_profondeur(
    construit_composee(construit_noir(),
        construit_composee(construit_blanc(), construit_blanc(),
        construit_noir(), construit_blanc()),
        construit_blanc(),
            construit_composee(construit_noir(),
                construit_composee(construit_noir(), construit_noir(), construit_blanc(),
                    construit_composee(construit_noir(), construit_blanc(), construit_noir(),
                                        construit_noir())),
                    construit_blanc(), construit_noir())));
  printf("\n");
}
