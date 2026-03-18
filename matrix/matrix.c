//Реализуй основные действия с матрицами: 

// create_matrix (создание) есть
// remove_matrix (очистка и уничтожение) есть
// eq_matrix (сравнение) 
// sum_matrix (сложение) 
// sub_matrix (вычитание) 
// mult_matrix (умножение)  
// mult_number (умножение на число) 
// transpose (транспонирование) 
// determinant (вычисление определителя) 
// calc_complements (вычисление матрицы алгебраических дополнений) 
// inverse_matrix (поиск обратной матрицы)  

//Все операции (кроме сравнения матриц) должны возвращать результирующий код:

// 0 — OK;
// 1 — Ошибка, некорректная матрица;
// 2 — Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой нельзя провести вычисления и т. д.).


#include <stdio.h>
#include <string.h>

#define SUCCESS 1
#define FAILURE 0

typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;

int is_matrix_exists(matrix_t *A);

int s21_create_matrix(int rows, int columns, matrix_t *result);

void s21_remove_matrix(matrix_t *A);

int s21_eq_matrix(matrix_t *A, matrix_t *B); // не возвращают 0 1 2

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

int s21_mult_number(matrix_t *A, double number, matrix_t *result);

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

int s21_transpose(matrix_t *A, matrix_t *result);

int s21_calc_complements(matrix_t *A, matrix_t *result);

int s21_determinant(matrix_t *A, double *result);

int s21_inverse_matrix(matrix_t *A, matrix_t *result);

int s21_create_matrix(int rows, int columns, matrix_t *result){
    result->rows = rows;
    result->columns = columns;

    int num;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {   
            if(scanf("%d ", num) != 1){
                printf("Ошибка ввода!/n");
                return 2;
            }
            result->matrix[i][j] = num;
        }
    }
    
    return 1;
}

void s21_remove_matrix(matrix_t *A){
    if (){
        printf("Ошибка, матрица не существует!/n");
    }

    if(A->matrix != NULL){
        for (int i = 0; i < A->rows; i++)
        {
            if(A->matrix[i] != NULL){
                free(A->matrix[i]);
                A->matrix[i] == NULL;
            }
        }
    }

    free(A->matrix);
    free(A);
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result){

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {   
            if(scanf("%d ", num) != 1){
                printf("Ошибка ввода!/n");
                return 2;
            }
            result->matrix[i][j] = num;
        }
    }
    
    return 1;
}

int is_matrix_exists(matrix_t *A){
    if (A == NULL){
        return 2;
    }

    return 0;
}

