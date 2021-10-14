/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkrifa <hkrifa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:26:59 by hkrifa            #+#    #+#             */
/*   Updated: 2021/10/14 18:50:09 by hkrifa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//int j = 0;
// void	multipipes(t_tree **cmds, char **env)
// {
	
// }

void	free_pipes(int *old_pipefd, int *new_pipefd)
{
	free(old_pipefd);
	free(new_pipefd);
}

void	exec_pipes(t_tree **cmds, char **env)
{
	//print_tree(cmds);
	int i;
	int is_child;
	int *old_pipefd;
	int *new_pipefd;
	char *path;
	
	i = 0;
	old_pipefd = malloc(sizeof(int) * 2);
	pipe(old_pipefd);
	while(cmds[i] != NULL)
	{
		path = get_path(cmds[i]->args[0]);
		//printf("%s\n", path);
		new_pipefd = malloc(sizeof(int) * 2);
		pipe(new_pipefd);
		if ((is_child = fork()) == -1)
		{
			perror("fork:");
			free_pipes(old_pipefd, new_pipefd);
			return ;
		}
		else if (is_child == 0)
		{
			if (cmds[i + 1] != NULL)
				dup2(new_pipefd[1], 1);
			if (i != 0)
				dup2(old_pipefd[0], 0);
			close(old_pipefd[0]);
			close(old_pipefd[1]);
			close(new_pipefd[0]);
			close(new_pipefd[1]);	
			if ((execve(path, cmds[i]->args, env)) == -1)
			{
				perror("execve:");
				free_pipes(old_pipefd, new_pipefd);
				return ;
			}
		}
		close(new_pipefd[1]);
		if (cmds[i + 1] != NULL)
			old_pipefd = new_pipefd;
		i++;
	}
	while (wait(NULL) > 0);
}