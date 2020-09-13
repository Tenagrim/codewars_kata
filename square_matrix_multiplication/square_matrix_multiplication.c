#include <stdlib.h>
#include <stdio.h>

int	**init_matrix(int width, int height)
{
	int **res = malloc(sizeof(int*) * height);
	for(int i = 0; i < height; i++)
		res[i] = malloc(sizeof(int) * width);
	return (res);
}


int **matrix_multiplication(int **a, int **b, int n) {
	int **res = init_matrix(n,n);
	int subsum;
	
	for(int k = 0; k < n; k++)
	{
		for(int i = 0; i < n; i++)
		{
			subsum = 0;
			for(int j = 0 ; j < n; j++)
			{
				subsum += a[i][j] * b[j][k];
			}
		res[i][k] = subsum;	
		}
	}
	return res;
}

void	print_matrix(int **f, int n)
{
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
			printf("%d ", f[i][j]);
		printf("\n");
	}
}


int	main(int argc, char **argv)
{
  int **a = malloc(2 * sizeof(int *)), **b = malloc(2 * sizeof(int *)), **expected = malloc(2 * sizeof(int *));
  for (int i = 0; i < 2; i++) {
    *(a + i) = malloc(2 * sizeof(int));
    *(b + i) = malloc(2 * sizeof(int));
    *(expected + i) = malloc(2 * sizeof(int));
  }

**a = 1;
  *(*a + 1) = 2;
  **(a + 1) = 3;
  *(*(a + 1) + 1) = 2;
  /*
        3  2
    B = 
        1  1
  */
  **b = 3;
  *(*b + 1) = 2;
  **(b + 1) = 1;
  *(*(b + 1) + 1) = 1;

	int **C = matrix_multiplication(a,b,2);
	print_matrix(a, 2);
	print_matrix(b, 2);
	print_matrix(C, 2);
}
