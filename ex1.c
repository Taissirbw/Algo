#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ISNOT !=
#define NOT !
#define AND &&
#define OR ||
#define then
typedef enum { false, true } bool;


/* Fonction récursive terminale calculant la valeur de n!,
pour n supérieur ou égal à 0.
L'accumulateur acc doit être initialisé à 1 lors de l'appel de la fonction. */
double factorielle(double n, double acc){
  if (n==0) return acc;
  else return factorielle(n-1, n * acc);
}

/* Fonction récursive terminale calculant une approximation de e.
(k étant le nombre d'itérations du calcul).
L'accumulateur acc doit être initialisé à 1 lors de l'appel de fonction. */
double calc_e(double k, double acc){
  if (k == 0) return acc;
  else return calc_e(k - 1, acc + 1/(factorielle(k, 1)));
}

/* Fonction récursive terminale élevant x à la puissance n
(n étant un entier positif ou null).
L'accumulateur acc doit être initialisé à 0 lors de l'appel de fonction*/
double puissance(double x, double n, double acc){
  if (n == 0) return acc;
  else return puissance(x, n-1, x*acc);
}


void main(int argc, char const *argv[]) {

  printf("Fact : %f\n", factorielle(2, 1)); //test de la fonction factorielle
  printf("e : %f\n", calc_e(5, 1)); //test de la fonction calc_e
  //Calcul de e avec la fonction puissance
  int k = 5;
  for (int i = 0; i < k; i++){
  printf("(1 + 10^%d)^10^%d : %f\n", -i, i,
        puissance((1 + 1/puissance(10, i, 1)), puissance(10, i, 1), 1)) ;
  }
  return 0;
}
