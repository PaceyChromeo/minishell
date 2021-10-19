/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkrifa <hkrifa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:26:59 by hkrifa            #+#    #+#             */
/*   Updated: 2021/10/19 10:54:09 by hkrifa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	is_child(t_tree **cmds, int old_pipefd[2], int new_pipefd[2], t_var *var)
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
	if (cmds[var->i]->cmd_type >= tree_cd 
		&& cmds[var->i]->cmd_type <= tree_exit)
	{
		bultins_cmd(cmds[var->i]);
		exit(STDERR_FILENO);
	}
	else if (!execute(cmds, var->env, var->i))
		exit(STDERR_FILENO);
}

static void	multipipes(t_tree **cmds, int old_pipefd[2], t_var *var)
{
	int		new_pipefd[2];
	pid_t	pid;
	
	pipe(new_pipefd);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
		is_child(cmds, old_pipefd, new_pipefd, var);
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

	var.i = 0;
	var.env = env;
	pipe(fd);
	multipipes(cmds, fd, &var);
	close(fd[1]);
	close(fd[0]);
	while (wait(NULL) > 0);
}
