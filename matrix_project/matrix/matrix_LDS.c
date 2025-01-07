#include <stdio.h>
#include <limits.h>
#include "matrix_LDS.h"

typedef struct cell cell;

struct cell {
  size_t row;
  size_t col;
  int value;
  cell *next;
};

struct matrix {
  cell *head;
  size_t nb_element;
  size_t nb_rows;
  size_t nb_cols;
};

matrix *matrix_empty() {
  matrix *p = malloc(sizeof(*p));
  if (p == nullptr) {
    return nullptr;
  }
  p->head = nullptr;
  p->nb_element = 0;
  p->nb_rows = 0;
  p->nb_cols = 0;
  return p;
}

bool is_empty(matrix *m) {
  return m->head == nullptr;
}

void matrix_dispose(matrix **mptr) {
  if (*mptr == nullptr) {
    return;
  }
  cell *p = (*mptr)->head;
  while (p != nullptr) {
    ((*mptr)->head) = p->next;
    free(p);
    p = (*mptr)->head;
  }
  free(*mptr);
  *mptr = nullptr;
}

//  research : cherche la refèrence se trouvant aux coordonnées representées par
//    le couple (row, col), en cas de succès renvoie un pointeur vers la
//    cellule correspondante sinon nullptr.
static cell *research(matrix *m, size_t row, size_t col) {
  cell *p = m->head;
  while (p != nullptr) {
    if (p->row == row && p->col == col) {
      return p;
    }
    p = p->next;
  }
  return nullptr;
}

int modification(matrix *m, size_t row, size_t col, int value) {
  cell *p = research(m, col, row);
  if (p == nullptr) {
    return EOF;
  }
  int r = p->value;
  p->value = value;
  return r;
}

int delete_element(matrix *m, size_t row, size_t col) {
  cell *p = research(m, col, row);
  if (p == nullptr) {
    return EOF;
  }
  cell *q = m->head;
  if (p == q) {
    int r = p->value;
    free(p);
    m->head = nullptr;
    return r;
  }
  while (q->next != p) {
    q = q->next;
  }
  if (p->next == nullptr) {
    q->next = nullptr;
  } else {
    q->next = p->next;
  }
  int r = p->value;
  free(p);
  return r;
}

void *add_element(matrix *m, size_t row, size_t col, int value) {
  if (research(m, row, col) || value == 0) {
    return nullptr;
  }
  cell *p = malloc(sizeof(*p));
  if (p == nullptr) {
    return nullptr;
  }
  p->col = col;
  p->row = row;
  p->value = value;
  p->next = nullptr;
  cell *prev = nullptr;
  cell *current = m->head;
  while (current != nullptr
      && (current->row < row
      || (current->row == row && current->col < col))) {
    prev = current;
    current = current->next;
  }
  if (prev == nullptr) {
    p->next = m->head;
    m->head = p;
  } else {
    prev->next = p;
    p->next = current;
  }
  ++(m->nb_element);
  if (row + 1 > m->nb_rows) {
    m->nb_rows = row + 1;
  }
  if (col + 1 > m->nb_cols) {
    m->nb_cols = col + 1;
  }
  return (void *) p;
}

void print_dim(matrix *m) {
  printf("%zu\tx\t%zu\n\n", m->nb_rows, m->nb_cols);
}

void print_matrix(matrix *m) {
  if (is_empty(m)) {
    return;
  }
  for (size_t i = 0; i < m->nb_rows; ++i) {
    for (size_t j = 0; j < m->nb_cols; ++j) {
      cell *p = (cell *) research(m, i, j);
      if (p != nullptr) {
        printf("%d\t", p->value);
      } else {
        printf("0\t");
      }
    }
    printf("\n");
  }
  printf("\n");
}

