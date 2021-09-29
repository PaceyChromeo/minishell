#include "minishell.h"

char lexer_quote(char *line)
{
	int		single;
	int		d_ouble;
	char	first = 'a';
	char	last = 'a';
	int		i;

	single = 0;
	d_ouble = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == 39)
		{
			if (d_ouble == 0 && single == 0)
			{
				first = 39;
				single++;
			}
			else if (d_ouble != 0 || single != 0)
			{
				last = 39;
				single++;
			}
		}
		if (line[i] == 34)
		{
			if (single == 0 && d_ouble == 0)
			{
				first = 34;
				d_ouble++;
			}
			else if (d_ouble != 0 || single != 0)
			{
				last = 34;
				d_ouble++;
			}
		}
		i++;
	}
	if (first == last)
	{
		if (first == 39 || first == 34)
		{
			if (first == 39 && single % 2 == 0)
				return (first);
			else if (first == 34 && d_ouble % 2 == 0)
				return (first);
		}
		else 
			return ('x');
	}
	return ('!');
}
