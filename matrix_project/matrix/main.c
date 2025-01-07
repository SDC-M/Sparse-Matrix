#include <stdlib.h>
#include <stdio.h>
#include "matrix_LDS.h"

int main() {
  matrix *m1 = matrix_empty();
  if (m1 == nullptr) {
    goto error0;
  }
  matrix *m2 = matrix_empty();
  if (m2 == nullptr) {
    matrix_dispose(&m1);
    goto error0;
  }
  if (add_element(m1, 0, 0, 2) == nullptr) {
    goto error1;
  }
  if (add_element(m1, 1, 0, 2) == nullptr) {
    goto error1;
  }
  if (add_element(m1, 0, 1, 2) == nullptr) {
    goto error1;
  }
  if (add_element(m2, 0, 0, 2) == nullptr) {
    goto error1;
  }
  if (add_element(m2, 1, 0, 2) == nullptr) {
    goto error1;
  }
  if (add_element(m2, 0, 1, 2) == nullptr) {
    goto error1;
  }
  printf("Matrice 1 après l'ajout de quelques elements :\n");
  print_matrix(m1);
  printf("Matrice 1 après la modification de de l'élément a l'indice 0,0 :\n");
  if (modification(m1, 0, 0, 4) == EOF) {
    goto error1;
  }
  print_matrix(m1);
  printf("Matrice 2 après l'ajout de quelques elements :\n");
  print_matrix(m2);
  if (delete_element(m2, 0, 1) == EOF) {
    goto error1;
  }
  printf("Matrice 2 après la suppression de de l'élément a l'indice 0,1 :\n");
  print_matrix(m2);
  int **t1;
  t1 = malloc(2 * sizeof(int *));
  if (t1 == nullptr) {
    goto error1;
  }
  for (size_t i = 0; i < 2; i++) {
    t1[i] = malloc(2 * sizeof(int));
  }
  t1[0][0] = 1;
  t1[0][1] = 2;
  t1[1][0] = 3;
  t1[1][1] = 4;
  printf("Conversion dans le sens matrice dense vers matrice creuse :\n");
  matrix *m3 = to_sparse_matrix(t1, 2, 2);
  if (m3 == nullptr) {
    goto error2;
  }
  print_matrix(m3);
  for (size_t i = 0; i < 2; i++) {
    free(t1[i]);
  }
  free(t1);
  printf("Conversion dans le sens matrice creuse vers matrice dense :\n");
  int **t2 = to_dense_matrix(m3);
  if (t2 == nullptr) {
    matrix_dispose(&m3);
    goto error2;
  }
  for (size_t k = 0; k < 2; ++k) {
    for (size_t j = 0; j < 2; ++j) {
      printf("%d\t", t2[k][j]);
    }
    printf("\n");
  }
  printf("\n");
  for (size_t i = 0; i < 2; i++) {
    free(t2[i]);
  }
  free(t2);
  printf("Matrice résultat de M1 x M2 :\n");
  matrix *m4 = mult_mat(m1, m2);
  if (m4 == nullptr) {
    goto error2;
  }
  print_matrix(m4);
  printf("Dimension de la matrice M1 :\n");
  print_dim(m1);
  printf("Dimension de la matrice M2 :\n");
  print_dim(m2);
  printf("Dimension de la matrice resultat de M1 x M2 :\n");
  print_dim(m4);
  printf("Échange des deux lignes de la matrice résultat M1 x M2 :\n");
  matrix *m5 = swap_row(m2, 1, 0);
  if (m5 == nullptr) {
    goto error3;
  }
  print_matrix(m5);
  printf("Matrice résultat de M1 + M2 :\n");
  matrix *m6 = add_mat(m4, m4);
  if (m6 == nullptr) {
    goto error4;
  }
  print_matrix(m6);
  printf("Matrice résultat de M1 x 2 :\n");
  if (self_mult_by_scalar(m1, 2) == nullptr) {
    goto error5;
  }
  print_matrix(m1);
  matrix_dispose(&m1);
  matrix_dispose(&m2);
  matrix_dispose(&m3);
  matrix_dispose(&m4);
  matrix_dispose(&m5);
  matrix_dispose(&m6);
  return EXIT_SUCCESS;
error5:
  matrix_dispose(&m6);
error4:
  matrix_dispose(&m5);
error3:
  matrix_dispose(&m4);
error2:
  matrix_dispose(&m3);
error1:
  matrix_dispose(&m1);
  matrix_dispose(&m2);
error0:
  return EXIT_FAILURE;
}
