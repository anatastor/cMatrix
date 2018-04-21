
#include "cmatrices.h"


matrix *matrix_create (const size_t rows, const size_t cols)
{
    matrix *m = calloc(1, sizeof(matrix));
    matrix_init(m, rows, cols);
    return m;
}


void matrix_init (matrix *m, const size_t rows, const size_t cols)
{   
    m->rows = rows;
    m->cols = cols;
    m->elements = calloc(rows * cols, sizeof(double));
}


void matrix_set (matrix *m, ...)
{
    va_list arguments;
    va_start(arguments, m);
    for (size_t i = 0; i < m->rows * m->cols; i++)
        m->elements[i] = va_arg(arguments, double);
    va_end(arguments);
}


void matrix_copy (matrix *m, double *b)
{
    for (size_t i = 0; i < m->rows * m->cols; i++)
        m->elements[i] = b[i];
}


void matrix_set_value (matrix *m, const size_t index, const double value)
{
    m->elements[index] = value;
}


matrix *matrix_transpose (matrix *m)
{
    matrix *res = matrix_create(m->cols, m->rows);
    for (size_t r = 0; r < m->rows; r++)
        for (size_t c = 0; c < m->cols; c++)
            M(res, c, r) = M(m, r, c);
    return res;
}


matrix *matrix_scalar (matrix *a, const double b)
{
    matrix *m = matrix_create(a->rows, a->cols);
    for (size_t i = 0; i < a->rows * a->cols; i++)
        m->elements[i] = b * a->elements[i];
    return m;
}


matrix *matrix_add (matrix *a, matrix *b)
{
    if (a->cols == b->cols && a->rows == b->rows)
    {   
        matrix *m = matrix_create(a->rows, a->cols);
        for (size_t i = 0; i < a->rows * a->cols; i++)
        {
            m->elements[i] = a->elements[i] + b->elements[i];
        }

        return m;
    }

    return NULL;
}


void matrix_add_to (matrix *a, matrix *b)
{
    if (a->cols == b->cols && a->rows == b->rows)
    {
        for (size_t i = 0; i < a->rows * a->cols; i++)
        {
            a->elements[i] += b->elements[i];

        }
    }
}


matrix *matrix_sub (matrix *a, matrix *b)
{
    return (matrix_add(a, matrix_scalar(b, -1.0)));
}


matrix *matrix_dot (matrix *a, matrix *b)
{
    if (a->cols == b->rows)
    {
        matrix *m = matrix_create(a->rows, b->cols);
        for (size_t rm = 0; rm < m->rows; rm++)
        {
            for (size_t cm = 0; cm < m->cols; cm++)
            {
                for (size_t i = 0; i < a->cols; i++)
                {
                    M(m, rm, cm) += M(a, rm, i) * M(b, i, cm);
                }
            }
        }

        return m;
    }   

    return NULL;
}


void matrix_sigmoid (matrix *m)
{
    for (size_t i = 0; i < m->rows * m->cols; i++)
    {
        m->elements[i] = 1.0 / (1.0 + exp(-m->elements[i]));
    }
}


void matrix_sigmoid_derivate (matrix *m)
{
    for (size_t i = 0; i < m->rows * m->cols; i++)
    {
        m->elements[i] = m->elements[i] * (1.0 - m->elements[i]);
    }
}


void matrix_print (const matrix *m)
{
    printf("[");
    for (size_t r = 0; r < m->rows; r++)
    {
        printf("\n[");
        for (size_t c = 0; c < m->cols; c++)
        {
            printf("%lf ", M(m, r, c));
        }
        printf("]");
    }
    printf("\n]\n");
}
