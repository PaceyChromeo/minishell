#include "minishell.h"

int check_quote(char *line)
{
    int single;
    int d_ouble;
    char first;
    char last;
    int i;

    single = 0;
    d_ouble = 0;
    i = 0;
    first = last = 'p';
    while (line[i])
    {
        if (line[i] == 39)
        {
            if (single == 0 && d_ouble == 0)
                first = 's';
            else
            {
                last = 's';
            }
            single++;
            if (first == 's')
            {
                while (line[i])
                {
                    i++;
                    if (line[i] == 39)
                    {
                        last = 's';
                        single = d_ouble = 0;
                        break;
                    }
                }
            }
        }
        else if (line[i] == 34)
        {
            if (single == 0 && d_ouble == 0)
                first = 'd';
            else
            {
                last = 'd';
            }
            d_ouble++;
            if (first == 'd')
            {
                while (line[i])
                {
                    i++;
                    if (line[i] == 34)
                    {
                        last = 'd';
                        d_ouble = single = 0;
                        break;
                    }
                }
            }
        }
        i++;
    }
    if (line[i - 1] == '|')
        return (1);
    if (single != 0 || d_ouble != 0)
        return (1);
    else if (first != last)
        return (1);
    else
        return(single);
}


static size_t	ft_strlen_quotes(const char *str)
{
	size_t	i;
	size_t	j;
    int single;
    int d_ouble;
    char first;
    char last;

    single = 0;
    d_ouble = 0;
    i = 0;
    j = 0;
    first = last = 'p';
    while (str[i])
    {
        if (str[i] == 39)
        {
            if (single == 0 && d_ouble == 0)
                first = 's';
            else
            {
                last = 's';
            }
            single++;
            if (first == 's')
            {
                while (str[i])
                {
                    i++;
                    if (str[i] == 39)
                    {
                        last = 's';
                        single = d_ouble = 0;
                        if (str[i + 1] != ' ')
                            j++;
                        break;
                    }
                }
            }
        }
        else if (str[i] == 34)
        {
            if (single == 0 && d_ouble == 0)
                first = 'd';
            else
            {
                last = 'd';
            }
            d_ouble++;
            if (first == 'd')
            {
                while (str[i])
                {
                    i++;
                    if (str[i] == 34)
                    {
                        last = 'd';
                        d_ouble = single = 0;
                        if (str[i + 1] != ' ')
                            j++;
                        break;
                    }
                }
            }
        }
        i++;
    }
    return (i += j);
}


char	*clean_quotes(char *str)
{
	char 	*copy = NULL;
	int		i;
	int		j;
    int     counter;

	i = 0;
	j = 0;
    counter = 0;
	copy = malloc(sizeof(char) * ft_strlen_quotes(str) + 1);
	if (!copy)
		return (NULL);
	while (str[i] != '\0')
	{
        if (str[i] == 39)
        {
            copy[j] = str[i];
            counter++;
            i++;
            j++;
            while (counter < 2)
            {
                copy[j] = str[i];
                if (str[i] == 39)
                    counter++;
                i++;
                j++;
            }
			counter = 0;
            if (str[i] != ' ')
            {
                copy[j] = ' ';
                i--;
            }
            else
            {
                i--;
                j--;
            }
        }
		else if (str[i] == 34)
        {
            copy[j] = str[i];
            counter++;
            i++;
            j++;
            while (counter < 2)
            {
                copy[j] = str[i];
                if (str[i] == 34)
                    counter++;
                i++;
                j++;
            }
			counter = 0;
            if (str[i] != ' ')
            {
                copy[j] = ' ';
                i--;
            }
            else
            {
                i--;
                j--;
            }
        }
		else
		{
			copy[j] = str[i];
            if (str[i] != ' ' && (str[i + 1] == 34 || str[i + 1] == 39) && counter == 0)
            {
                j++;
                copy[j] = ' ';
            }
		}
		i++;
		j++;
	}
	copy[j] = '\0';
	return (copy);
}
