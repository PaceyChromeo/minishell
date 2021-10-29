/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_left_redir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkrifa <hkrifa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:42:34 by hkrifa            #+#    #+#             */
/*   Updated: 2021/10/29 15:48:48 by hkrifa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	handler_exit_builtins(int sig)
{
	if (sig == SIGQUIT && g_global > 258)
	{
		ft_putstr_fd("\e[2K", 1);
		ft_putstr_fd("\r> ", 1);
		
	}
	if ((sig == SIGINT) && g_global > 258)
	{
		kill(g_global, SIGTERM);
		printf("\e[2K");
		printf("\n");  	
	}
}

int	left_redirs(t_tree *cmd, int j)
{
	int	filein;

	filein = open(cmd->red[j + 1], O_RDONLY, 0777);
	if (filein == -1)
	{
		perror("open");
		g_global = 1;
		return (g_global);
	}
	dup2(filein, 0);
	return (0);
}

int	double_left_redirs(t_tree *cmd, int j)
{
	int	filein;

	(void)cmd;
	(void)j;
	filein = open("temp.txt", O_RDONLY, 0777);
	if (filein == -1)
	{
		perror("open");
		g_global = 1;
		return (g_global);
	}
	dup2(filein, 0);
	return (0);
}

int	open_heredoc_builtins(t_tree *cmd, int j)
{
	int		temp;
	char	*line;
	pid_t 	pid;
	int		status;
	
	pid = fork();
	if (!pid)
	{
		while (!ft_strcmp(cmd->red[j], "<<") && cmd->red[j] != NULL)
		{
			temp = open("temp.txt", O_CREAT | O_WRONLY | O_TRUNC, 0777);
			while (write(1, "> ", ft_strlen("> "))
				&& get_next_line(0, &line) > 0 && (ft_strcmp(line, cmd->red[j + 1]) != 0))
			{
				write(temp, line, ft_strlen(line));
				write(temp, "\n", 1);
				free(line);
			}
			j+=2;
		}
		exit(0);
	}
	g_global = pid;
	signal(SIGINT, handler_exit_builtins);
	signal(SIGQUIT, handler_exit_builtins);
	while (waitpid(pid, &status, 0) > 0)
		;
	return (1);
}

void	loop_double_redirs(t_tree *cmd)
{
	int	j;

	j = 0;
	if (!ft_strcmp(cmd->red[j], "<<"))
		open_heredoc_builtins(cmd, j);
}