#include <stdlib.h>
#include <stdio.h>
#include "matrix_LDS.h"

int main() {
  matrix *m1 = matrix_empty();
  matrix *m2 = matrix_empty();
  add_element(m1, 0, 0, 2);
  add_element(m1, 1, 0, 2);
  add_element(m1, 0, 1, 2);
  add_element(m2, 0, 0, 2);
  add_element(m2, 1, 0, 2);
  add_element(m2, 0, 1, 2);
  printf("Matrice 1 après l'ajout de quelques elements :\n");
  print_matrix(m1);
  printf("Matrice 1 après la modification de de l'élément a l'indice 0,0 :\n");
  modification(m1, 0, 0, 4);
  print_matrix(m1);
  printf("Matrice 2 après l'ajout de quelques elements :\n");
  print_matrix(m2);
  suppression(m2, 0, 1);
  printf("Matrice 2 après la suppression de de l'élément a l'indice 0,1 :\n");
  print_matrix(m2);
  int **t1;
  t1 = malloc(2 * sizeof(int *));
  for (size_t i = 0; i < 2; i++) {
    t1[i] = malloc(2 * sizeof(int));
  }
  t1[0][0] = 1;
  t1[0][1] = 2;
  t1[1][0] = 3;
  t1[1][1] = 4;
  printf("Conversion dans le sens matrice dense vers matrice creuse :\n");
  matrix *m3 = to_sparse_matrix(t1, 2, 2);
  print_matrix(m3);
  for (size_t i = 0; i < 2; i++) {
    free(t1[i]);
  }
  free(t1);
  printf("Conversion dans le sens matrice creuse vers matrice dense :\n");
  int **t2 = to_dense_matrix(m3);
  for(size_t k = 0; k < 2; ++k){
    for(size_t j = 0; j < 2; ++j){
      printf("%d\t", t2[k][j]);
    }
    printf("\n");
  }
  printf("\n");
  for (size_t i = 0; i < 2; i++) {
    free(t2[i]);
  }
  free(t2);
  printf("Matrice résultat de M1 x M2\n");
  matrix *m4 = mult_mat(m1, m2);
  print_matrix(m4);
  printf("Dimension de la matrice M1\n");
  print_dim(m1);
  printf("Dimension de la matrice M2\n");
  print_dim(m2);
  printf("Dimension de la matrice resultat de M1 x M2\n");
  print_dim(m4);;
  matrix_dispose(&m1);
  matrix_dispose(&m2);
  matrix_dispose(&m3);
  matrix_dispose(&m4);
  return EXIT_SUCCESS;
}
