#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define the matrix structure
struct matrix {
    float **m;    // Pointer to pointer for storing the 2D array
    int rows;     // Number of rows
    int cols;     // Number of columns
};

// Function to allocate memory for the matrix
void allocate_matrix(struct matrix *mat) {
    mat->m = (float **)malloc(mat->rows * sizeof(float *));
    for (int i = 0; i < mat->rows; i++) {
        mat->m[i] = (float *)malloc(mat->cols * sizeof(float));
    }
}

// Function to free the allocated memory of the matrix
void free_matrix(struct matrix *mat) {
    for (int i = 0; i < mat->rows; i++) {
        free(mat->m[i]);
    }
    free(mat->m);
}

// Function to read a matrix from user input
void read_matrix(struct matrix *mat, int matrix_number) {
    printf("Enter the number of rows and columns for Matrix %d (e.g., 2 3): ", matrix_number);
    while (scanf("%d %d", &mat->rows, &mat->cols) != 2 || mat->rows <= 0 || mat->cols <= 0) {
        printf("Invalid input. Please enter two positive integers for rows and columns: ");
        while (getchar() != '\n'); // Clear input buffer
    }

    allocate_matrix(mat);

    printf("Enter %d elements row-wise for Matrix %d: ", mat->rows * mat->cols, matrix_number);
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            while (scanf("%f", &mat->m[i][j]) != 1) {
                printf("Invalid input. Please enter a number: ");
                while (getchar() != '\n'); // Clear input buffer
            }
        }
    }
}

// Function to multiply two matrices
struct matrix multiply(struct matrix mat1, struct matrix mat2) {
    struct matrix result;
    // Check if multiplication is possible
    if (mat1.cols != mat2.rows) {
        // Set result matrix to invalid state
        result.rows = 0;
        result.cols = 0;
        result.m = NULL;
        return result;
    }

    result.rows = mat1.rows;
    result.cols = mat2.cols;
    allocate_matrix(&result);

    // Perform multiplication
    for (int i = 0; i < result.rows; i++) {
        for (int j = 0; j < result.cols; j++) {
            result.m[i][j] = 0.0;
            for (int k = 0; k < mat1.cols; k++) {
                result.m[i][j] += mat1.m[i][k] * mat2.m[k][j];
            }
        }
    }

    return result;
}

// Function to print a matrix
void print_matrix(struct matrix mat) {
    for (int i = 0; i < mat.rows; i++) {
        for (int j = 0; j < mat.cols; j++) {
            printf("%.2f ", mat.m[i][j]);
        }
        printf("\n");
    }
}

int main() {
    struct matrix mat1, mat2, result;

    printf("Matrix Multiplication Program\n");
    printf("-----------------------------\n");

    read_matrix(&mat1, 1);
    read_matrix(&mat2, 2);

    // Check if multiplication is possible before timing
    if (mat1.cols != mat2.rows) {
        printf("Error: Cannot multiply matrices with dimensions %dx%d and %dx%d.\n",
               mat1.rows, mat1.cols, mat2.rows, mat2.cols);
        // Free allocated memory
        free_matrix(&mat1);
        free_matrix(&mat2);
        return 1;
    }

    // Measure time taken for multiplication
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    result = multiply(mat1, mat2);
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Check for a valid result
    if (result.m != NULL && result.rows > 0 && result.cols > 0) {
        printf("Resultant matrix:\n");
        print_matrix(result);
        printf("Time taken for multiplication: %f seconds\n", cpu_time_used);
        free_matrix(&result);
    } else {
        printf("Matrix multiplication failed due to incompatible dimensions.\n");
    }

    // Free allocated memory
    free_matrix(&mat1);
    free_matrix(&mat2);

    return 0;
}
