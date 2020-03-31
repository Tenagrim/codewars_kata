#include <stdlib.h>
#include <stdio.h>


#include <stdint.h>

int digits(uint64_t n)
{
	int res;

	if (n == 0)
		return (1);
	res = 0;
	while (n > 0)
	{
		n /= 10;
		res++;
	}
 	return (res);
}

int	main(int argc,char **argv)
{
	printf("%s   %d\n", argv[1], digits((uint64_t)(atoi(argv[1]))));
}
