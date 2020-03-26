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

char		*ft_substr(char *src, char *find)
{
	char	*temp_src;
	int	count;
	char	*res;
	int	i;

	i = 0;
	count = 0;	
	if (*find == '\0')
		return (src);
	while (*src != *find && *src != '\0')
		src ++;
	if (*src == '\0')
		return (NULL);
	temp_src = src;
	while (*src == *find && *find != '\0')
	{
		src++;
		find++;
		count++;
	}
	if (*find != '\0')
		return (NULL);
	else
	{
		res = malloc(count + 1);
		src = temp_src;
		while (i < count)
		{
			res[i] = *src;
			i++;
			src++;
		}
		res[i] = '\0';
		return (res);

	}

}

void		ft_push_back(char ***arr, int *size, char *ins)
{
	char	**res;
	int	i;

	i = 0;
	res = (char **)malloc(sizeof(char *) * (*size) + 1);
	while (i < *size)
	{
		res[i] = arr[0][i];
		i++;
	}
	res[*size] = ins;
	*size = *size + 1;
	if (*arr != NULL)
		free(*arr);
	arr[0] = res;
}

int		is_repeat(char **arr, int size, char *find)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (ft_strcmp(arr[i], find) == 0)
			return (1);
		i++;
	}
	return (0);
}

void		ft_swap(char **s1, char **s2)
{
	char *temp;

	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}

void		ft_sort(char **arr, int size)
{
	int i;
	int j;

	if (size <=1)
		return ;
	i = 0;
	while (i < size)
	{
		j = 1;
		while (j < size)
		{
			if (ft_strcmp(arr[j], arr[j - 1]) < 0)
				ft_swap(&arr[j], &arr[j - 1]);
			j++;
		}
		i++;
	}
}

char**		inArray(char* array1[], int sz1, char* array2[], int sz2, int* lg)
{
	char	**res;
	int	i;
	int	j;
	int	k;
	int	res_size;
	char	*sub_str;

	res = NULL;
	res_size = 0;
	i = 0;
	while (i < sz2)
	{
		j = 0;
		while (j < sz1)
		{
			if (is_substr(array2[i], array1[j]))
			{
				sub_str = ft_substr(array2[i], array1[j]);
				if (is_repeat(res, res_size, sub_str) == 0)
					ft_push_back(&res, &res_size, sub_str);
				else
					free (sub_str);
			}
			j++;	
		}
		i++;
	}
	*lg = res_size;
	ft_sort(res, res_size);
	return (res);
}

int		main()
{
	int i;
	int size1;
	int size2;
	int size_res;
	size1 = 3;
	size2 = 5;
	char **arr1 = malloc(sizeof(char *)* size1);
	char **arr2 = malloc(sizeof(char *)* size2);
	
	arr1[0] = "arp";
	arr1[1] = "live";
	arr1[2] = "strong";

	arr2[0] = "lively";
	arr2[1] = "alive";
	arr2[2] = "harp";
	arr2[3] = "sharp";
	arr2[4] = "armstrong";
	
	char **res = inArray(arr1, size1, arr2, size2, &size_res);

	i = 0;
//	ft_push_back(&res, &size, insert);
	while (i < size_res)
	{	
		printf("%s\n", res[i]);
		i++;
	}

}
