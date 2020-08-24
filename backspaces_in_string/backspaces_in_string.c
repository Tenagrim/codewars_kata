#include <stdlib.h>

#include <stdio.h>

int ft_strlen(char *str)
{
	int count;

	count = 0;
	while (str[count] != '\0')
		count++;
	return (count);
}

int count_remains(const char *s)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '#')
			count--;
		else 
			count++;
		i++;
	count = count < 0 ? 0 : count;
	}
	return (count);
}

char *strclr(const char *s)
{
    char	*res;
    int		len;
    int		i;
    int		j;
    int		back;

    len = count_remains(s);
    res = malloc(sizeof(char) * (len + 1));
    res[len] = '\0';
    i = len - 1;
    back = 0;
    j = ft_strlen((char*)s) - 1;
    //printf("len %d\n", len);
    while (j >= 0)
    {
	    if (s[j] == '#')
		    back++;
	    else if (back == 0)
	    {
	    	res[i] = s[j];
	    //printf("%c  %d\n", s[j], res[i]);
		i--;
	    }
	    else
		    back--;
	    //printf("j: %d |%s|\n",j, res);
	    j--;
    }
	return (res);
}

int main(int argc, char **argv)
{
	char *tmp;

	tmp = strclr("########");
	printf("%s\n", tmp);
	//free(tmp);
}
