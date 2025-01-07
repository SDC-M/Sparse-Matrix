//  matrix_LSD.h : partie interface d'un module matrix ainsi que pour une
// extension optionnelle.

//  Fonctionnement général :

//  L'extension est formée des éventuelles déclarations et définitions qui
//    figurent aux lignes 94-113.

//  Les indices de lignes / colonnes commencent à 0.

//  Les identificateurs introduits par l'extension ainsi que les identificateurs
//    de macro MAT_EXT et WANT_MAT_EXT sont réservés pour être utilisés
//    comme indiqué ci-après :
//  - lorsque le module peut mettre l'intégralité de l'extension à disposition
//      de l'utilisateurice, la macro MAT_EXT doit être définie dans l'en-tête
//      "matrix_LDS_ip.h" ;
//  - dans le cas contraire, la macro MAT_EXT n'est pas définie dans l'en-tête
//      "matrix_LDS_ip.h" et ne doit pas l'être au sein de l'unité de traduction
//      de prétraitement  ;
//  - la visibilité et l'implantation de l'extension ne sont effectives qu'à la
//      double condition que la macro MAT_EXT soit définie dans l'en-tête
//      "stack_ip.h" et que la macro WANT_MAT_EXT soit définie par
//      l'utilisateurice ;
//  - aucune modification du statut défini/non défini des macros MAT_EXT et
//      WANT_MAT_EXT ne doit intervenir au sein de l'unité de traduction de
//      prétraitement après que le présent en-tête ait été inclus pour la
//      première fois.

//- STANDARD --v---v---v---v---v---v---v---v---v---v---v---v---v---v---v---v---v

#include <stdlib.h>

//  struct matrix, matrix : type et nom de type d'un contrôleur regroupant les
//    informations nécessaires pour gérer une matrice de références sur des
//    entiers.
typedef struct matrix matrix;

//  matrix_empty : tente d'allouer les ressources nécessaires pour gérer une
//    nouvelle matrice initialement vide. Renvoie un pointeur nul en cas de
//    dépassement de capacité. Renvoie sinon un pointeur vers le contrôleur
//    associé à la matrice.
extern matrix *matrix_empty();

//  is_empty : renvoie true ou false selon que la matrice associée à m est
//    vide ou non.
extern bool is_empty(matrix *m);

//  matrix_dispose : sans effet si *mptr est un pointeur nul. Libère sinon les
//    ressources allouées à la gestion de la matrice   associée à *mptr puis
//    affecte un pointeur nul à *mptr.
extern void matrix_dispose(matrix **mptr);

//  add_element : renvoie nullptr si l'element à l'indice représenter par les
//   coordonnées (row, col) ou si une erreur d'allocation à eu lieu en tentant
//   d'ajouter la valeur au bon endroit dans la liste chainée, en cas de succès
//   renvoie un poiteur vers la cellule ajouté.
extern void *add_element(matrix *m, size_t row, size_t col, int value);

// modification : renvoie EOF si l'element n'existe pas sinon l'ancienne valeur.
extern int modification(matrix *m, size_t row, size_t col, int value);

//  delete_element : renvoie EOF si l'element n'existe pas sinon libère la
//   cellule associé et renvoie la valeur supprimée.
extern int delete_element(matrix *m, size_t row, size_t col);

//  print_dim : affiche sur la sortie standart la dimension associé à la matrice
//   pointée par m.
extern void print_dim(matrix *m);

//  print_matrix : affiche sur la sortie standart une représentation de la
//   matrice pointée par m.
extern void print_matrix(matrix *m);

//  add_mat : tente d'allouer les ressources nécéssaires à la création d'une
// nouvelle matrice représentant l'addition des matrices pointées par m1 et m2.
extern matrix *add_mat(matrix *m1, matrix *m2);

// self_mult_by_scalar : renvoie la matrice multipliée par un scalaire, en cas
//    de dépassement de capacité renvoie nullptr.
extern matrix *self_mult_by_scalar(matrix *m, int scalar);

//  mult_mat : tente d'allouer les ressources nécéssaires à la création d'une
//   nouvelle matrice représentant la multiplication de la matrice pointée par
//   m1 par celle pointée par m2, retourn nullptr en cas d'échec.
extern matrix *mult_mat(matrix *m1, matrix *m2);

//- STANDARD --^---^---^---^---^---^---^---^---^---^---^---^---^---^---^---^---^

#undef MAT_EXT
#include "matrix_LDS_ip.h"

#if defined MAT_EXT && defined WANT_MAT_EXT

//- EXTENSION -v---v---v---v---v---v---v---v---v---v---v---v---v---v---v---v---v

//  Sont ajoutées au standard quelques fonctions qui peuvent être utiles.

//  to_sparse_matrix : tente d'allouer les ressources nécéssaires à la création
//   d'une nouvelle matrice représentant la matrice creuse associé au tableau
//   à deux dimensions représenté par t.
extern matrix *to_sparse_matrix(int **t, size_t rows, size_t cols);

//  to_dense_matrix : tente d'allouer les ressources nécéssaires à la création
//   d'une nouvelle matrice representant la matrice pleine associé à la matrice
//   creuse pointée par m.
extern int **to_dense_matrix(matrix *m);

//  swap_row : tente d'allouer les ressources nécéssaires à la création d'une
//   nouvelle matrice representant l'échange des lignes données en paramètre
//   si les lignes n'existent pas ou si la matrice est vide renvoie nullptr.
extern matrix *swap_row(matrix *m, size_t row1, size_t row2);

//- EXTENSION -^---^---^---^---^---^---^---^---^---^---^---^---^---^---^---^---^

#endif
