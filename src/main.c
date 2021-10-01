#include "minishell.h"

int main (int argc, char **argv, char **envp)
{
	int		ok;
	char	*line;
	//int		pipe;
	//pid_t pid;
	//int	status;
	//char	c;
	t_command	*cmd;
	char		**split_pp;

	ok = 1;
	(void)argc;
	(void)argv;
	(void)envp;	
	while (ok)
	{
		if (prompt_color() == 0)
			return (0);
		line = readline("");
		if (line != NULL)
		{
			cmd = find_indexes(line);
			if (!cmd)
				printf("error quote\n");
			else
			{
				int x = -1;
				int y = -1;
				while (++x < cmd->nb_dq)
					printf("dq[%d] : %d\n", x, cmd->double_q[x]);
				while (++y < cmd->nb_sq)
					printf("sq[%d] : %d\n", y, cmd->single_q[y]);
			}
			init_builtin_lst(cmd);
			for (int i = 0; cmd->blti_lst[i]; i++)
				printf("cmd[%d] : %s\n", i, cmd->blti_lst[i]);
			if (count_pipe(line) > 0)
			{
				split_pp = ft_split_pipe(line, '|');
				for (int i = 0; split_pp[i]; i++)
					printf("split_pp[%d] : %s\n", i, split_pp[i]);
			}
			// pipe = count_pipe(line);
			// printf("pipe = %d\n", pipe);
			// c = lexer_quote(line);
			// printf("%c\n", c);
			// line = str_trim(line, c);
			// printf("redir : %s\n", line);
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
