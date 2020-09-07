#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define BOARD_HEIGHT	8
#define BOARD_WIDTH	8


typedef struct	s_point
{
	int	x;
	int	y;
}		t_point;

t_point	set_pos(int x, int y)
{
	t_point res;

	res.x = x;
	res.y = y;
	return (res);
}

char	is_equal(t_point a, t_point b)
{
	return ((a.x == b.x && a.y == b.y) ? 1 : 0);
}

void	print_point(t_point a)
{
	printf("x = %d  y = %d ", a.x, a.y);
}

void	print_field(short **f)
{
	for(int i = 0; i < BOARD_HEIGHT; i++)
	{
		for(int j = 0; j < BOARD_HEIGHT; j++)
			printf("%d ", f[i][j]);
		printf("\n");
	}

}

short	**init_field(int width, int height)
{
	short **res = malloc(sizeof(short*) * height);
	for(int i = 0; i < height; i++)
	{
		res[i] = malloc(sizeof(short) * width);
		for(int j = 0; j < width; j++)
			res[i][j] = 9;
	}
	return (res);
}


char	in_world(t_point pos)
{
	return(pos.x >= 0 && pos.y >=0 && pos.x < BOARD_WIDTH && pos.y < BOARD_HEIGHT);
}

char try_pos(t_point pos, t_point dest, int path_len, short **field)
{
	if(in_world(pos) == 0)
		return (0);
	field[pos.y][pos.x] = (short)(path_len );
	return (0);
}

short	rec_knight(t_point pos, t_point dest, short path_len, short **field)
{


	if (in_world(pos) == 0)
		return 0;

	if(field[pos.y][pos.x] < path_len)
		return (0);

	try_pos(pos, dest, path_len, field);

	if(is_equal(pos, dest))
		return (0);

	rec_knight (set_pos(pos.x - 1, pos.y + 2), dest , path_len + 1, field);	
	rec_knight (set_pos(pos.x - 1, pos.y - 2), dest , path_len + 1, field);	
	rec_knight (set_pos(pos.x - 2, pos.y + 1), dest , path_len + 1, field);
	rec_knight (set_pos(pos.x - 2, pos.y - 1), dest , path_len + 1, field);
	rec_knight (set_pos(pos.x + 1, pos.y + 2), dest , path_len + 1, field);
	rec_knight (set_pos(pos.x + 1, pos.y - 2), dest , path_len + 1, field);
	rec_knight (set_pos(pos.x + 2, pos.y + 1), dest , path_len + 1, field);
	rec_knight (set_pos(pos.x + 2, pos.y - 1), dest , path_len + 1, field);

	return (0);

}

void	free_field(short **field)
{
	for(int i = 0; i< BOARD_HEIGHT; i++)
		free(field[i]);	
	free(field);
}

short knight(const char *p1, const char *p2)
{
	short res;

	short **field = init_field(BOARD_WIDTH, BOARD_HEIGHT);
	t_point pos = set_pos(p1[0] - 'a', p1[1] - '1');
	t_point dest = set_pos(p2[0] - 'a', p2[1] - '1');

	rec_knight(pos, dest, 0, field);
	res  = field[dest.y][dest.x];
	print_field(field);
	free_field(field);	
	return (res);
}

int	main(int argc, char **argv)
{
	printf(">>%d<<\n",knight(argv[1], argv[2]));
}
