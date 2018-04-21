/*
 * GNU cMatrices 2.3
 * License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
 * This is free software: you are free to change and redistibute it.
 * There is NO WARRANTY, to the extent permitted by law.
 *
 * Author: Torsten Lehmann
 * Mail: anatas.torsten@gmx.de
 */


#ifndef _CMATRICES_H_
#define _CMATRICES_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>


#define M(m, r, c)  (m->elements[c + r * m->cols])


typedef struct
{
    size_t rows;
    size_t cols;
    double *elements;
} matrix;


matrix *matrix_create (const size_t rows, const size_t cols);
void matrix_init (matrix *m, const size_t rows, const size_t cols);

void matrix_copy (matrix *m, double *b);
void matrix_set (matrix *m, ...);

void matrix_set_value (matrix *m, const size_t index, const double value);


matrix *matrix_transpose (matrix *m);


matrix *matrix_scalar (matrix *a, const double b);
matrix *matrix_add (matrix *a, matrix *b);
void matrix_add_to (matrix *a, matrix *b);
matrix *matrix_sub (matrix *a, matrix *b);
matrix *matrix_dot (matrix *a, matrix *b);


void matrix_sigmoid (matrix *m);
void matrix_sigmoid_derivate (matrix *m);

void matrix_print (const matrix *m);



#endif
