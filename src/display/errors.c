/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:26:55 by pjacob            #+#    #+#             */
/*   Updated: 2021/10/26 12:27:19 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_args(t_tree *tree)
{
	int	i;

	i = 0;
	if (tree->size_args)
	{
		//printf("cmd_value: %s\n", tree->f_cmd);
		if (tree->cmd_type == tree_nocmd && ft_strcmp(tree->args[0], "$?") != 0
			&& ft_strcmp(tree->f_cmd, "$?+$?") != 0
			&& ft_strcmp(tree->f_cmd, "$? + $?") != 0 )
		{
			global = 127;
			return (printf("minishell: command not found\n"));
		}
		else if (tree->cmd_type == tree_nocmd && (ft_strcmp(tree->args[0], "$?") == 0 || ft_strcmp(tree->f_cmd, "$? + $?") == 0) && ft_strcmp(tree->f_cmd, "$?+$?") != 0)
		{
		//	printf("cmd_value: %s\n", tree->cmd_value);
		//	global = 127;
			return (printf("minishell: %d: command not found\n", global));
		}
		else if (tree->cmd_type == tree_nocmd
			&& ft_strcmp(tree->f_cmd, "$?+$?") == 0)
		{
		//	global = 127;
			return (printf("minishell: %d+%d: command not found\n", global, global));
		}
	}
	return (0);
}

int	error_redirections(t_tree *tree)
{
	int	i;

	i = 0;
	if (tree->size_red)
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
				return (printf("Syntax error near token \"%s\"\n", tree->red[i]));
			}
		}
		i = 1;
		while (tree->red[i])
		{
			if ((tree->red[i][0] != '<' && tree->red[i][0] != '>'))
					i += 2;
			else
			{
				global = 1;
				return (printf("Syntax error unexpected token\n"));
			}
		}
	}
	return (0);
}

int	error_handler(t_tree *tree)
{
	int	ret;

	ret = 0;
	if (tree->size_args)
		ret = error_args(tree);
	if (tree->size_red && ret == 0)
		ret = error_redirections(tree);
	return (ret);
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
