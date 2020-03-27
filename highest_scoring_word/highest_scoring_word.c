/*
** @param str: a C-string containing only lowercase letters and spaces (' ')
** @return:    a C-string allocated on the heap containing the highest scoring word of str
*/
#include <stdio.h>
#include <stdlib.h>

int	ft_strlen(const char *str)
{
	return (*str) ? ft_strlen(++str) + 1 : 0;
}

int	ft_wordlen(const char *str, const char e)
{	
	return (*str != e && *str != '\0') ? ft_wordlen(++str, e) + 1 : 0;
}

int	score_word(char *str, int count)
{
	int res;
	int i;

	i = 0;
	res = 0;
	while (i < count)
	{
		res += str[i] - 96;
		i++;
	}
	return (res);
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

char	*copy_n_word(char *str, int n)
{
	int	i;
	
	i = 0;
	while (*str == ' ')
		str++;
	while (i < n)
	{
		while (*str != ' ')
			str++;
		while (*str == ' ')
			str++;
		i++;
	}
	return (copy_word(str, ft_wordlen(str, ' ')));
}

int	is_empty(const char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

char 	*highestScoringWord(const char *str)
{
	int	h_word;
	int	h_score;
	char	*h_w_pointer;
	char	*temp_str;
	int	temp_score;
	int	i;
	int	j;

	if (is_empty(str))
		return (NULL);
	i = 0;
	j = 0;
	h_word = 0;
	h_score = 0;
		printf("!!!!!!\n");
	while (str[j] == ' ')
		j++;
	while (str[j])
	{
		printf("!!!!!!\n");
		temp_score = score_word((char *)str + j, ft_wordlen(str + j,' '));
		if (temp_score > h_score)
		{
			h_score = temp_score;
			h_word = i;
		}
		printf("!!!!!!\n");
		j += ft_wordlen(str + j, ' ');
		while (str[j] == ' ')
			j++;
		printf("i = %d  j = %d str[j] |%c|  h_word = %d \n", i, j, str[j], h_word);
		i++;
	}
	return (copy_n_word((char *)str, h_word));
}



int main(int argc, char **argv)
{
	char	*res;

	res = highestScoringWord(argv[1]);
	printf("%s ", res);
	printf("= %d\n", score_word(res, ft_wordlen(res, ' ')));
}
