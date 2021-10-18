/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:43:53 by pjacob            #+#    #+#             */
/*   Updated: 2021/10/18 16:49:56 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

int	treat_single_cmd(char *line, char **envp)
{
	(void)envp;
	t_tree	*cmd;
	int		fd;

	cmd = create_trees(line);
	//print_tree(cmd);
	error_handler(cmd);
	if (cmd->size_red)
		fd = redirections(&cmd, 0);
	else
		fd = STDOUT_FILENO;
	//printf("fd : %d\n", fd);
	exec_bltin(cmd, fd);
	return (0);
}