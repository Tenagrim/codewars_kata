#include <stdio.h>
#include <stdlib.h>

typedef struct Pair Pair;
struct Pair {
    long long first;
    long long snd;
};

long long	sum_of_seq(long long n)
{
	printf("!!! %lld\n", n);
	long long	res;
	long long	i;

	i = 1;
	res = 0;
	while (i <= n)
	{
		res += i;
		i++;
	}
	return (res);	
}

long long	sum_of_seq_ab(long long n, long long a, long long b)
{
	if (n == 0)
		return (0);
	else if (n != a && n != b)
		return (n + sum_of_seq_ab(n -1, a, b));
	else
		return (sum_of_seq_ab(n -1, a, b));
}

void		push_back(Pair ***res, Pair *ins, int *length)
{
	Pair	**res2;
	int	i;




	if (res[0] == NULL)
	{
		res[0] = malloc(sizeof(Pair *));
		res[0][0] = ins;
		*length =  1;
	}
	else
	{
		i = 0;
		res2 = malloc(sizeof(Pair) * *length + 1);
		while (i < *length)
		{
			res2[i] = res[0][i];
			i++;
		}
		res2[i] = ins;
		free(res[0]);
		res[0] = res2;
		*length = *length + 1;
	}
}

Pair		*new_pair(long long a, long long b)
{
	Pair	*res;

	res = malloc(sizeof(Pair));
	res->first = a;
	res->snd = b;
	return (res);
}

// fill length with the number of pairs in your array of pairs
Pair		**removNb(long long n, int *length)
{
	long long	sum;
	long long	a;
	long long	b;
	Pair		**res;

	a = 1;
	res = NULL;
//	printf("!!!\n");
//	sum = sum_of_seq(n);
	sum = ((double)n / 2) * ((double)n + 1);
//	printf("!!!%lld   %lld\n", n, sum);
	while (a <= n)
	{
//		if (a % 1000 ==0)
//	printf("!!! %lld\n",a);
	//	b = n/2;
		b = (sum - a) / (a + 1);
	//	while (b <= n)
	//	{
			//sum = sum_of_seq_ab(n,a,b);
			if (a * b == sum - (a + b) && b <= n)
			{
				push_back(&res, new_pair(a,b),length);
			//	printf("===%lld   %lld\n", res[0]->first, res[0]->snd);
			}
	//		b++;
	//	}
		a++;
	}
	return (res);
}

void		test(long long n)
{
	int	size;
	Pair	**res;
	int	i;

	i = 0;
	size = 0;
	res = removNb(n, &size);
	if (size != 0)
	{
		printf("size: %d, n = %lld \t ", size, n);

	while (i < size)
	{
	//	printf("%d  ", i);
		printf("{%lld ", res[i]->first);
		printf("%lld} \t  ", res[i]->snd);
		free(res[i]);
		i++;
	}
	printf("\n");
	free(res);
	}
}

void		t_test(int n)
{
	Pair	**res;
	int	i;
	int	size;

	size = 0;
	i = 0;
	res = NULL;
	while (i < n)
	{
		push_back(&res, new_pair(i, i * i), &size);
		i++;
	}
	i = 0;
	while (i < size)
	{
		printf("{%lld ", res[i]->first);
		printf("%lld} \t  ", res[i]->snd);
		free(res[i]);
		i++;
	}
	free(res);
}

int		main(int argc, char **argv)
{
	
	int i;
	int bord;

	i = atoi(argv[1]);
	bord = atoi(argv[2]);
	while(i < bord)
	{
		test(i);
		i++;
	}

//	t_test(atoi(argv[1]));
}
