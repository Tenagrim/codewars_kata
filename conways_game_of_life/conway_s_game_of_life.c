#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define DEAD "░░"
#define LIVE "▓▓"

#define TORUS 1
#define BORDERED 2 

//char *htmlize(int **, int, int);

int **read_file(int ***res, char *file_name, int *rows, int *cols)
{
	int	fd;
	char	*buff;
	char	c;
	int	i;
	int	j;

	i = 0;
	buff = malloc(500);
	fd = open(file_name, O_RDONLY);
	while(read(fd, buff + i, 1) == 1 && buff[i] != '\n')
		i++;
	buff[i + 1] = '\0';
	*rows = atoi(buff);
	i = 0;
	while(read(fd, buff + i, 1) == 1 && buff[i] != '\n')
		i++;
	*cols = i;
	i = 0;
	*res = malloc(sizeof(int*) * *rows);
	res[0][0] = malloc(sizeof(int) * *cols);
	while (i < *cols)
	{
		res[0][0][i] = (buff[i] == '_' || buff[i] == '.') ? 0 : 1; 
		i++;
	}
	i = 1;
	while (i < *rows)
	{
		j = 0;
		res[0][i] = malloc(sizeof(int) * *cols);
		while (j < *cols)
		{
			read(fd, &c, 1);
			res[0][i][j] = (c == '_' || c == '.') ? 0 : 1; 
			j++;
		}
		read(fd, &c, 1);
		i++;
	}
	close(fd);
	free(buff);
	return (*res);
}

int **get_dead_field( int ***res, int rows, int cols)
{
	int i;
	int j;

	*res = malloc(sizeof(int*) * rows);
	i =0;
	while (i < rows)
	{
		j = 0;
		res[0][i] = malloc(sizeof(int) * cols);
		while (j < cols)
		{
			res[0][i][j] = 0;
			j++;
		}
		i++;
	}
	return (*res);
}



int get_state_torus(int **cells, int rows, int cols, int x, int y)
{
	int neighbours;
	int i;
	int j;

	int i_c;
	int j_c;

	i = y - 1 >= 0 ? y - 1 : rows - 1;
	j = x - 1 >= 0 ? x - 1 : cols - 1;
	i_c = 0;
	neighbours = 0;
	while (i_c < 3)
	{
		j_c = 0;
		j = x - 1 >= 0 ? x - 1 : cols - 1;
		while (j_c < 3)
		{
			if (!(i_c == 1 && j_c == 1))
			{
			//printf("%d %d %d\n",i, j, cells[i][j] );
				if (cells[i][j] == 1)
					neighbours++;
			}
			j = j + 1 == cols ? 0  : j + 1;
			j_c++;
		}
		i = i + 1 == rows ? 0 : i + 1;
		i_c++;
	}
	//printf("x: %d y: %d neigh: %d\n", x, y, neighbours);
	if (cells[y][x] == 1)
	{
		if (neighbours == 2 || neighbours == 3)
			return (1);
		else
			return (0);
	}
	else
	{
		if (neighbours == 3)
			return (1);
		else
			return (0);
	}

}

int get_state_bordered(int **cells, int rows, int cols, int x, int y)
{
	int neighbours;
	int up;
	int down;
	int left;
	int right;

	int tmp_x;
	int tmp_y;

	up = y - 1 < 0 ? 0 : y - 1;
	down = y + 1 == rows ? rows - 1 : y + 1;
	left = x - 1 < 0 ? 0 : x - 1;
	right = x + 1 == cols ? cols - 1 : x + 1;
	neighbours = 0;
	while (up <= down)
	{
		left = x - 1 < 0 ? 0 : x - 1;
		while (left <= right)
		{
			if (!(left == x && up == y))
			{
			//printf("%d %d %d\n",i, j, cells[i][j] );
				if (cells[up][left] == 1)
					neighbours++;
			}
			left++;
		}
		up++;
	}
	//printf("x: %d y: %d neigh: %d\n", x, y, neighbours);
	if (cells[y][x] == 1)
	{
		if (neighbours == 2 || neighbours == 3)
			return (1);
		else
			return (0);
	}
	else
	{
		if (neighbours == 3)
			return (1);
		else
			return (0);
	}
}

