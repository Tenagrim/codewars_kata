#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long	ull;

ull				fibonacci(int n)
{
	ull cur;
	ull prev;
	ull prev_prev;
	int i;

	prev_prev = 1;
	prev = 1;
	i = 2;
	n--;
	if (n <= 0)
		return (0);
	else if (n == 1 || n == 2)
		return (1);
	else
	{
		cur =0;
		while (i < n)
		{
			cur = prev_prev + prev;
			i++;
			prev_prev = prev;
			prev = cur;
		}
		return (cur);
	}
}

ull				get_susp(int n)
{
	return (fibonacci(n + 1) * fibonacci(n));
}

unsigned long long*		productFib(ull prod)
{
	int i;
	ull *res;

	res = malloc(sizeof (ull) * 3);
	i = 1;
	while (1)
	{
		if (get_susp(i) >= prod)
		{
			res[0] = fibonacci(i);
			res[1] = fibonacci(i + 1);
			res[2] = (get_susp(i) == prod) ? 1 : 0;
			return (res);
		}
		i++;
	}
}

int				main(int argc, char **argv)
{
	ull	*res = productFib(atoi(argv[1]));

	printf("%lld    %lld    %lld\n", res[0], res[1], res[2]);
}
