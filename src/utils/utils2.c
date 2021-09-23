#include "minishell.h"

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i] != '\0')
		{
			write(fd, &str[i], 1);
			i++;
		}
	}
}

void blue() 
{
  printf("\033[1;36m");
}

void yellow()
{
  printf("\033[1;33m");
}

void reset() 
{
  printf("\033[0m");
}

 