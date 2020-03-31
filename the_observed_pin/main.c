#include <stdio.h>

#include <stdlib.h>

int	num_of_forks(int digit)
{
	if (digit == 0)
		return (2);
	else if (digit == 5 || digit == 8)
		return (5);
	else if (digit == 1 || digit == 3 || digit == 9 || digit == 7)
		return (3);
	else if (digit == 2 || digit == 4 || digit == 6 || digit == 8)
		return (4);
	else
		return (0);
}

int	*get_forks(int d)
{
	int	*res;

	res = malloc(sizeof(int) * num_of_forks(d));
	if (d == 0)
	{
		res[0] = 0;
		res[1] = 8;
		return (res);
	}
	else if (d == 1)
	{
		res[0] = 1;
		res[1] = 2;
		res[2] = 4;
		return (res);
	}
	else if (d == 2)
	{
		res[0] = 1;
		res[1] = 2;
		res[2] = 5;
		res[3] = 3;
		return (res);
	}
	else if (d == 3)
	{
		res[0] = 3;
		res[1] = 2;
		res[2] = 6;
		return (res);
	}
	else if (d == 4)
	{
		res[0] = 4;
		res[1] = 1;
		res[2] = 5;
		res[3] = 7;
		return (res);
	}
	else if (d == 5)
	{
		res[0] = 5;
		res[1] = 2;
		res[2] = 4;
		res[3] = 6;
		res[4] = 8;
		return (res);
	}
	else if (d == 6)
	{
		res[0] = 6;
		res[1] = 5;
		res[2] = 3;
		res[3] = 9;
		return (res);
	}
	else if (d == 7)
	{
		res[0] = 7;
		res[1] = 8;
		res[2] = 4;
		return (res);
	}
	else if (d == 8)
	{
		res[0] = 5;
		res[1] = 8;
		res[2] = 7;
		res[3] = 9;
		res[4] = 0;
		return (res);
	}
	else if (d == 9)
	{
		res[0] = 9;
		res[1] = 8;
		res[2] = 6;
		return (res);
	}
	else
		return (NULL);
}

size_t	get_aver_size(char *pin)
{
	size_t	res;
	int	i;

	res = 1;
	i = 0;
	while (pin[i] != '\0')
	{
		res *= num_of_forks((int)pin[i] - '0');
		i++;
	}
	return (res);
}

int		ft_strlen(const char *str)
{
	return (*str) ? ft_strlen(++str) + 1 : 0;
}

char		*ft_copy_str(char *src)
{
	char	*res;
	int	i;
	int	j;

	i = 0;
	j = 0;
	res = malloc(sizeof(char) * ft_strlen(src) * 1);
	while (src[j] != '\0')
	{
		res[i] = src[j];
		j++;
		i++;
	}
	res[i] = '\0';
	return (res);
}

void		get_pins_r(char *pin, char **res, int ind, int *k)
{
	int	*forks;
	int	c_forks;
	int	i;
	int	j;
	int	c;
	char	*subres;
	int	len;

	if(pin[ind] == '\0')
		return ;
	forks = get_forks((int)pin[ind] - '0');
	c_forks = num_of_forks((int)pin[ind] - '0');
	c = 0;
	//	printf("%d) pin: %s\n", k, pin);
	while (c < c_forks)
	{
		subres = ft_copy_str(pin);
		subres[ind] = forks[c] + '0';
		get_pins_r(subres, res, ind + 1, k);
		if (pin[ind + 1] == '\0')
		{
			res[*k] = subres;
//			printf("%d) pin: %s\n", *k, subres);
			*k = *k + 1;
		}
		else
			free(subres);
		c++;
	}
	free(forks);
}

//Function should return an array of c-strings with all possible PINs.
//It must allocate all required meomry, but there are no requirements
//as to how it should be done. It must be possible to free
//allocated memory with a call to free_pins.
//Upon return, count should contain the amount of returned PINs.
const char** get_pins(const char* observed, size_t* count)
{
	int	i;
	int	j;
	int	k;
	int	*forks;
	int	c_forks;
	int	len;
	char	*subres;
	char	**res;

	k = 0;
	res = malloc(sizeof(char *) * get_aver_size((char *)observed));
	
	get_pins_r((char *)observed, res, 0, &k);
	

	*count = get_aver_size((char *)observed);
	return ((const char **)res);

}

//This function will be called once per every call to get_pins
//with a pointer value returned by such call.
void free_pins(const char ** pins)
{
	/*
	int	i;
	int	len;

	len = get_aver_size((char *)pins[0]);
	i = 0;
	while(i < len)
	{
		free((char *)pins[i]);
		i++;
	}
	free((char **)pins);
	*/
}


int	main(int argc, char **argv)
{
	int	i;
	size_t	av_size;
	char	**res;

	i = 0;
//	av_size = get_aver_size(atoi(argv[1]));
//	printf("av size = %d\n", av_size);
	res = (char **)get_pins(argv[1], &av_size);
	printf("av size = %zu\n", av_size);
	while (i < av_size)
	{
		printf("%d) \t|%s|\n", i, res[i]);
		i++;
	}
	printf("av size = %zu\n", av_size);
	free_pins((const char **)res);
	return (0);
}
