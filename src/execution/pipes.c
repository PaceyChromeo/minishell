/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:26:59 by hkrifa            #+#    #+#             */
/*   Updated: 2021/10/26 18:40:38 by pjacob           ###   ########.fr       */
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
		global = 1;
		return (global);
	}
	return (0);
}

static int	is_child(t_tree **cmds, int old_pipefd[2],
	int new_pipefd[2], t_var *var)
{
	if (cmds[var->i + 1] != NULL)
		dup2(new_pipefd[1], 1);
	if (var->i != 0)
		dup2(old_pipefd[0], 0);
	if (cmds[var->i]->size_red > 0)
		if (redirections(cmds, var->i))
			exit(global);
	close(old_pipefd[0]);
	close(old_pipefd[1]);
	close(new_pipefd[0]);
	close(new_pipefd[1]);
	if (cmds[var->i]->cmd_type != tree_execve && cmds[var->i]->cmd_type != tree_nocmd)
	{
		global = builtins_cmd(cmds[var->i]);
		exit (global);
	}
	else if (cmds[var->i]->cmd_type == tree_execve)
		execute(cmds, var->env, var->i);
	return (global);
}

static int	multipipes(t_tree **cmds, int old_pipefd[2], t_var *var)
{
	int		new_pipefd[2];

	pipe(new_pipefd);
	var->pid = fork();
	if (var->pid == -1)
	{
		perror("fork");
		return (-1);
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
	return (0);
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
	int x = WIFEXITED(status);
	int y = WEXITSTATUS(status);
	printf("x : %d y : %d\n", x, y);
	// if (!y)
	// {
	// 	if (global != 130 || global != 131 || global != 255 | global !=)
	// 		global = 0;
			
	// }
	// if (WIFEXITED(status))
	// {
	// 	//global = WEXITSTATUS(status);
	// 	if (global == 2)
	// 		global += 125;
	// }
	// else
	// 	global = 0;
}
