/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkrifa <hkrifa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 11:18:03 by hkrifa            #+#    #+#             */
/*   Updated: 2021/11/01 13:54:20 by hkrifa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	handler_exit(int sig)
{
	if (sig == SIGQUIT && g_global > 258)
	{
		ft_putstr_fd("\e[2K", 1);
		ft_putstr_fd("\r> ", 1);
	}
	if ((sig == SIGINT) && g_global > 258)
	{
		if (!kill(g_global, SIGTERM))
			g_global = 1;
		printf("\e[2K");
		printf("\n");
	}
}

int	left_redir(t_tree **cmds, int i, int j)
{
	int	filein;

	filein = open(cmds[i]->red[j + 1], O_RDONLY, 0777);
	if (filein == -1)
	{
		perror("open");
		g_global = 1;
		return (g_global);
	}
	if (j == 0)
		dup2(filein, 0);
	return (0);
}

int	double_left_redir(t_tree **cmds, int i, int j)
{
	int	filein;

	(void)cmds;
	(void)i;
	(void)j;
	filein = open("temp.txt", O_RDONLY, 0777);
	if (filein == -1)
	{
		perror("open");
		g_global = 1;
		return (g_global);
	}
	dup2(filein, 0);
	if (!cmds[i]->cmd_value && cmds[i]->red[j + 2] == NULL)
		exit (0);
	return (0);
}


static int	count_strs(char **tab)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (tab[i] != NULL)
	{
		if (!ft_strcmp(tab[i], "<<"))
			count++;
		i++;
	}
	return (count);
}

static char	**get_tab(t_tree *cmd)
{
	int k;
	int l;
	int count;
	char **heredoc;
	
	k = 0;
	l = 0;
	count = count_strs(cmd->red);
	heredoc = malloc(sizeof(heredoc) * (count + count) + 1);
	k = 0;
	while (cmd->red[k] != NULL)
	{
		if (!ft_strcmp(cmd->red[k], "<<"))
		{
			heredoc[l] = cmd->red[k];
			k++;
			l++;
			heredoc[l] = cmd->red[k];
			l++;
		}
		k++;
	}
	heredoc[l] = NULL;
	return (heredoc);
}

int	open_heredoc(t_tree **cmds, int i, int j)
{
	int		temp;
	char	*line;
	pid_t	pid;
	int		status;

	pid = fork();
	if (!pid)
	{
		while (cmds[i]->heredoc[j] != NULL)
		{
			temp = open("temp.txt", O_CREAT | O_WRONLY | O_TRUNC, 0777);
			while (write(1, "> ", ft_strlen("> "))
				&& get_next_line(0, &line) > 0
				&& (ft_strcmp(line, cmds[i]->heredoc[j + 1]) != 0))
			{
				write(temp, line, ft_strlen(line));
				write(temp, "\n", 1);
				free(line);
			}
			j += 2;
		}
		exit(0);
	}
	g_global = pid;
	signal(SIGINT, handler_exit);
	signal(SIGQUIT, handler_exit);
	while (waitpid(pid, &status, 0) > 0)
		;
	cmds[i]->sig = WTERMSIG(status);
	return (1);
}

void	loop_double_redir(t_tree **cmds, int i)
{
	int	j;

	j = 0;
	cmds[i]->heredoc = get_tab(cmds[i]);
	open_heredoc(cmds, i, j);
	free(cmds[i]->heredoc);
}
