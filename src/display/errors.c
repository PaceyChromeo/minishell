/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:26:55 by pjacob            #+#    #+#             */
/*   Updated: 2021/10/22 14:12:27 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

int	error_handler(t_tree *tree)
{
	int	i;

	i = 0;
	printf("cmd_value: %s\n", tree->args[0]);
	if (tree->cmd_type == tree_nocmd && ft_strcmp(tree->args[0], "$?") != 0 && ft_strcmp(tree->f_cmd, "$?+$?") != 0 && ft_strcmp(tree->f_cmd, "$? + $?") != 0 )
	{
		global = 127;
		return (printf("bash: command not found\n"));
	}
	else if (tree->cmd_type == tree_nocmd && ft_strcmp(tree->args[0], "$?") == 0 && ft_strcmp(tree->f_cmd, "$?+$?") != 0 && ft_strcmp(tree->f_cmd, "$? + $?") == 0)
	{
	//	printf("cmd_value: %s\n", tree->cmd_value);
	//	global = 127;
		return ( printf("bash: %d: command not found\n", global));
	}
	else if (tree->cmd_type == tree_nocmd && ft_strcmp(tree->f_cmd, "$?+$?") == 0)
	{
	//	global = 127;
		return ( printf("bash: %d+%d: command not found\n", global, global));
	}

	
	else if (tree->size_red)
	{
		while (tree->red[i])
		{
			if ((!ft_strcmp(tree->red[i], "<") || !ft_strcmp(tree->red[i], "<<")
					|| !ft_strcmp(tree->red[i], ">")
					|| !ft_strcmp(tree->red[i], ">>")) && tree->red[i + 1])
				i += 2;
			else
			{
				global = 1;
				return (printf("Syntax error\n"));
			}
		}
	}
	return (0);
}

int	check_forbidden_char(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_sch_forbidden_char(line[i]))
		{
			global = 1;
			ft_putstr_fd("Invalid character\n", STDOUT_FILENO);
			return (1);
		}
		i++;
	}
	return (0);
}
