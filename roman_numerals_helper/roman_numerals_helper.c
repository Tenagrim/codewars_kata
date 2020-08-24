/*42 school - style  )*/
int	get_num(char r_dgit)
{
	int	values[] = { 1 ,  5 , 10 , 50 , 100, 500, 1000};
	char	keys[] =   {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
	int i;

	i= 0;
	while (i < 7)
	{
		if (keys[i] == r_dgit)
			return(values[i]);
		i++;
	}
	return (0);
}

int	from_roman(char* roman)
{
	int res;
	int i;

	res = 0;
	i = 0;
	while (roman[i] != 0)
	{
		if (roman[i + 1] && get_num(roman[i + 1]) > get_num(roman[i]))
		{
			res += get_num(roman[i + 1]) - get_num(roman[i]);
			i += 2;
		}
		else
		{
			res += get_num(roman[i]);
			i += 1;
		}
	}
  	return (res);
}

void	to_roman(int number, char* destination)
{
	int	values[] = { 1 ,  5 , 10 , 50 , 100, 500, 1000};
	char	keys[] =   {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
	int	i;
	int	c;

	i = 6;
	c = 0;
	while (i >= 0)
	{
		while (number / values[i] != 0 && number >= 5)
		{
				printf("%d  %d  %d\n", number, values[i], number / values[i]);
			if (number / values[i - 1] == 9 && (i == 5 || i == 3 || i == 1))
			{
				i--;
				destination[c] = keys[i];
				destination[c + 1] = keys[i + 2];
				c += 2;
				number -= values[i + 2] - values[i];
			}
			else if (number / values[i] == 4 && ( i == 4 || i == 2))
			{
				destination[c] = keys[i];
				destination[c + 1] = keys[i + 1];
				c += 2;
				number -= 4 * values[i];
			}
			else
			{
				destination[c] = keys[i];
				number -= values[i];
				c++;
			}
		}
		i--;
	}
	if (number == 4)
	{
		
		destination[c] = 'I';
		destination[c + 1] = 'V';
		number -= 4;
		c += 2;
	}
	while (number > 0)
	{
		destination[c] = 'I';
		number--;
		c++;
	}
	destination[c] = '\0';

}

int	main(int argc, char **argv)
{
	char buff[256];
	to_roman(atoi(argv[1]), buff);
	printf("  to roman: %d    :%s\n",atoi(argv[1]), buff);
	//printf("from roman: CDLXXXV : %d\n",from_roman("CDLXXXV"));
	printf("from roman:  CMXCIX: %d\n",from_roman("CMXCIX"));
}
