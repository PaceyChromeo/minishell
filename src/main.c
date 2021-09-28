#include "minishell.h"

int main (int argc, char **argv, char **envp)
{
	int		ok;
	char	*line;
	int		pipe;
	//pid_t pid;
	//int	status;
	char	c;

	ok = 1;
	(void)argc;
	(void)argv;
	(void)envp;
	while (ok)
	{
		prompt_color();    
		line = readline("");
		if (line != NULL)
		{
			pipe = count_pipe(line);
			printf("pipe = %d\n", pipe);
			c = lexer_quote(line);
			printf("%c\n", c);
			line = str_trim(line, c);
			printf("redir : %s\n", line);
			add_history(line);
			// pid = fork();
			// if (pid == 0)
			// {
			// 	system(line); // ici c'est biensur execve qu'il faut employer
			// 	free (line);
			// 	line = NULL;
			// }
			// else
			// {
			// 	waitpid(pid, &status, WUNTRACED); // option wuntraced, le process parent reprend la main si un fils est bloque 
			// 	free (line);
			// 	line = NULL;
			// }
		}
		else
		{
			free((void *)line);
			line = NULL;
			ok = 0;
		}
	}
	return (0);
}
