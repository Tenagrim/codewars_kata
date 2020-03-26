#include <stdlib.h>
#include <stdio.h>

long long tribonacci_one(const long long signature[3], size_t n)
{

	if (n == 0)
		return (0);
	else if (n <=3)
	{
		return (signature[n - 1]);
	}
	else
	{
	return (tribonacci_one(signature, n-3) + tribonacci_one(signature, n-2) + tribonacci_one(signature, n-1));
	}

}




long long *tribonacci(const long long signature[3], size_t n)
{
	long long *res;
	int i;

	if (n == 0)
		return (NULL);
	i = 0;
	res = malloc(sizeof(long long) * n);

	while (i + 1 <= n)
	{
		if (i <= 2)
			res[i] = signature[i];
		else
			res[i] = res[i - 3] + res[i - 2] + res[i - 1]; 
		i++;
	}
	return (res);
}
int		main(int argc, char **argv)
{
	long long *res;
	long long sig[] = {1,1,1};
	int n = atoi(argv[1]);


	res = tribonacci(sig, n);

	for(int i = 0; i < n; i++)
		printf("%lld ", res[i]);
	printf("\n");
}
