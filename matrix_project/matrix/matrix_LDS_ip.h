//  matrix_LDS_ip.h : précisions sur l'implantation du module matrix.

// Si des matrices sont prises en paramètres.
// Soit m le nombres d'elements de la matrice prise en paramètre.
// Soit n le nombre d'element de la seconde matrice prise en paramètre.

// matrix_empty : temps constant; espace constant
// is_empty : temps constant; espace constant
// matrix_dispose : temps linéaire en m; espace constant
// add_element : temps au plus linéaire en m; espace constant
// modification : temps au plus linéaire en m; espace constant
// suppression : temps au plus linéaire en m; espace constant
// print_dim : temps constant; espace constant
// print_matrix : temps linéaire en m; espace constant
// add :
//    temps au plus linéaire en la somme m + n
//    espace au plus linéaire en la somme m + n
// self_mult_by_scalar : temps linéaire en m; espace constant
// mult_mat :
//    temps au plus linéaire en le produit de m * n;
//    espace au plus linéaire en le produit de m * n
// to_sparse_matrix : temps linéaire en m; espace au plus linéaire en m
// to_matrix :
//    temps linéaire en m ;
//    espace linéaire en le produit du nombre de colonnes et lignes.

#define MAT_EXT
