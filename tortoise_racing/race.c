#include <stdlib.h>
#include <stdio.h>

int*		separate_time(int time_secs)
{
	int *res;

	res = malloc(sizeof(int) * 3);
	if (time_secs == -1)
	{
		res[0] = -1;
		res[1] = -1;
		res[2] = -1;
		return (res);
	}
	else 
	{
		res[0] = time_secs / 3600;
		res[1] = (time_secs - res[0] * 3600) / 60;
		res[2] = time_secs % 60;

		
		
		return (res);
	}
}

int*		race(int v1, int v2, int g)
{
	float	v1_s;
	float	v2_s;
	float	res_s;

	if (v1 >= v2)
		return (separate_time(-1));
	else
	{
		v1_s = (float)v1 / 3600;
		v2_s = (float)v2 / 3600;
		res_s = (float)g / (v2 -v1) * 3600;
//		printf (" g = %d  v1_s =%f v2_s = %f  res_s = %f\n",g,v1_s,v2_s, res_s);
		return (separate_time((int)res_s));
		
	}
}

int		main(int argc, char **argv)
{
	int *res;

	res = race(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
	int *res2 = separate_time(1938);
	printf("%d   %d   %d\n", res[0], res[1], res[2]);

	free(res);
	free(res2);
}
