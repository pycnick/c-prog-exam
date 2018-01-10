#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define ERROR -1


int read_size_matrix(FILE* f, int* m, int*n)
{
    fscanf(f, "%d ", m);
    fscanf(f, "%d ", n);

    return SUCCESS;
}

int read_matrix(FILE* f, int **A, int* m, int* n)
{

    for(int i = 0; i < *m; i++)
        for(int j = 0; j < *n; j++)
            fscanf(f, "%d", &A[i][j]);

    return SUCCESS;
}


int** memory(int **A, int m, int n)
{
    A = malloc(m * sizeof(int *));

    for(int i = 0; i < m; i++)
        A[i] = malloc(n * sizeof(int));

    return A;
}

void mfree(int **A, int m)
{
    for(int i = 0; i < m; i++) 
        free(A[i]);
    free(A);
}

void mprintf(int **A, int m, int n)
{   
    printf("%d %d\n", m, n);

    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
            printf("|%4d ", A[i][j]);
        printf("|\n");
    }
    
    printf("\n");
}

int func(int** A, int column, int row)
{
	int tmp = A[0][0];
	A[0][0] = 0;

	for(int i = 1; i < column - 1; i++)
	{
		int data = tmp;
		tmp = A[0][i];
		A[0][i] = data;
	}
	for(int i = 0; i < row - 1; i++)
	{
		int data = tmp;
		tmp = A[i][column - 1];
		A[i][column - 1] = data;
	}
	for(int i = column - 1; i > 0; i--)
	{
		int data = tmp;
		tmp = A[row - 1][i];
		A[row - 1][i] = data;
	}
	for(int i = row - 1; i > 0; i--)
	{
		int data = tmp;
		tmp = A[i][0];
		A[i][0] = data;
	}

	A[0][0] = tmp;

	return 1;
}


int main(void)
{
	FILE* file;

	int row = 0, column = 0;

	file = fopen("in.txt", "r");

	int** A = NULL;

	read_size_matrix(file, &column, &row);

	A = memory(A, column, row);

	read_matrix(file, A, &row, &column);

	mprintf(A, row, column);

	func(A, row, column);

	mprintf(A, row, column);

	return 0;
}