/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 18:48:23 by hkrifa            #+#    #+#             */
/*   Updated: 2021/10/18 15:55:45 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char	*line;
	int		cmd_nbr;
	int		i;
	
	i = 0;
    while (1)
	{
		line = display_prompt();
		if (!check_forbidden_char(line))
		{
			cmd_nbr = count_pipes(line, '|');
			if (!cmd_nbr)
				treat_single_cmd(line, envp);
			else
				treat_multi_cmd(line, cmd_nbr, envp);
		}
	}
	return (0);
}
