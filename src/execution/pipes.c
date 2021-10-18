/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:26:59 by hkrifa            #+#    #+#             */
/*   Updated: 2021/10/18 17:43:30 by pjacob           ###   ########.fr       */
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

static void	multipipes(t_tree **cmds, int old_pipefd[2], int i, char **env)
{
	int		new_pipefd[2];
	pid_t	pid;
	
	pipe(new_pipefd);
	// printf("oldfd[0] : %d oldfd[1]: %d\n", old_pipefd[0], old_pipefd[1]);
	// printf("new_pipefd[0] : %d new_pipefd[1]: %d\n", new_pipefd[0], new_pipefd[1]);
	if (cmds[i]->size_red > 0)
		if (redirections(cmds, i) == -1)
			return ;
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
		//print_tree(cmds[i]);
		close(old_pipefd[0]);
		close(old_pipefd[1]);
		close(new_pipefd[0]);
		close(new_pipefd[1]);
		if (cmds[i]->cmd_type >= 0 && cmds[i]->cmd_type <= 6)
			exec_bltin(cmds[i]);
		else if (cmds[i]->cmd_type == 7)
		{
			if (!execute(cmds, env, i))
				return ;
		}
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

	//print_tree(*cmds);
	i = 0;
	pipe(fd);
	
	multipipes(cmds, fd, i, env);
	close(fd[1]);
	close(fd[0]);
	while (wait(NULL) > 0);
}
