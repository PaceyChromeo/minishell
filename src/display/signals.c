/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 16:26:16 by pjacob            #+#    #+#             */
/*   Updated: 2021/10/22 16:26:59 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

void	handler_int(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		global = 130;
	}
	else if (sig == SIGQUIT)
	{
		exit(0);
	}
}
