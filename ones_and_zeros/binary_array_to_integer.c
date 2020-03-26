#include <stddef.h>
#include <stdio.h>
#include <stdlib.h> 

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

unsigned binary_array_to_numbers(const unsigned *bits, size_t count)
{
	int i;
	unsigned res;

	res = 0;
	i = 0;
	while (i < count)
	{
	//	printf("%d *  %d  = %d |  ",bits[count - i -1], ft_iterative_pow(2,i), bits[count - i -1]* ft_iterative_pow(2,i));
		res += (bits[count - i - 1] * ft_iterative_pow(2, i));
		i++;
	}
//	printf("\n");
	return (res);
}

int main(int argc, char **argv)
{
	unsigned *bits = malloc(sizeof(unsigned) * (argc - 1));

	for (int i = 0 ; i < argc -1; i++)
		bits[i] = atoi(argv[i + 1]);
	printf("%d\n",(int)binary_array_to_numbers(bits, argc - 1));
}
