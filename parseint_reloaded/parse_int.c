#include <stdio.h>
#include <stdlib.h>

int		ft_strcmp(char *str1, char *str2)
{
	while(*str1 != '\0' && *str2 != '\0' && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return (*(unsigned char *)str1 - *(unsigned char *)str2);
}

unsigned char	is_space(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '-')
		return (1);
	else
		return (0);
}

int	ft_wordlen(const char *str)
{	
	return (is_space(*str) != 1 && *str != '\0') ? ft_wordlen(++str) + 1 : 0;
}

int		ft_strlen(const char *str)
{
	return (*str) ? ft_strlen(++str) + 1 : 0;
}

char	*copy_word(char *begin, int len)
{
	int	i;
	char	*res;

	i = 0;
	res = malloc(sizeof(char) * len + 1);
	while (i < len)
	{
		res[i] = begin[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
/*
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
*/
/*
int		is_substr(char *src, char *find)
{
	if (*find == '\0')
		return (1);
	while (*src != *find && *src != '\0')
		src ++;
	if (*src == '\0')
		return (0);
	while (*src == *find && *find != '\0')
	{
		src++;
		find++;
	}
	if (*find != '\0')
		return (0);
	else
		return (1);
}
*/
char	*copy_n_word(char *str, int n)
{
	int	i;
	
	i = 0;
	while (is_space(*str) == 1)
		str++;
	while (i < n)
	{
		while (is_space(*str) != 1)
			str++;
		while (is_space(*str) == 1)
			str++;
		i++;
	}
	return (copy_word(str, ft_wordlen(str)));
}

/*
char		*cut_word(char *src, char *end)
{
	int	i;
	int	j;
	char	*res;
	int	begin_of_end;

	i = 0;
	j = 0;
	printf("!!!!!!\n");
	res = ft_copy_str(src);
	while (src[i] != end[0] && src[i] != '\0')
		i++;
	begin_of_end = i;
	printf("===%s\n", src);
	if (src[i] == '\0')
		return (NULL);
	i = 0;
	while (end[j] != '\0' && src[i] != '\0')
	{
		if (src[i] != end[j])
			return (NULL);
		i++;
		j++;
	}
	res[begin_of_end] = '\0';
	return (res);
}
*/

int				count_words(char *str)
{
	int res;
	int prev_ch_is_letter;

	if (*str == '\0')
		return (0);
	res = 0;
	prev_ch_is_letter = 0;
	while (*str != '\0')
	{
		if (is_space(*str) == 1)
		{
			prev_ch_is_letter = 0;
			str++;
		}
		else
		{
			if (prev_ch_is_letter == 0)
				res++;
			prev_ch_is_letter = 1;
			str++;
		}
	}
	return (res);
}

int		parse_mul(char * number)
{
	if (!ft_strcmp(number, "hundred"))
		return (100);
	else if (!ft_strcmp(number, "thousand"))
		return (1000);
	else if (!ft_strcmp(number, "million"))
		return (1000000);
	else if (!ft_strcmp(number, "billion") ||
			!ft_strcmp(number, "milliard"))
		return (1000000000);
	else
		return (0);
}

int		parse_ty(char *number)
{
	char	nums[][15] = {"twenty", "thirty", "forty", "fifty",
	"sixty", "seventy", "eighty", "ninety"};
	int	i;
	
	int	res;
	i = 0;
	while (i < 8)
	{
		if (!ft_strcmp(nums[i], (char *)number))
			return ((i + 2) * 10);
		i++;
	}
	return (parse_mul((char *)number));
}

int		parse_digit(const char *number)
{
	char	nums[][15] = {"zero", "one", "two", "three",
	"four", "five", "six", "seven", "eight", "nine", "ten",
	"eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen",
	"seventeen", "eighteen", "nineteen"};
	int	i;
	
	int	res;
	i = 0;
	while (i < 20)
	{
		if (!ft_strcmp(nums[i], (char *)number))
			return (i);
		i++;
	}
	return (parse_ty((char *)(number)));
}

int		mul_num(int num, int **mul)
{
	int ind;

	if (num == 1000000000)
		ind = 3;
	else if (num == 1000000)
		ind = 2;
	else if (num == 1000)
		ind = 1;
	else if (num == 100)
		ind = 0;
	else 
		return (0);
	if (mul[0][ind] == 0)
	{
		mul[0][ind] = 1;
		return (0);
	}
	else
		return (1);
}

int		next_mul(char *number, int c_word, int w_count)
{
	char	*word;
	int	i;
	int	p_word;

	i = c_word + 1;
	while (i < w_count)
	{
		word = copy_n_word(number, i);
		p_word = parse_digit(word);
		free(word);
		if (p_word >= 100)
			return (p_word);
		i++;
	}
	return (1);
}

long		parse_int(const char* number)
{
//	printf("%d\n", count_words((char *)number));
//	printf("%s\n", copy_n_word((char *)number, count_words((char *)number) - 1));
	
	int	w_count;
	int	i;
	long	res;
	long	sub_res;
	char	*cur_word;
	int	p_word;
	int	c_mul;
	int	n_mul;

	w_count = count_words((char *)number);
	if (w_count == 0)
		return (0);
	sub_res = 0;
	res = 0;
	i = 0;
	//printf ("w_count: %d\n", w_count);
	while (i < w_count)
	{
		cur_word = copy_n_word((char *)number, i);
	//	printf("%d) %s\n", i, cur_word);
		p_word = parse_digit(cur_word);
		free(cur_word);
		if (p_word < 100)
		{
			sub_res += p_word;
		}
		else
		{
			c_mul = p_word;
			n_mul = next_mul((char *)number, i, w_count);
			c_mul = (n_mul > c_mul) ? n_mul * c_mul : c_mul;
			sub_res *= c_mul;
			res += sub_res;
			sub_res = 0;
		}
		i++;
	}
	if (sub_res != 0)
		res += sub_res;
	return (res);
}

int		main(int argc, char **argv)
{
	char *res;

//	res = cut_word("twenty", "ty");
	printf("%ld\n", parse_int(argv[1]));
//	if (res !=NULL)
//		printf("%s\n", res);
//	else
//		printf("NULL\n");
}
