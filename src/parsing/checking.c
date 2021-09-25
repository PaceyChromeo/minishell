#include "minishell.h"

int	count_pipe(char *line)
{
	int	i;
	int	pipe;

	i = -1;
	pipe = 0;
	while(line[++i])
	{
		if (line[i] == 34 && line[i + 1] != 34)
		{
			i++;
			while (line[i] != 34 && line[i])
				i++;
		}
		if (line[i] == 39 && line[i + 1] != 39)
		{
			i++;
			while (line[i] != 39 && line[i])
				i++;
		}
		if (line[i] == '|')
			pipe++;
	}
	return (pipe);
}

char	*trim_str(char *s)
{
	char	*trim;
	int		i;

	trim = malloc(sizeof(*trim) * ft_strlen(s) + 1);
	if (!trim)
		return (NULL);
	i = -1;
	while (s[++i])
		trim[i] = s[i];
	trim[i] = '\0';
	return (trim);
}

