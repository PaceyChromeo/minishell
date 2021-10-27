/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkrifa <hkrifa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 16:26:16 by pjacob            #+#    #+#             */
/*   Updated: 2021/10/27 13:59:44 by hkrifa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_signals(int sig)
{
	if (sig == SIGINT)
	{
		printf("\e[2K");
		rl_on_new_line();
		rl_redisplay();
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();	  	
	}
	else if (sig == SIGQUIT)
	{
		printf("\e[2K");
		rl_on_new_line();
		rl_redisplay();
	}
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

