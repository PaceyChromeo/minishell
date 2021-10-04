
#include "minishell.h"

static int	nbr_strings(char const *line, char c)
{
   	int single;
    int d_ouble;
    char first;
    char last;
    int i;
	int	nbr;
	int cles;

    single = 0;
    d_ouble = 0;
    i = 0;
	nbr = 0;
	cles = 0;
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
				i++;
                while (line[i] != 39)
                {

                    i++;
				}
				last = 's';
				single = d_ouble = 0;
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
				i++;
                while (line[i] != 34)
                {
                    i++;
				}
				last = 'd';
				d_ouble = single = 0;
            }
        }
		if (line[i] == c)
		{
			cles = 0;
		}
		else if (cles == 0)
		{
			cles = 1;
			nbr++;
		}
        i++;
    }
	return (nbr);
}

static int	index_pipe(char const *line, char c, int i)
{

    int single;
    int d_ouble;
    char first;
    char last;

    single = 0;
    d_ouble = 0;
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
				i++;
                while (line[i] != 39)
                {
                    i++;
				}
				last = 's';
				single = d_ouble = 0;
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
				i++;
                while (line[i] != 34)
                {
                    i++;
				}
					last = 'd';
					d_ouble = single = 0;
			}
        }
		else if (line[i] == c)
			return (i);
        i++;
    }
	return (i);
}

static char	**ft_copy_strings(char const *s, char **dst, char c, int total)
{
	int	i;
	int	j;
	int	k;
	int	index;

	i = 0;
	j = 0;
	while (s[i] != '\0' && j < total)
	{
		index = 0;
		k = 0;
		index = index_pipe(s, c, i);
		dst[j] = (char *)malloc(sizeof(char) * (index - i) + 1);
		if (!dst[j])
			return (NULL);
	//	printf("len : %d\n", index - i);
		if ((index - i) == 0)
		{
			i++;
			free (dst[j]);
			dst[j] = NULL;
			continue;
		}
		
		while (i < index && s[i] != '\0')
			dst[j][k++] = s[i++];
		dst[j][k] = '\0';
		j++;
	}
	dst[j] = 0;
	return (dst);
}

char	**ft_split_space(char *s, char c)
{
	char	**dst;
	int		total;

    total = 0;
	if (!s)
		return (NULL);
	total = nbr_strings(s, c);
//	printf("Total strings: %d\n", total);
	dst = (char **)malloc(sizeof(char **) * (total + 1));
	if (!dst)
		return (NULL);
	return (ft_copy_strings(s, dst, c, total));
}
