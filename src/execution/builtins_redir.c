/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkrifa <hkrifa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:32:08 by hkrifa            #+#    #+#             */
/*   Updated: 2021/10/29 15:52:36 by hkrifa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static	int	right_redirs(t_tree *cmd, int j)
{	
	int	fileout;
	
	while (cmd->red[j] != NULL)
	{
		if (!ft_strcmp(cmd->red[j], ">") || !ft_strcmp(cmd->red[j], ">>"))
		{
			fileout = open(cmd->red[j + 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (fileout == -1)
			{
				perror("open");
				return (0);
			}
			if (cmd->red[j + 2] == NULL)
			{
				cmd->save = dup(1);
				dup2(fileout, 1);
				close(fileout);
			}
			j+= 2;
		}
	}
	return (1);
}

static int	double_right_redirs(t_tree *cmd, int j)
{
	int	fileout;

	fileout = open(cmd->red[j + 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fileout == -1)
	{
		perror("open");
		return (0);
	}
	if (cmd->red[j + 2] == NULL)
		dup2(fileout, 1);
	return (1);
}

static int	rights_redirections(t_tree *cmd, int j)
{
	if (!ft_strcmp(cmd->red[j], ">"))
	{
		if (!right_redirs(cmd, j))
			return (0);
	}
	else if (!ft_strcmp(cmd->red[j], ">>"))
	{
		if (!double_right_redirs(cmd, j))
			return (0);
	}
	return (1);
}

static int	lefts_redirections(t_tree *cmd, int j)
{
	if (!ft_strcmp(cmd->red[j], "<"))
	{
		if (left_redirs(cmd, j))
			return (g_global);
	}
	else if (!ft_strcmp(cmd->red[j], "<<"))
	{
		if (double_left_redirs(cmd, j))
			return (g_global);
	}
	g_global = 0;
	return (g_global);
}

int	builtins_redir(t_tree *cmd)
{
	int	j;

	j = 0;
	while (cmd->red[j])
	{
		if (!ft_strcmp(cmd->red[j], ">")
			|| !ft_strcmp(cmd->red[j], ">>"))
		{
			if (!rights_redirections(cmd, j))
				return (0);
		}
		else if (!ft_strcmp(cmd->red[j], "<")
			|| !ft_strcmp(cmd->red[j], "<<"))
		{
			if (lefts_redirections(cmd, j))
				return (g_global);
		}
		j++;
	}
	g_global = 0;
	return (0);
}