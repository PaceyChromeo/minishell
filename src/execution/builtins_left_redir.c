/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_left_redir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:42:34 by hkrifa            #+#    #+#             */
/*   Updated: 2021/11/02 11:13:28 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	return (0);
}

int	open_heredoc_builtins(char **heredoc, int j, t_var *var)
{
	var->pid2 = fork();
	if (!var->pid2)
	{
		while (heredoc[j] != NULL)
		{
			var->temp = open("temp.txt", O_CREAT | O_WRONLY | O_TRUNC, 0777);
			while (write(1, "> ", ft_strlen("> "))
				&& get_next_line(0, &var->line) > 0
				&& (ft_strcmp(var->line, heredoc[j + 1]) != 0))
			{
				write(var->temp, var->line, ft_strlen(var->line));
				write(var->temp, "\n", 1);
				free(var->line);
			}
			j += 2;
		}
		exit(0);
	}
	g_global = var->pid2;
	signal(SIGINT, handler_exit_builtins);
	signal(SIGQUIT, handler_exit_builtins);
	while (waitpid(var->pid2, &var->status, WUNTRACED) > 0)
		;
	return (1);
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

void	loop_double_redirs(t_tree *cmd, t_var *var)
{
	int	j;
	char **heredoc;
	
	j = 0;
	heredoc = get_tab(cmd);
	open_heredoc_builtins(heredoc, j, var);
	free(heredoc);
}
