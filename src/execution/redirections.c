/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:23:28 by hkrifa            #+#    #+#             */
/*   Updated: 2021/10/27 10:56:21 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	right_redirections(t_tree **cmds, int i, int j)
{
	if (!ft_strcmp(cmds[i]->red[j], ">"))
	{
		if (!right_redir(cmds, i, j))
			return (0);
	}
	else if (!ft_strcmp(cmds[i]->red[j], ">>"))
	{
		if (!double_right_redir(cmds, i, j))
			return (0);
	}
	return (1);
}

static int	left_redirections(t_tree **cmds, int i, int j)
{
	if (!ft_strcmp(cmds[i]->red[j], "<"))
	{
		if (left_redir(cmds, i, j))
			return (g_global);
	}
	else if (!ft_strcmp(cmds[i]->red[j], "<<"))
	{
		if (double_left_redir(cmds, i, j))
			return (g_global);
	}
	g_global = 0;
	return (g_global);
}

int	redirections(t_tree **cmds, int i)
{
	int	j;

	j = 0;
	while (cmds[i]->red[j] != NULL)
	{
		if (!ft_strcmp(cmds[i]->red[j], ">")
			|| !ft_strcmp(cmds[i]->red[j], ">>"))
		{
			if (!right_redirections(cmds, i, j))
				return (0);
		}
		else if (!ft_strcmp(cmds[i]->red[j], "<")
			|| !ft_strcmp(cmds[i]->red[j], "<<"))
		{
			if (left_redirections(cmds, i, j))
				return (g_global);
		}
		j++;
	}
	g_global = 0;
	return (0);
}
