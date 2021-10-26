/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkrifa <hkrifa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 10:05:47 by misaev            #+#    #+#             */
/*   Updated: 2021/10/26 12:45:41 by hkrifa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	echo(t_tree *tree)
{
	int	i;
	int	opt;

	opt = 0;
	i = 1;
	if (tree->size_args > 1)
	{
		i = echo_option(tree->args, i);
		if (i > 1)
			opt = 1;
		while (i < tree->size_args)
		{
			if (!ft_strcmp(tree->args[i], "$?"))
				ft_putnbr_fd(global, STDOUT_FILENO);
			else	
				ft_putstr_fd(tree->args[i], STDOUT_FILENO);
			if (i < tree->size_args - 1)
				ft_putchar_fd(' ', STDOUT_FILENO);
			if (i == tree->size_args - 1 && !opt)
				ft_putchar_fd('\n', STDOUT_FILENO);
			i++;
		}
	}
	else
		ft_putchar_fd('\n', STDOUT_FILENO);
		
}

void	cd(char *path)
{
	char *home;

	if (access(path, F_OK) == 0)
		chdir(path);
	else if (!path)
	{
		home = getenv("HOME");
		if (access(home, F_OK) == 0)
			chdir(home);
	}
	else
		perror(path);
}

void	pwd(void)
{
	char	*buf;

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

void	exit_cmd(t_tree *cmd)
{
	//print_tree(cmd);
	int ret;

	if (cmd->args[1])
		ret = ft_atoi(cmd->args[1]);
	else
		ret = 0;
	global = ret;
}

int	builtins_cmd(t_tree *cmd)
{
	if (cmd->cmd_type == tree_echo)
		echo(cmd);
	else if (cmd->cmd_type == tree_pwd)
		pwd();
	else if (cmd->cmd_type == tree_cd)
		cd(cmd->args[1]);
	else if (cmd->cmd_type == tree_exit)
		exit_cmd(cmd);
	return (0);
}
