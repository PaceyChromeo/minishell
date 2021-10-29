/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkrifa <hkrifa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:26:59 by hkrifa            #+#    #+#             */
/*   Updated: 2021/10/29 10:41:15 by hkrifa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	execute(t_tree **cmds, t_var *var, int i)
{
	int		exec;
	char	*path;

	if (cmds[i]->cmd_type != tree_path)
	{
		path = get_path(cmds[i]->cmd_value);
		exec = execve(path, cmds[i]->args, var->envp);
	}
	else
		exec = execve(cmds[i]->cmd_value, cmds[i]->args, var->envp);
	if (exec == -1)
	{
		perror("execve");
		g_global = 1;
		return (g_global);
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
			exit(g_global);
	close(old_pipefd[0]);
	close(old_pipefd[1]);
	close(new_pipefd[0]);
	close(new_pipefd[1]);
	if (cmds[var->i]->cmd_type < 8)
	{
		printf("hey\n");
		g_global = builtins_cmd(cmds[var->i], var);
		exit (g_global);
	}
	else if (cmds[var->i]->cmd_type == 8 || cmds[var->i]->cmd_type == 9)
		execute(cmds, var, var->i);
	return (g_global);
}

static int	multipipes(t_tree **cmds, int old_pipefd[2], t_var *var)
{
	int		new_pipefd[2];
	
	if (cmds[var->i]->cmd_value 
		&& (!ft_strcmp(cmds[var->i]->cmd_value, "cat") 
		|| !ft_strcmp(cmds[var->i]->cmd_value, "sort")))
		g_global = -888;
	if (cmds[var->i]->size_red > 0)
		loop_double_redir(cmds, var->i);
	pipe(new_pipefd);
	var->pid = fork();
	if (var->pid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (!var->pid)
		g_global = is_child(cmds, old_pipefd, new_pipefd, var);
	close(new_pipefd[1]);
	if (cmds[var->i + 1] != NULL)
	{
		var->i++;
		multipipes(cmds, new_pipefd, var);
	}
	close(new_pipefd[0]);
	return (0);
}

void	exec_pipes(t_tree **cmds, t_var *var)
{
	int	fd[2];
	int status;
	int res;

	var->i = 0;
	pipe(fd);
	signal(SIGINT, handler_child);
	signal(SIGQUIT, handler_child);
	multipipes(cmds, fd, var);
	close(fd[1]);
	close(fd[0]);
	while ((waitpid(var->pid, &status, WUNTRACED) > 0))
		;
	unlink("temp.txt");
	if (WIFEXITED(status) && !WIFSIGNALED(status))
    {
        g_global = WEXITSTATUS(status); // bonne cmd
		if (g_global == 255)
			g_global = 255;
        else if (WEXITSTATUS(status) != 0 && g_global != 1) // mauvaise cmd
            g_global += 125;
        else if (WEXITSTATUS(status) != 0 && g_global == 1) // mauvais file
            g_global = 1;
    }
    else if (!WIFEXITED(status) && WIFSIGNALED(status))
    {
    	res = WTERMSIG(status);
		if (g_global == 130 && res == 1) //cat + ctrl c
			g_global = 130;
		else if (res == 100)
			g_global = 1;
		else
			g_global = res + 128;
    }
}
