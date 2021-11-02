/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkrifa <hkrifa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 10:05:47 by misaev            #+#    #+#             */
/*   Updated: 2021/11/02 14:29:33 by hkrifa           ###   ########.fr       */
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
	int		j;

	j = 0;
	if (access(path, F_OK) == 0)
	{
		change_path(var, "OLDPWD");
		chdir(path);
		change_path(var, "PWD");
	}
	else if (!path)
	{
		home = ft_getenv("HOME", var);
		if (home)
		{
			if (access(home, F_OK) == 0)
			{
				change_path(var, "OLDPWD");
				chdir(home);
				change_path(var, "PWD");
			}
		}
		else
		{
			j = 1;
			g_global = 1;
			printf("cd: HOME not set\n");
		}
	}
	else
		perror(path);
	if (j != 1)
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

int	exit_cmd(t_tree *cmd)
{
	int	i;
	
	i = 0;
	if (cmd->size_args > 1)
	{
		while (cmd->args[1][i])
		{
			if (!ft_isnum(cmd->args[1][i]))
			{
				printf("exit: %s: numeric argument required\n", cmd->args[1]);
				g_global = 255;
				return (0);
			}
			i++;
		}
		g_global = ft_atoi(cmd->args[1]);
	}
	else
		g_global = 0;
	if (cmd->size_args > 2)
	{
		printf("exit: too many arguments\n");
		g_global = 1;
		return (1);
	}
	return (0);
}

int	builtins_cmd(t_tree *cmd, t_var *var)
{
	int fdt;
	
	if (cmd->z == 1 && cmd->size_red > 0)
	{
		loop_double_redirs(cmd, var);
		builtins_redir(cmd);
	}
	if (g_global <= 258 && g_global != 1)
	{
		if (cmd->cmd_type == tree_echo)
			g_global = echo(cmd);
		else if (cmd->cmd_type == tree_pwd)
			g_global = pwd();
		else if (cmd->cmd_type == tree_cd)
			g_global = cd(var, cmd->args[1]);
		else if (cmd->cmd_type == tree_export
			|| cmd->cmd_type == tree_exportargs)
			g_global = exec_export(cmd, var);
		else if (cmd->cmd_type == tree_env)
			g_global = exec_env(cmd, var);
		else if (cmd->cmd_type == tree_unset)
			g_global = exec_unset(cmd, var);
		dup2(cmd->save, 1);
	}
	if (g_global > 258)
		g_global = 1;
	fdt = open("temp.txt", O_RDONLY, 0777);
	if (fdt != -1)
		unlink("temp.txt");
	return (g_global);
}
