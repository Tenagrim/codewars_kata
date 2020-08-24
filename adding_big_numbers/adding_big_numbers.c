#include <stdlib.h>

#include <stdio.h>

int	ft_strlen(char *str)
{
	int count;

	count = 0;
	while (*str != '\0')
	{
		count++;
		str++;
	}
	return (count);
}

void	init_vars(int *max_len, int *min_len, char **max, char **min, char **a, char **b)
{
	char *tmp;

	*max = *a;
	*min = *b;
	while (**max == '0')
		*max = *max + 1;
	while (**min == '0')
		*min = *min + 1;
	if (ft_strlen(*max) < ft_strlen(*min))
	{
		tmp = *max;
		*max = *min;
		*min = tmp;
	}
	*max_len = ft_strlen(*max);
	*min_len = ft_strlen(*min);
}

void	shift(char *str, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		str[i] = str[i + 1];
		i++;
	}
}

char	*add(const char *a, const char *b) 
{
	int	max_len;
	int	min_len;
	char	*res;
	int	i;
	int	j;
	char	*max;
	char	*min;
	int	tmp;
	
	init_vars(&max_len, &min_len, &max, &min, (char**)&a, (char**)&b);
	res = malloc(sizeof(char) * (max_len + 2));
	res[max_len + 1] = '\0';
	res[max_len] = '0';
	//printf("len %d\n", max_len);
	i = max_len;
	j = min_len - 1;
	while (i >= 1)
	{
		res[i - 1] = '0';
		tmp = j >= 0 ? (max[i - 1] - '0') + (min[j] - '0') : max[i - 1] - '0';
		tmp = res[i] == '1' ? tmp + 1 : tmp;
		//printf("{%c}\n", min[j]);
		//printf("i:  %d j: %d  tmp:  %d\n", i, j, tmp);
		if (tmp < 10)
			res[i] = tmp + '0';
		else
		{
			res[i] = (tmp % 10) + '0';
			res[i - 1] = '1'; 
		}
		//printf("|%c|\n", res[i]);
		i--;
		j--;
	}
	if (res[0] == '0')
		shift(res, max_len + 1);
	return (res);
}

int	main(int argc, char **argv)
{
	char *tmp;
	tmp = add(argv[1], argv[2]);
	printf("%s\n",tmp);
	free(tmp);	
}
