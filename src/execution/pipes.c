/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacey <pacey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:26:59 by hkrifa            #+#    #+#             */
/*   Updated: 2021/10/16 16:48:12 by pacey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute(t_tree **cmds, char **env, int i)
{
	int		exec;
	char	*path;

	path = get_path(cmds[i]->args[0]);
	exec = execve(path, cmds[i]->args, env);
	if (exec == -1)
	{
		perror("execve");
		return (0);
	}
	return (1);
}

static void	multipipes(t_tree **cmds, int old_pipefd[2], int i, char **env)
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
	{
		if (cmds[i + 1] != NULL)
			dup2(new_pipefd[1], 1);
		if (i != 0)
			dup2(old_pipefd[0], 0);
		if (cmds[i]->size_red > 0)
			redirections(cmds, i);
		close(old_pipefd[0]);
		close(old_pipefd[1]);
		close(new_pipefd[0]);
		close(new_pipefd[1]);
		if (!execute(cmds, env, i))
			return ;
	}
	close(new_pipefd[1]);
	if (cmds[i + 1] != NULL)
		multipipes(cmds, new_pipefd, i + 1, env);
	close(new_pipefd[0]);
}

void	exec_pipes(t_tree **cmds, char **env)
{
	int	i;
	int	fd[2];

	i = 0;
	pipe(fd);
	multipipes(cmds, fd, i, env);
	close(fd[1]);
	close(fd[0]);
	while (wait(NULL) > 0);
}
