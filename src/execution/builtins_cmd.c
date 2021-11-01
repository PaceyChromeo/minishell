/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochichep <ochichep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 10:05:47 by misaev            #+#    #+#             */
/*   Updated: 2021/11/01 13:33:21 by ochichep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(t_tree *tree)
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
				ft_putnbr_fd(g_global, STDOUT_FILENO);
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
	g_global = 0;
	return (g_global);
}

int	cd(t_var *var, char *path)
{
	char	*home;

	if (access(path, F_OK) == 0)
	{
		haroun_la_pute(var, "OLDPWD");
		chdir(path);
		haroun_la_pute(var, "PWD");
	}
	else if (!path)
	{
		home = getenv("HOME");
		if (access(home, F_OK) == 0)
		{
			haroun_la_pute(var, "OLDPWD");
			chdir(home);
			haroun_la_pute(var, "PWD");
		}
	}
	else
		perror(path);
	g_global = 0;
	return (g_global);
}

int	pwd(void)
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
	g_global = 0;
	return (g_global);
}

static int	exit_cmd_norm(t_tree *cmd, int ret)
{
	if (cmd->size_args > 2)
	{
		printf("exit: too many arguments\n");
		g_global = 255;
		return (g_global);
	}
	else
		ret = 0;
	return (ret);
}

int	exit_cmd(t_tree *cmd)
{
	int	ret;
	int	i;

	i = 0;
	ret = 0;
	if (cmd->size_args == 2)
	{
		while (cmd->args[1][i])
		{
			if (!ft_isnum(cmd->args[1][i]))
			{
				printf("exit: %s: numeric argument required\n", cmd->args[1]);
				g_global = 255;
				return (g_global);
			}
			i++;
		}
		ret = ft_atoi(cmd->args[1]);
	}
	ret = exit_cmd_norm(cmd, ret);
	//else if (cmd->size_args > 2)
	// {
	// 	printf("exit: too many arguments\n");
	// 	g_global = 255;
	// 	return (g_global);
	// }
	// else
	// 	ret = 0;
	g_global = ret;
	return (g_global);
}

static int	builtins_cmd_norm(t_tree *cmd, t_var *var)
{
	if (cmd->cmd_type == tree_echo)
		g_global = echo(cmd);
	else if (cmd->cmd_type == tree_pwd)
		g_global = pwd();
	else if (cmd->cmd_type == tree_cd)
		g_global = cd(var, cmd->args[1]);
	else if (cmd->cmd_type == tree_exit)
		g_global = exit_cmd(cmd);
	else if (cmd->cmd_type == tree_export
		|| cmd->cmd_type == tree_exportargs)
		g_global = exec_export(cmd, var);
	else if (cmd->cmd_type == tree_exit)
		g_global = exit_cmd(cmd);
	else if (cmd->cmd_type == tree_env)
		g_global = exec_env(cmd, var);
	else if (cmd->cmd_type == tree_unset)
		g_global = exec_unset(cmd, var);
	return (g_global);
}

int	builtins_cmd(t_tree *cmd, t_var *var)
{
	if (cmd->z == 1 && cmd->size_red > 0)
		builtins_redir(cmd);
	if (g_global < 258)
	{
		g_global = builtins_cmd_norm(cmd, var);
		dup2(cmd->save, 1);
	}
	if (g_global > 258)
		g_global = 1;
	return (g_global);
}
