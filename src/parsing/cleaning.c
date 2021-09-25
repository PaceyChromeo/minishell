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

static int	count_separators(char *s)
{
	int	i;
	int	separators;

	i = 0;
	separators = 0;
	while (s[i])
	{
		if (s[i] == 60 || s[i] == 62 || s[i] == 124)
			separators++;
		i++;
	}
	return (separators * 2);
}

static int	is_separator(char c)
{
	if (c == 60 || c == 62 || c == 124)
		return (1);
	return (0);
}

char	*trim_str(char *s)
{
	char	*trim;
	int		i;
	int		j;

	trim = malloc(sizeof(*trim) * (ft_strlen(s) + count_separators(s)) + 1);
	if (!trim)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == ' ' && s[i + 1] == ' ')
		{
			trim[j++] = s[i++];
			while (s[i] == ' ')
				i++;
		}
		if ((s[i]) != ' ' && is_separator(s[i + 1]))
		{
			trim[j++] = s[i++];
			trim[j++] = ' ';
		}
		if ((s[i]) != ' ' && is_separator(s[i - 1]))
			trim[j++] = ' ';
		trim[j] = s[i];
		j++;
		i++;
	}
	trim[j] = '\0';
	return (trim);
}
