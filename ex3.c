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

bool meme_dessin(image i1, image i2){
  if(! (i1 == NULL)){
    if (i1->toutnoir) return est_noire(i2); //On teste si les deux images sont noires
    else return (meme_dessin(i1->fils[0],i2->fils[0]) &&
                meme_dessin(i1->fils[1],i2->fils[1]) &&
      		meme_dessin(i1->fils[2],i2->fils[2]) &&
                meme_dessin(i1->fils[3],i2->fils[3])); //Appel récursif sur les fils
  } else {
    return est_blanche(i2); //On teste si les deux images sont blanches
  }
}

image Difference(image i1, image i2){
	image res;
	
	//Cas où les images sont de meme couleurs :
	if(est_noire(i1) && est_noire(i2)) 
		res = construit_blanc();
	else if (est_blanche(i1) && est_blanche(i2))
		res = construit_blanc();
	
	//Cas où les images sont de couleurs différentes
	else if(est_blanche(i1) && est_noire(i2))
		res = construit_noir();
	else if (est_noire(i1) && est_blanche(i2))
		res = construit_noir();
	
	//Cas où les images n'ont pas la meme profondeur
 	 else if(i1==NULL && !(i2==NULL)) res = construit_noir();
  	else if (!(i1==NULL) && i2==NULL) res = construit_noir();
	
	else{
		res = construit_composee(Difference(i1->fils[0],i2->fils[0]),Difference(i1->fils[1],i2->fils[1]),
		 			Difference(i1->fils[2],i2->fils[2]),Difference(i1->fils[3],i2->fils[3]));
	}
	return res;
}

void rendmemoire(image *img){
  if (! ((*img) == NULL) ){
    printf("Image non nulle\n");
    if (! (*img)->toutnoir == true){
      printf("Image non toute noire\n");
      for (int i = 0; i < 4; ++i){
        printf("rendmemoire fils %d\n", i);
        rendmemoire(&((*img)->fils[i]));
      }
    }
    printf("fin de l'itération\n");
  }
  free(img);
}

image lecture(){
  image Aux(){
    char c;
    scanf(" %c", &c);
    if(c == '.'){
      image i1 = Aux();
      image i2 = Aux();
      image i3 = Aux();
      image i4 = Aux();
      return construit_composee(i1, i2, i3, i4);
    } else if (c == 'N') return construit_noir();
    else if (c == 'B') return construit_blanc();
    else printf("Entrée invalide, fin de la lecture clavier\n");
    exit(1);
  }
  printf("Lecture Clavier : entrez une image valide à l'aide des caractères '.', 'N' ou 'B' \n");
  return Aux();
}

void Negatif(image *img){
	
	if(est_noire(*img)) *img = construit_blanc(); //Inverse en blanc
	else if(est_blanche(*img)) *img = construit_noir(); //Inverse en noir
	else{
		for (int i = 0; i < 4; ++i)
			Negatif(&((*img)->fils[i])); //Appel récursif sur les fils
	}
}

/*************************************************/
/*                Créations d'images             */
/*            pour tester les fonctions et       */
/*                   procédures                  */
/*************************************************/

void nv_carre(image *img){
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
      construit_blanc())
    );
}

void nv_carre2(image *img){
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
}

void nv_damier(image *img){
  *img = construit_composee(
    construit_noir(),
    construit_blanc(),
    construit_noir(),
    construit_blanc()
  );
}

void nv_pif(image *img){
  *img = construit_composee(
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

void nv_pif_blanche(image *img){
  *img = construit_composee(
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

void nv_pif_noire(image *img){
  *img = construit_composee(
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
void main(int argc, char const *argv[]) {
  image damier;
  nv_damier(&damier);
  image carre;
  nv_carre(&carre);
  image carre2;
  nv_carre2(&carre2);
  image pif;
  nv_pif(&pif);
  image pif_blanche;
  nv_pif_blanche(&pif_blanche);
  image pif_noire;
  nv_pif_noire(&pif_noire);


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
  if (est_noire(pif_noire)) printf("Vrai\n");
  else printf("Faux\n");

  //rendmemoire(&pif);

  printf("\nTest Copie : \n");
  affiche_simple(pif);
  affiche_simple(Copie(pif));

  printf("\nTest Meme dessin : \n");
  printf("Carre et carre : ");
  if (meme_dessin(carre,carre)) printf("Vrai\n");
  else printf("Faux\n");
  printf("Carre et damier : ");
  if (meme_dessin(carre,damier)) printf("Vrai\n");
  else printf("Faux\n");
  printf("pif noire et pif blanche : ");
  if (meme_dessin(pif_noire, pif_blanche)) printf("Vrai\n");
  else printf("Faux\n");
  printf("pif noire et pif noire : ");
  if (meme_dessin(pif_noire, pif_noire)) printf("Vrai\n");
  else printf("Faux\n");

  printf("\nDifference : ");
  affiche_simple(Difference(carre,damier));
  affiche_simple(Difference(carre,carre2));
  affiche_simple(Difference(carre, carre));
  affiche_simple(Difference(pif, construit_noir())); //resultat chelou
  affiche_simple(Difference(pif_noire, construit_noir()));
  affiche_simple(Difference(pif_noire, pif_blanche));

  printf("Test Lecture Clavier : \n");
  image lue = lecture();
  printf("Voici l'image lue : \n");
  affiche_simple(lue);
  affiche_profondeur(lue);

  printf("Negatif avant : ");
  affiche_simple(carre);
  printf("Negatif apres : ");
  Negatif(&carre);
  affiche_simple(carre);

}
