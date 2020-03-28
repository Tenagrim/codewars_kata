#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

int	ft_strlen(const char *str)
{
	return (*str) ? ft_strlen(++str) + 1 : 0;
}

char	off_char(char src)
{
	int	offset;
	char	res;
	res = src + 13;
	if (src >= 'A' && src <= 'Z')
	{
		if (res > 'Z')
			res -= 26; 
	}
	else if (src >= 'a' && src <= 'z')
	{
//		printf(" src = %c  %d   |%d  ,%c, z: %d\n",src,src, res, res, 'z');
		if (res <= 0)
			res += 256 - 26;
		else if (res > 'z')
			res -= 26; 
//		printf("===========src = %c  %d   |%d  ,%c, z: %d\n",src,src, res, res, 'z');
	}
	else
		res = src;
	return (res);
}



char	*rot13(const char *src)
{
	char	*res;
	int	len;
	int	i;

	i= 0;
	len = ft_strlen(src);
	res = malloc(sizeof(char) * len + 1);
	while (src[i])
	{
		res[i] = off_char(src[i]);
	//	printf("%c\n", res[i]);
	       i++;	
	}
	res[i] = '\0';
	return (res);
}

int	main(int argc, char **argv)
{
	char *res;

	res = rot13(argv[1]);
	printf("%s\n", res);
}
