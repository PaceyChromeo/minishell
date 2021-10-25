/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaev <misaev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:26:59 by hkrifa            #+#    #+#             */
/*   Updated: 2021/10/25 17:35:26 by misaev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	execute(t_tree **cmds, char **env, int i)
{
	int		exec;
	char	*path;

	path = get_path(cmds[i]->cmd_value);
	exec = execve(path, cmds[i]->args, env);
	if (exec == -1)
	{
		perror("execve");
		return (0);
	}
	return (1);
}

static void	is_child(t_tree **cmds, int old_pipefd[2],
	int new_pipefd[2], t_var *var)
{
	if (cmds[var->i + 1] != NULL)
		dup2(new_pipefd[1], 1);
	if (var->i != 0)
		dup2(old_pipefd[0], 0);
	if (cmds[var->i]->size_red > 0)
		if (!redirections(cmds, var->i))
			exit(STDERR_FILENO);
	close(old_pipefd[0]);
	close(old_pipefd[1]);
	close(new_pipefd[0]);
	close(new_pipefd[1]);
	if (cmds[var->i]->cmd_type != tree_execve)
	{
		builtins_cmd(cmds[var->i], var->env);
		exit(STDERR_FILENO);
	}
	else if (!execute(cmds, var->env, var->i))
		exit(STDERR_FILENO);
}

static void	multipipes(t_tree **cmds, int old_pipefd[2], t_var *var)
{
	int		new_pipefd[2];

	pipe(new_pipefd);
	var->pid = fork();
	if (var->pid == -1)
	{
		perror("fork");
		return ;
	}
	if (var->pid == 0)
	{
		if (cmds[var->i]->size_red > 0)
			loop_double_redir(cmds, var->i);
		is_child(cmds, old_pipefd, new_pipefd, var);
	}
	close(new_pipefd[1]);
	
	if (cmds[var->i + 1] != NULL)
	{
		var->i++;
		multipipes(cmds, new_pipefd, var);
	}
	close(new_pipefd[0]);
}

void	exec_pipes(t_tree **cmds, char **env)
{
	int	fd[2];
	t_var var;
	int status;
	
	var.i = 0;
	var.env = env;
	pipe(fd);
	multipipes(cmds, fd, &var);
	signal(SIGINT, handler_child);
	signal(SIGQUIT, handler_child);
	close(fd[1]);
	close(fd[0]);
	while ((waitpid(var.pid, &status, WUNTRACED) > 0))
		;
	if (WIFEXITED(status))
	{
		global = WEXITSTATUS(status);
		if (global == 2)
			global += 125;
	}
}
