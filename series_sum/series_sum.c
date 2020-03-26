#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

void		reverse(char *str, int len)
{
	int i;
	int j;
	int temp;

	i = 0;
	j = len - 1;
	while (i < j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}	
}

int		int_to_str(int x, char *str, int d)
{
	int i;

	i = 0;
	if (x != 0)
	{
		while (x != 0)
		{
			str[i] = (x % 10) + '0';
			x /= 10;
			i++;
		}
	}
	else
	{
		str[0] = '0';
		str[1] = '\0';
		i = 1;
	}
	while (i < d)
		str[i++] = '0';
	reverse(str, i);
	str[i] = '\0';
	return (i);

}

void		round_f_str(char *str, int afterpoint)
{
	int point;

	point = 0;
	while (str[point] != '.')
	{
		if (str[point] == '\0')
			return ;
		point++;
	}

	if (str[point + afterpoint + 1] > '5')
		str[point + afterpoint]++;
	else if (str[point + afterpoint] < '5')
		str[point + afterpoint]--;
}

int		ft_iterative_pow(int a, int b)
{
	int	i;
	int	res;

	if (b == 0)
		return (1);
	res = 1;
	i = 0;
	while (i < b)
	{
		res *= a;
		i++;
	}
	return (res);
}

int		ft_roundf(float num)
{
	int	ipart;
	float	fpart;

	ipart = (int)num;
	fpart = num - (float)ipart;
	if (fpart > 0.5)
		ipart++;
	return (ipart);
}

void 		ftoa(float n, char *res, int afterpoint)
{
	int	ipart;
	float	fpart;
	int	i;

	ipart = (int)n;
	fpart = n - (float)ipart;
	i = int_to_str(ipart, res, 0);
	if(afterpoint != 0)
	{
		res[i] = '.';
		fpart = fpart * ft_iterative_pow(10, afterpoint);
		int_to_str(ft_roundf(fpart), res + i + 1, afterpoint);
	}
}

char		*series_sum(const size_t n)
{
	float	res;
	char	*res_str;
	int	i;
	
	res_str = malloc(100);
	i = 0;
	res = 0;
	while (i < n)
	{
		res += 1/(float)(1 + i * 3);
		i++;
	}
	ftoa(res, res_str, 2);
	return (res_str);
}

int		main(int argc, char **argv)
{
	printf("%s\n", series_sum(atoi(argv[1])));
}
