#include <stdio.h>

#include <stdlib.h>

int		ft_strlen(const char *str)
{
	return (*str) ? ft_strlen(++str) + 1 : 0;
}

char		*concat_str(char *str1, char *str2)
{
	int	i;
	char	*res;
	
	res = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2)) + 1);
	i = 0;
	while (*str1)
	{
		res[i] = *str1;
		str1++;
		i++;
	}
	while (*str2)
	{
		res[i] = *str2;
		str2++;
		i++;
	}
	res[i] = '\0';
	return (res);
}

int		dig_count(int n)
{
	int	res;

	if (n == 0)
		return (1);
	res = 0;
	while (n > 0)
	{
		res++;
		n /= 10;
	}
	return (res);
}

char		*ft_itoa(int n)
{
	char	*res;
	int	size;
	int	i;

	i = 0;
	size = dig_count(n);
	res = malloc(sizeof(int) * size + 1);
	while (i < size)
	{
		res[size - i - 1] = n % 10 + '0';
		n /= 10;
		i++;
	}

	res[size] = '\0';
	return (res);
}

int*		separate_time(int time_secs)
{
	int *res;

	res = malloc(sizeof(int) * 5);
	if (time_secs == -1)
	{
		res[0] = -1;
		res[1] = -1;
		res[2] = -1;
		res[3] = -1;
		res[4] = -1;
		return (res);
	}
	else 
	{
		res[4] = time_secs % 60;
		time_secs /= 60; //mins
		//printf("%d\n", )
		res[3] = time_secs % 60;
		time_secs /= 60; //hours
		res[2] = time_secs % 24;
		time_secs /= 24;
		res[1] = time_secs % 365;
		time_secs /= 365;
		res[0] = time_secs;

		/*
		res[0] = time_secs / 31536000;
		res[1] = (time_secs - res[0] * 31536000) / 86400;
		printf("%d\n",(time_secs -res[1] * 86400) / 3600);
		res[2] = (time_secs - res[1] * 86400) / 3600;
		printf("%d\n",time_secs -(res[2] * 3600)/ 60);
		res[3] = (time_secs - res[2] * 3600) / 60;
		res[4] = time_secs % 60;
		*/
		return (res);
	}
}

void		add_to_str(char **dest, char *ins)
{
	char	*t_dest;
	char	*t_ins;

	t_dest = *dest;
	t_ins = ins;
	*dest = concat_str(*dest, ins);
	free(t_dest);
	free(t_ins);
}

void		add_to_str_p(char **dest, char *ins)
{
	char	*t_dest;

	t_dest = *dest;
	*dest = concat_str(*dest, ins);
	free(t_dest);
}

int		is_last(int *nums, int ind)
{
	int i;

	i = ind + 1;
	if (i >= 5)
		return (-1);
	while (i < 5)
	{
		if (nums[i] != 0)
			return (0);
		i++;
	}
	return (1);
}
int		is_p_last(int *nums, int ind)
{
	int i;
	int f;

	f = 0;
	i = ind + 1;
	if (i >= 5)
		return (-1);
	while (i < 5)
	{
		if (nums[i] != 0)
			f++;
		i++;
	}
	return ((f == 1) ? 1 : 0);
}

char		*to_str(int *nums)
{
	int	i;
	char	*res;
	char	*t_res;
	char	suffs[][10] = {" year", " day", " hour", " minute", " second"};

	i = 0;
	res = malloc(1);
	res[0] = '\0';
	while (i < 5)
	{
		if (nums[i] != 0)
		{
			add_to_str(&res, ft_itoa(nums[i]));
			add_to_str_p(&res, suffs[i]);
			if (nums[i] > 1)
				add_to_str_p(&res, "s");
			if (is_p_last(nums, i) == 1)
			{
				add_to_str_p(&res, " and ");
			}
			else if (is_last(nums, i) == 0)
			{
				add_to_str_p(&res, ", ");
			}
		}
		i++;
	}
	return (res);
}



char *formatDuration (int n)
{
	int	*nums;
	char	*res;

	if (n == 0)
	{
		res = malloc(4);
		res[0] = 'n';
		res[1] = 'o';
		res[2] = 'w';
		res[3] = '\0';
		return (res);
	}
	nums = separate_time(n);
	res = to_str(nums);
	free(nums);
	return (res);
}

int		main(int argc, char **argv)
{
	char *str;

	str = formatDuration(atoi(argv[1]));
	printf("%s\n",str );
	free(str);
}
