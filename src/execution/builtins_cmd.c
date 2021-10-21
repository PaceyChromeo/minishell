/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkrifa <hkrifa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 10:05:47 by misaev            #+#    #+#             */
/*   Updated: 2021/10/21 12:03:22 by hkrifa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	echo(t_tree *tree)
{
	int	i;
	int	opt;

	opt = 0;
	i = echo_option(tree->f_cmd, 5);
	if (tree->size_args > 1 && i)
		opt = 1;
	else
		i = 5;
	while (tree->f_cmd[i])
	{
		if (tree->f_cmd[i] != 34 && tree->f_cmd[i] != 39
			&& tree->f_cmd[i] != '$')
			ft_putchar_fd(tree->f_cmd[i], STDOUT_FILENO);
		if (tree->f_cmd[i] == 39 && tree->f_cmd[i + 1])
			i = print_quote(tree->f_cmd, i + 1, 39);
		if (tree->f_cmd[i] == 34 && tree->f_cmd[i + 1])
			i = print_quote(tree->f_cmd, i + 1, 34);
		if (tree->f_cmd[i] == '$' && (ft_isalpha(tree->f_cmd[i + 1])
				|| ft_isnum(tree->f_cmd[i + 1]) || tree->f_cmd[i + 1] == '_'))
			i = echo_print_env(tree->f_cmd, i + 1);
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

void	bultins_cmd(t_tree *cmd, int nbr_cmd)
{
	//printf("%d\n", nbr_cmd);
	(void)nbr_cmd;
	 if (cmd->size_red > 0)
	 	redirections(&cmd, 0);
	if (cmd->cmd_type == tree_echo)
		echo(cmd);
	else if (cmd->cmd_type == tree_pwd)
		pwd();
	else if (cmd->cmd_type == tree_cd)
		cd(cmd->args[1]);
}
