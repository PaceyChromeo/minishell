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

static size_t	ft_strlen_redir(const char *str)
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
					if (str[i] != ' ')
						j++;
				}
			}
		}
		i++;
	}
	return (i += j);
}

char	*str_trim(char *str)
{
	char 	*copy = NULL;
	int		i;
	int		j;
	int		redir_left;
	int		redir_right;
	int		space;

	i = 0;
	j = 0;
	redir_left = 0;
	redir_right = 0;
	space = 0;
	copy = malloc(sizeof(char) * ft_strlen_redir(str) + 1);
	if (!copy)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
		{
			space++;
			copy[j] = str[i];
		}
		else if (str[i] == '<' || str[i] == '>')
		{
			if (i != 0 && !space && !redir_left && !redir_right)
				copy[j++] = ' ';
			copy[j] = str[i];
			if (i == '>')
				redir_right++;
			else
				redir_left++;
			space = 0;
			if (redir_left > 2 || redir_right > 2)
				return (strerror(5));
		}
		else
		{
			if (i != 0)
			{
				if (str[i - 1] == '<' || str[i - 1] == '>')
					copy[j++] = ' ';
			}
			copy[j] = str[i];
			space = 0;
			redir_left = redir_right = 0;	
		}
		i++;
		j++;
	}
	copy[j] = '\0';
	return (copy);
}
