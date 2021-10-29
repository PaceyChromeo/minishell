/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 11:18:18 by hkrifa            #+#    #+#             */
/*   Updated: 2021/10/29 16:46:44 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	right_redir(t_tree **cmds, int i, int j)
{	
	int	fileout;

	fileout = open(cmds[i]->red[j + 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fileout == -1)
	{
		perror("open");
		return (0);
	}
	if (cmds[i]->red[j + 2] == NULL)
		dup2(fileout, 1);
	if (!cmds[i]->cmd_value)
		exit(0);
	return (1);
}

int	double_right_redir(t_tree **cmds, int i, int j)
{
	int	fileout;

	fileout = open(cmds[i]->red[j + 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fileout == -1)
	{
		perror("open");
		return (0);
	}
	if (cmds[i]->red[j + 2] == NULL)
		dup2(fileout, 1);
	if (!cmds[i]->cmd_value)
		exit(0);
	return (1);
}
