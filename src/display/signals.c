/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 16:26:16 by pjacob            #+#    #+#             */
/*   Updated: 2021/10/27 10:55:20 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_signals(int sig)
{
	int		exec;
	char	**path = NULL;
	int	pid;

	path = (char **)malloc(sizeof(char *) * 2 + 1);
	path[0] = ft_strdup("/bin/stty");
	path[1] = ft_strdup("-echoctl");
	path[2] = 0;
	if (sig == SIGINT || sig == SIGQUIT)
	{
		pid = fork();
		if (pid == 0)
		{
			if(sig == SIGINT)
				printf("\n");
			exec = execve(path[0], path, NULL);
			if (exec == -1)
				perror("execve");
		}
		free_tab(path);
		wait(NULL);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		if (sig == SIGINT)
      		g_global = 1;
		else
			g_global  = 127;	  
	}
}

void	handler_child(int sig)
{
	//int		exec;
	//char	**path = NULL;
	//int		pid;
	
	//path = (char **)malloc(sizeof(char *) * 2 + 1);
	//path[0] = ft_strdup("/bin/stty");
	//path[1] = ft_strdup("-echoctl");
	//path[2] = 0;
	if (sig == SIGINT || sig == SIGQUIT)
	{
		// pid = fork();
		// if (pid == 0)
		// {
		// 	printf("\n");
		// 	exec = execve(path[0], path, NULL);
		// 	if (exec == -1)
		// 		perror("execve");
		// }
		//free_tab(path);
		if(sig == SIGINT)
			g_global += 0;
		else if (sig == SIGQUIT)
			g_global += 1;
		wait(NULL);
		//rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

