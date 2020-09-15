#include <stdlib.h>

#define RIGHT 1
#define DOWN  2
#define LEFT  3
#define UP    4

void	turn(int *direction)
{
	*direction = *direction + 1;
	if (*direction >= 5)
		*direction = *direction % 5 + 1;
}

int	*snail(size_t *outsz, const int **mx, size_t rows, size_t cols)
{
	int	step = 0;
	size_t	*max;
	int	*res;
	int	offset = 0;
	int	direction = RIGHT;

	int	i = 0;
	int	j = 0;

	if(rows == 0 || cols == 0)
		return (int*)(outsz);
	
	res = malloc(sizeof(size_t) * (rows * cols));
	*outsz = (rows*cols);
	for(int k = 0; k < rows * cols; k++)
	{
		res[k] = mx[i][j];
		switch(direction)
		{
			case RIGHT:
				j++;
				step = j;
				max = &cols;
				break;
			case DOWN:
				i++;
				step = i;
				max = &rows;
				break;
			case LEFT:
				j--;
				step = cols-j-1;
				max = &cols;
				break;
			case UP:
				i--;
				step = cols-i-1;
				max = &rows;
				break;
		}
		if(*max - (size_t)step - 1 == offset + 1 && direction == UP)
			offset++;
		if(*max - (size_t)step - 1 == offset)
			turn(&direction);
	}
	return (res);
}

///////////////////////////////////////////////////////////////////
#include <stdio.h>

int	**rand_matrix(int rows, int cols)
{
	int	**res = malloc(sizeof(int*) * rows);
	int	c = 1;
	
	for(int i = 0; i < rows; i++)
	{
		res[i] = malloc(sizeof(int) * cols);
		for(int j = 0; j < cols; j++)
		{
			res[i][j] = c;
			c++;
		}
	}
	return res;
}

void	free_matrix(int **matrix, int rows)
{
	for(int i = 0; i < rows; i++)
		free(matrix[i]);
}

void	print_matrix(int **matrix, int rows,int cols)
{
	for(int i= 0; i < rows; i++)
	{
		for(int j = 0 ; j < cols; j++)
			printf("%d\t", matrix[i][j]);
		printf("\n");
	}
}

int	main(int ac, char **av)
{
	int	**matrix;
	int	rows;
	int	cols;
	size_t	size;
	int	*res;

	if(ac < 3)
	{
		printf("missing matrix size\n");
		return 0;
	}

	rows = atoi(av[1]);
	cols = atoi(av[2]);

	if(rows <= 0 || cols <= 0)
	{
		printf("invalid matrix size\n");
		return 0;
	}

	matrix = rand_matrix(rows, cols);
	print_matrix(matrix, rows, cols);
	res = snail((size_t*)&size, (const int**)matrix, (size_t)rows, (size_t)cols);
	for(int i = 0; i < rows*cols; i++)
		printf("%d ", res[i]);
	printf("\n");

	free(res);
	free_matrix(matrix, rows);
}
