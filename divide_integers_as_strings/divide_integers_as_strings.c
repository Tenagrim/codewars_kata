#include <stdlib.h>
#include <stdio.h>

#define FRONT	1
#define BACK	2

typedef struct	s_int_pair
{
	int	a;
	int	b;
}		t_int_pair;

void		free_if(char **str)
{
	if(str != NULL)
	{
		free(*str);
		*str = NULL;
	}
}

int		ft_strlen(char *str)
{
	int count = 0;
	if(!str)
		return (0);
	while(str[count] != '\0')
		count++;
	return (count);
}

int		ft_strcmp(char *s1, char *s2)
{
	if(s1 == NULL && s2 == NULL)
		return 0;
	if(s1 == NULL)
		return -1;
	if(s2 == NULL)
		return 1;

	while (*s1 != '\0' &&*s2 != '\0' && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

int		ft_num_strcmp(char *s1, char *s2)
{
	t_int_pair	len;
	len.a = 	ft_strlen(s1);
	len.b = 	ft_strlen(s2);
	if(len.a < len.b)
		return -1;
	if(len.a > len.b)
		return 1;
	if(s1 == NULL && s2 == NULL)
		return 0;
	if(s1 == NULL)
		return -1;
	if(s2 == NULL)
		return 1;

	while (*s1 != '\0' &&*s2 != '\0' && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

void		push(char **dest, char *add, int mode)
{
	t_int_pair len;
	char	*res;
	
	len.a = ft_strlen(*dest);
	len.b = ft_strlen(add);
	res = malloc(sizeof(char) *(len.a + len.b + 1));	
	res[len.a + len.b] = '\0';
	if (mode == BACK)
	{
		for(int i = 0; i < len.a; i++)
			res[i] = dest[0][i];
		for(int i = 0; i < len.b; i++)
			res[i+len.a] = add[i];
	}
	else if (mode == FRONT)
	{
		for(int i = 0; i < len.b; i++)
			res[i] = add[i];
		for(int i = 0; i < len.a; i++)
			res[i + len.a] = dest[0][i];
	}
	free_if(dest);
	*dest = res;
}


char		*zero_str(int size)
{
	char *res = malloc(sizeof(char) * size + 1);
	res[size] = '\0';
	for(int i = 0; i < size; i++)
		res[i] = '0';
	return (res);
}

void		swap_c(char **a, char **b)
{
	char *tmp = *a;
	*a = *b;
	*b = tmp;
}

void		swap_i(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void		left_shift(char *str)
{
	int i;

	i = 1;
	while(str[i] != '\0')
	{
		str[i - 1] = str[i];
		i++;
	}
	str[i-1] = '\0';
}

char		*mult (char *a, char *b)
{
	char		*res;
	char		*up_register;
	t_int_pair	len;
	int		res_len;
	int		tmp;
	int		res_ptr;
	int		k;
	if(ft_strcmp(a,b) < 0)
		swap_c(&a,&b);
	len.a = ft_strlen(a);
	len.b = ft_strlen(b);
	up_register = zero_str(len.a);
	res_len = len.a + len.b; 
	res = zero_str(res_len);
	for(int i = 0; i < len.b; i++)
	{
		for(int j = 0; j < len.a; j++)
		{
			tmp = (a[len.a - j -1] - '0') * (b[len.b - i - 1] - '0'); 
			res_ptr = res_len - i - j - 1;
			tmp += res[res_ptr] - '0';
			res[res_ptr] = (tmp % 10) + '0';
			k = res_ptr - 1;
			res[k] = res[k] + (tmp / 10);
			while(res[k] > '9')
			{
				res[k] = ((res[k] - '0') % 10) + '0';
				res[k - 1] = res[k - 1] + 1;
				k--;
			}
			//printf("%s\n", res);
		}
	}
	if(res[0] == '0')
		left_shift(res);
	return (res);
}

char	*get_head(char *str,int n)
{
	char	*res = malloc(sizeof(char) * n + 1);
	int	i = 0;
	res[n] = '\0';
	while(str[i] != '\0' && i < n)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return res;
}

int	ft_str_n_cmp(char *s1, int n, char *s2)
{
	int i = 0;
	
	while (*s1 != '\0' &&*s2 != '\0' && (*s1 == *s2) && i < n)
	{
		s1++;
		s2++;
		i++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
	
}

char	*ft_strdup(char *str)
{
	int	len = ft_strlen(str);
	char	*res = malloc(sizeof(char) * len + 1);
	res[len] = '\0';
	for(int i = 0; i < len; i++)
		res[i] = str[i];
	return(res);
}

char	*sub(char *a, char *b)
{
	t_int_pair	len;
	int		i;
	char		*res;
	int		k;

	len.a = ft_strlen(a);
	len.b = ft_strlen(b);
	res = ft_strdup(a);
	i = 0;
	while(i < len.b)
	{
		//printf("%d\n", i);
		k = len.a - 1 - i;
		res[k] = res[k] - b[len.b-1-i] + '0';
		while(res[k] < '0')
		{
			res[k] = res [k] + 10;
			res[k-1] = res[k-1] - 1;
			k--;
		}
		i++;
	}
	while(res[0] == '0')
		left_shift(res);
	if(res[0] == 0)
		res[0] = '0';
	return res;
}

int	count_back_zeros(char *a)
{
	int		len;
	int		min_len;
	int		count;
	len = ft_strlen(a);
	count = 0;
       	for(int i = len - 1; i >=0; i--)
	{
		if(a[i] != '0' )
			return count;
		count++;
	}
	return count;
}

char	**divide_strings(char *a, char *b)
{
	char		**res = malloc(2 * sizeof(char *));
	t_int_pair	len;
	char		*head;
	int		tail = 0;
	char		*res_part;
	char		*sub_res = NULL;
	char		*tmp;
	int		back_zeros;
	
	res[0] = NULL;
	res[1] = NULL;
	len.a = ft_strlen(a);
	len.b = ft_strlen(b);
	back_zeros = count_back_zeros(a);
	if(ft_num_strcmp(a,b) < 0)
	{
		push(&(res[0]), "0", BACK);
		res[1] = ft_strdup(a);
		return res;
	}
	head = get_head(a,len.b);
	if(ft_strcmp(head, b) < 0)
	{
		free_if(&head);
		head = get_head(a,len.b + 1);
	}
	tail = ft_strlen(head); 
	res_part = malloc(sizeof(char) * 2);
	while (1)
	{
	res_part[0] = '1';
	res_part[1] = '\0';
	free_if(&sub_res);
	sub_res = ft_strdup(b);
//	printf("zeros: [%d]\n", count_back_zeros(a,b));
	while (ft_num_strcmp(sub_res,head) < 0 &&res_part[0] <= '9')
	{
		free_if(&sub_res);
		res_part[0] = res_part[0] + 1;
		sub_res = mult(b,res_part);
		printf("head: [%s] sub_res: [%s] res_part: [%s] tail: [%d]\n",head ,sub_res, res_part,tail );
  	}
	if(ft_num_strcmp(sub_res,head) != 0)
	{
		res_part[0] = res_part[0] - 1;
	
		tmp = sub_res;
		sub_res = sub(sub_res,b);
		free_if(&tmp);
	}

	printf("|| head: [%s] sub_res: [%s] res_part: [%s] tail: [%d]\n",head ,sub_res, res_part,tail );
	
	tmp = head;
	head = sub(head,sub_res);
	free_if(&tmp);

	push(&(res[0]), res_part, BACK);
	

	while(tail < len.a && ft_num_strcmp(head, b) < 0)
	{
		res_part[0] = a[tail];
		tail++;
		if(ft_strcmp(head,"0") == 0 && len.a-tail <= back_zeros)
			push(&(res[0]), res_part, BACK);
		else
			push(&head, res_part, BACK);

	}
	
	

	if (ft_num_strcmp(head, b) <= 0 && tail == len.a)
	{
		if(ft_strcmp(head,"") == 0)
			push(&head,"0",BACK);
		res[1] = head;
		free_if(&res_part);
		free_if(&sub_res);
		return res;
	}
	}
	//free_if(&head);
	
	return res;
}

int main(int ac, char **av)
{
	char **res = divide_strings(av[1], av[2]);

	//push(&str, av[1], BACK);
	//printf(">>%s<<\n", sub(av[1], av[2]));
	//printf(">>%s<<\n", mult(av[1], av[2]));
	printf(">>%s<<\n",res[0]);
	printf(">>%s<<\n",res[1]);

	//char *a= "qwerty";
	//char  *b = ft_strdup(a);
	//char  *c = ft_strdup(b);
	//printf("%s  %s  %s\n",a,b,c);
	//free_if(&b);
	//printf("%s  %s  %s\n",a,b,c);

	//printf("%s\n", str);
}
