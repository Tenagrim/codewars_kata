#include <stdio.h>
#include <stdlib.h>

char *to_hex(int n)
{
	char *digits = "0123456789ABCDEF";
	char *res = malloc(sizeof(char) *2);
	char c;
	n = n > 255 ? 255 : n;
	n = n < 0 ? 0 : n;
	res[0] = digits[n / 16];
	res[1] = digits[n % 16];
//	printf("%d  %d|%d", n,n/16, n%16);
	return res;
}

void project(char *str, char *dest, int offset)
{
	dest[0 + offset] = str[0];
	dest[1 + offset] = str[1];
	free(str);
}

int rgb(int r, int g, int b, char *output)
{
   char *tmp = to_hex(r);
   project(tmp, output, 0);
   tmp = to_hex(g);
   project(tmp, output, 2);
   tmp = to_hex(b);
   project(tmp, output, 4);
   free(tmp);

   return 0; 
}

int main(int ac, char **av)
{
	char *res = malloc(6);

	rgb(atoi(av[1]),atoi(av[2]),atoi(av[3]), res);

	printf("%s\n", res);
	return (0);
}
