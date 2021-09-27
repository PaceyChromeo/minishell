#include <stdlib.h>

/* size_t	ft_strlen_redir(const char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '<' || str[i] == '>')
		{
			if (str[i--] != ' ' && i != 0)
				j++;
			if (str[i++] == '<' || str[i++] == '>')
			{
				while (str[i++] == '<' || str[i++] == '>')
				{ 
				}
				if (str[i] != ' ')
					j++;
			}
		}
		i++;
	}
	return (i += j);
}*/

char	*redir(char *str)
{
	char 	*copy = NULL;
	int		i;
	int		j;
	int		checker1;
	int		checker2;
	int		space;

	i = 0;
	j = 0;
	checker1 = 0;
	checker2 = 0;
	space = 0;
	printf("%ld\n", ft_strlen_redir(str));
	copy = malloc(sizeof(char) * ft_strlen_redir(str) + 1);
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
		{
			space++;
			copy[j] = str[i];
		}
		else if (str[i] == '<' || str[i] == '>')
		{
			if (i != 0 && space == 0 && checker1 == 0 && checker2 == 0)
			{
				copy[j] = ' ';
				j++;
			}
			copy[j] = str[i];
			if (i == '>')
				checker2++;
			else
				checker1++;
			space = 0;
			if (checker1 == 3)
				checker1 = 0;
			if (checker2 == 3)
				checker2 = 0;
		}
		else
		{
			if (i != 0)
			{
				if (str[i-1] == '<' || str[i-1] == '>')
				{
					copy[j] = ' ';
					j++;
				}
			}
			copy[j] = str[i];
			space = 0;
			checker1 = checker2 = 0;	
		}
		i++;
		j++;
	}
	copy[j] = '\0';
	return (copy);
}