matrix *add_mat(matrix *m1, matrix *m2) {
  if (m1->nb_cols != m2->nb_cols && m1->nb_rows != m2->nb_rows) {
    return nullptr;
  }
  matrix *m = matrix_empty();
  if (m == nullptr) {
    return nullptr;
  }
  cell *p = m1->head;
  cell *q = m2->head;
  while (p != nullptr || q != nullptr) {
    if (p != nullptr && q != nullptr) {
      if (p->row == q->row && p->col == q->col) {
        if (p->value > INT_MAX - q->value) {
          matrix_dispose(&m);
          return nullptr;
        }
        int sum = p->value + q->value;
        if (sum != 0) {
          if (add_element(m, p->row, p->col, sum) == nullptr) {
            matrix_dispose(&m);
            return nullptr;
          }
        }
        p = p->next;
        q = q->next;
      } else if (p->row < q->row || (p->row == q->row && p->col < q->col)) {
        if (add_element(m, p->row, p->col, p->value) == nullptr) {
          matrix_dispose(&m);
          return nullptr;
        }
        p = p->next;
      } else {
        if (add_element(m, q->row, q->col, q->value) == nullptr) {
          matrix_dispose(&m);
          return nullptr;
        }
        q = q->next;
      }
    } else if (p != nullptr) {
      if (add_element(m, p->row, p->col, p->value) == nullptr) {
        matrix_dispose(&m);
        return nullptr;
      }
      p = p->next;
    } else {
      if (add_element(m, q->row, q->col, q->value) == nullptr) {
        matrix_dispose(&m);
        return nullptr;
      }
      q = q->next;
    }
  }
  return m;
}

matrix *self_mult_by_scalar(matrix *m, int scalar) {
  cell *p = m->head;
  if (scalar == 0) {
    while (p != nullptr) {
      cell *q = p;
      p = p->next;
      free(q);
    }
    m->head = nullptr;
    m->nb_element = 0;
    m->nb_rows = 0;
    m->nb_cols = 0;
    return m;
  }
  if (p->value > INT_MAX / scalar) {
    return nullptr;
  }
  while (p != nullptr) {
    p->value *= scalar;
    p = p->next;
  }
  return m;
}

matrix *mult_mat(matrix *m1, matrix *m2) {
  if (m1->nb_cols != m2->nb_rows) {
    return nullptr;
  }
  matrix *m = matrix_empty();
  if (m == nullptr) {
    return nullptr;
  }
  for (cell *p = m1->head; p != nullptr; p = p->next) {
    for (cell *q = m2->head; q != nullptr; q = q->next) {
      if (p->col == q->row) {
        size_t row = p->row;
        size_t col = q->col;
        int product = (p->value) * (q->value);
        cell *r = research(m, row, col);
        if (r != nullptr) {
          r->value += product;
        } else {
          if (add_element(m, row, col, product) == nullptr) {
            matrix_dispose(&m);
            return nullptr;
          }
        }
      }
    }
  }
  m->nb_cols = m1->nb_rows;
  m->nb_rows = m2->nb_cols;
  return m;
}

matrix *to_sparse_matrix(int **t, size_t rows, size_t cols) {
  matrix *m = matrix_empty();
  if (m == nullptr) {
    return nullptr;
  }
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      if (t[i][j] != 0) {
        if (add_element(m, i, j, t[i][j]) == nullptr) {
          matrix_dispose(&m);
          return nullptr;
        }
      }
    }
  }
  return m;
}

int **to_dense_matrix(matrix *m) {
  int **t = malloc(m->nb_rows * sizeof(*t));
  if (t == nullptr) {
    return nullptr;
  }
  for (size_t i = 0; i < m->nb_rows; ++i) {
    t[i] = calloc(m->nb_cols, sizeof(**t));
    if (t[i] == nullptr) {
      for (size_t j = 0; j < i; ++j) {
        free(t[j]);
      }
      free(t);
      return nullptr;
    }
  }
  for (cell *p = m->head; p != nullptr; p = p->next) {
    t[p->row][p->col] = p->value;
  }
  return t;
}

matrix *swap_row(matrix *m, size_t row1, size_t row2) {
  if (is_empty(m) || m->nb_rows <= 1
      || row1 == row2
      || row1 >= m->nb_rows
      || row2 >= m->nb_rows) {
    return nullptr;
  }
  matrix *new_matrix = matrix_empty();
  if (new_matrix == nullptr) {
    return nullptr;
  }
  for (cell *p = m->head; p != nullptr; p = p->next) {
    size_t new_row = p->row;
    if (new_row == row1) {
      new_row = row2;
    } else if (new_row == row2) {
      new_row = row1;
    }
    if (add_element(new_matrix, new_row, p->col, p->value) == nullptr) {
      matrix_dispose(&new_matrix);
      return nullptr;
    }
  }
  return new_matrix;
}
