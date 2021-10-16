/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkrifa <hkrifa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:23:28 by hkrifa            #+#    #+#             */
/*   Updated: 2021/10/15 18:40:26 by hkrifa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

int	right_redir(t_tree **cmds, int i, int j)
{
	
	int fileout;
	fileout = open(cmds[i]->red[j + 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fileout == -1)
	{
		perror("open");
		return (0);
	}
	return (1);
}

int	double_right_redir(t_tree **cmds, int i, int j)
{
	int fileout;

	fileout = open(cmds[i]->red[j + 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fileout == -1)
	{
		perror("open");
		return (0);
	}
	return (1);
}

int	left_redir(t_tree **cmds, int i, int j)
{
	int filein;
	filein = open(cmds[i]->red[j + 1], O_RDONLY, 0777);
	if (filein == -1)
	{
		perror("open");
		return (0);
	}
	return (1);
}

// void	double_left_redir(t_tree **cmds, int i, int j)
// {
// 	int filein;

	
// }

void	redirections(t_tree **cmds, int i)
{
	int j;

	j = 0;
	
	while (cmds[i]->red[j] != NULL)
	{
		if (!ft_strcmp(cmds[i]->red[j], ">"))
		{
			if (!right_redir(cmds, i, j))
				return ;	
		}
		else if (!ft_strcmp(cmds[i]->red[j], ">>"))
		{
			if (!double_right_redir(cmds, i, j))
				return ;
		}
		else if (!ft_strcmp(cmds[i]->red[j], "<"))
		{
			if (!left_redir(cmds, i, j))
				return ;
		}
		else if (!ft_strcmp(cmds[i]->red[j], "<<"))
		{
			double_left_redir(cmds, i, j);
			return ;
		}
		j++;
	}
}