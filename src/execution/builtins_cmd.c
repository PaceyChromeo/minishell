/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkrifa <hkrifa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 10:05:47 by misaev            #+#    #+#             */
/*   Updated: 2021/10/18 18:29:54 by hkrifa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void echo(char **arg)
{
	int i;
	int opt;

	opt = 0;
	i = 1;
	if (echo_option(arg[i]) == 1 && arg[i] != NULL)
	{
		opt = 1;
		i++;
	}
	while(arg[i] != '\0')
	{
		ft_putstr_fd(arg[i], STDOUT_FILENO);
		if (arg[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (opt != 1)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

void cd(char *path)
{
	if (access(path, F_OK) == 0)
		chdir(path);
	else
		perror(path);
}

void pwd(void)
{
	char *buf;
	buf = NULL;
	buf = getcwd(NULL, 0);
	if (buf == NULL)
		 perror(buf);
	else
	{
		ft_putstr_fd(buf, STDOUT_FILENO);
		write(STDOUT_FILENO, "\n", 1);
	}
}

void	bultins_cmd(t_tree *cmd)
{
	if (cmd->cmd_type == tree_echo)
		echo(cmd->args);
	else if (cmd->cmd_type == tree_pwd)
		pwd();
	else if (cmd->cmd_type == tree_cd)
		cd(cmd->args[1]);
}