int get_state(int **cells, int rows, int cols, int x, int y, int mode)
{
	if (mode == TORUS)
		return(get_state_torus(cells, rows, cols, x, y));
	else if (mode == BORDERED)
		return(get_state_bordered(cells, rows, cols, x, y));
}

void free_field(int **field, int rows)
{
	int i;

	if (field == NULL)
		return ;
	i = 0;
	while(i < rows)
	{
		free(field[i]);
		i++;
	}
	free(field);
}

int **get_generation(int **cells, int generations, int *rowptr, int *colptr) {
	int **res;
	int **tmp;
	int i;
	int j;
	int cur_gen;
	int **prev_gen;

	prev_gen = cells;
	cur_gen = 0;
	while (cur_gen < generations)
	{

		get_dead_field(&res, *rowptr, *colptr);
		i = 0;
		j = 0;
		while (i < *rowptr)
		{
			j = 0;
			while (j < *colptr)
			{
				res[i][j] = get_state(prev_gen, *rowptr, *colptr, j, i, BORDERED);
				j++;
			}
			i++;
		}
		if (cur_gen != 0)
			free_field(prev_gen, *rowptr);
		prev_gen = res;
		cur_gen++;
	}
	return (res);

  // Your code here
  // NOTE: Please make a deep copy of the GoL universe and modify that instead
  // of the original universe `cells` passed in because the test cases will
  // `free` the memory allocated by your solution *and* to the original grid
  // which will throw an error otherwise.  Also keep in mind that it is considered
  // best practice to keep your function pure.
}



void gotoxy(int x,int y)
{
	//printf("%c[%d;%df",0x1B,y,x);
	printf("%c[%d;%df",0x1B,y,x);
}


void raw_display(int **field, int rows, int cols, int off_x, int off_y)
{
	int i;
	int j;

	i = 0;
	while (i < rows)
	{
		j = 0;
	//	gotoxy(off_x,off_y + i);
		while (j < cols)
		{
			//gotoxy(i * 2 + +off_x,j + off_y);
				printf("%d", field[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\n");


}


void display(int **field, int rows, int cols, int off_x, int off_y)
{
	int i;
	int j;

	i = 0;
	//gotoxy(off_x,off_y + i);
	while (i < rows)
	{
		j = 0;
		gotoxy(off_x,off_y + i);
		while (j < cols)
		{
			//gotoxy(i * 2 + +off_x,j + off_y);
			if (field[i][j] == 0)		
				printf("%s", DEAD);
			else
				printf("%s", LIVE);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\n");
}



int main(int argc, char **argv)
{
	int **cells;
	int rows = 5;
	int cols = 10;
	int **gen;
	int **tmp;
	char c;
	int step;

	step = 1;
	if (argc == 1)
	{
		get_dead_field(&cells, rows,cols);
		cells[0][0] = 1;
		*(*cells + 1) = 0;
		*(*cells + 2) = 0;
		**(cells + 1) = 0;
		*(*(cells + 1) + 1) = 1;
		*(*(cells + 1) + 2) = 1;
		**(cells + 2) = 1;
  		*(*(cells + 2) + 1) = 1;
		*(*(cells + 2) + 2) = 0;
	}
	else
	{
		read_file(&cells, argv[1], &rows, &cols);
	}

	gen = get_generation(cells, step, &rows, &cols);
	display(cells, rows, cols, 2, 3);
	while (1) //(read(1, &c, 1))
	{
		tmp = gen;
		display(gen, rows, cols, 2, 3);
		gen = get_generation(gen, step, &rows, &cols);
		free_field(tmp, rows);	
		usleep(atoi(argv[2]));
	}
	return (0);
}
