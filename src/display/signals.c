#include "minishell.h"

void	handler_int(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
      	global = 130;
	}
	else if (sig == SIGQUIT)
	{
		exit(0);
	}
}
