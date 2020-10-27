#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ISNOT !=
#define NOT !
#define AND &&
#define OR ||
#define then
typedef enum { false, true } bool;


/*Fonction récursive terminale calculant la valeur de n!, pour n supérieur ou égal à 0.
L'accumulateur acc doit être initialisé à 1 lors de l'appel de la fonction.*/
double factorielle(double n, double acc){
  if (n==0) return acc;
  else return factorielle(n-1, n * acc);
}

/*Fonction récursive terminale calculant */
double calc_e(double k, double acc){
  if (k == 0) return acc;
  else return calc_e(k - 1, acc + 1/(factorielle(k, 1)));
}


void main(int argc, char const *argv[]) {
  /* code */
  printf("Fact : %f\n", factorielle(2, 1));
  printf("e : %f\n", calc_e(10, 1));
  return 0;
}
