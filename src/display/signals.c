/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 16:26:16 by pjacob            #+#    #+#             */
/*   Updated: 2021/10/27 13:32:21 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_signals(int sig)
{
	if (sig == SIGINT || sig == SIGQUIT)
	{
		printf("\n");
		printf("\e[2K");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGINT)
		g_global = 1;
	else
		g_global  = 127;
}

void	handler_child(int sig)
{
	if (sig == SIGINT || sig == SIGQUIT)
	{
		printf("\n");
		printf("\e[2K");
		//rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

