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
(n étant un entier positif ou null).*/
double puissance(double x, int n){
  if (n == 0) return 1;
  else {
    double y = puissance(x, n/2);
    if ((n%2) == 0) return y * y;
    else return y * y * x;
  }
}

/* Première version de la fonction d'Ackermann avec de l'itératif et du récursif */
int Ackermann(int m, int n){ 
  int res;
  if (m==0) return n+1;
  else{
      res = 1;
      for (int i = 0; i < n+1; ++i)
            res = Ackermann(m-1,res);
      return res; 
  }
}

/* Deuxième version de la fonction d'Ackermann purement récursif */
int Ackermann_rec(int m, int n){ 
  if (m== 0) return n+1;
  else if (n == 0) return Ackermann(m-1,1);
  else return Ackermann(m-1, Ackermann(m,n-1));
}


void main(int argc, char const *argv[]) {

  printf("Fact : %f\n", factorielle(2, 1)); //test de la fonction factorielle
  printf("e : %f\n", calc_e(5, 1)); //test de la fonction calc_e
  //Calcul de e avec la fonction puissance
  int k = 5;
  for (int i = 0; i < k; i++){
  printf("(1 + 10^%d)^10^%d : %f\n", -i, i,
        puissance((1 + 1/puissance(10, i)), puissance(10, i))) ;
  }
  
  printf("Ackermann de 1 et 14 : %d\n", Ackermann(1, 14)); 
  printf("Ackermann recursif de 1 et 14 : %d\n", Ackermann(1, 14));
  //return 0;
}
