/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacey <pacey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 10:05:47 by misaev            #+#    #+#             */
/*   Updated: 2021/10/20 18:39:11 by pacey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	echo(t_tree *tree)
{
	int i;
	int opt;

	opt = 0;
	i = echo_option(tree->full_cmd, 5);
	if (tree->size_args > 1 && i)
		opt = 1;
	else
		i = 5;
	while(tree->full_cmd[i])
	{
		if (tree->full_cmd[i] != 34 && tree->full_cmd[i] != 39
			&& tree->full_cmd[i] != '$')
			ft_putchar_fd(tree->full_cmd[i], STDOUT_FILENO);
		if (tree->full_cmd[i] == 39 && tree->full_cmd[i + 1])
		{
			i++;
			while (tree->full_cmd[i] != 39 && tree->full_cmd[i])
			{
				ft_putchar_fd(tree->full_cmd[i], STDOUT_FILENO);
				i++;
			}
		}
		if (tree->full_cmd[i] == '$' && (ft_isalpha(tree->full_cmd[i + 1])
			|| ft_isnum(tree->full_cmd[i + 1]) || tree->full_cmd[i + 1] == '_'))
		{
			i = echo_print_env(tree->full_cmd, i + 1);
		
		}
		if (tree->full_cmd[i] == 34 && tree->full_cmd[i + 1])
		{
			i++;
			while (tree->full_cmd[i] != 34 && tree->full_cmd[i])
			{
				if (tree->full_cmd[i] == '$' && (ft_isalpha(tree->full_cmd[i + 1])
					|| ft_isnum(tree->full_cmd[i + 1]) || tree->full_cmd[i + 1] == '_'))
					i = echo_print_env(tree->full_cmd, i + 1) + 1;
				if (tree->full_cmd[i] != 34)
					ft_putchar_fd(tree->full_cmd[i], STDOUT_FILENO);
				i++;
			}	
		}
		i++;
	}
	if (!opt)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

void	cd(char *path)
{
	if (access(path, F_OK) == 0)
		chdir(path);
	else
		perror(path);
}

void	pwd(void)
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
		echo(cmd);
	else if (cmd->cmd_type == tree_pwd)
		pwd();
	else if (cmd->cmd_type == tree_cd)
		cd(cmd->args[1]);
}