/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:26:55 by pjacob            #+#    #+#             */
/*   Updated: 2021/10/29 16:01:30 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	signal_set(t_tree *tree)
{
	int	i;

	i = 0;
	if (tree->size_args)
	{
		if (tree->cmd_type == tree_nocmd && ft_strcmp(tree->f_cmd, "$?")
			&& ft_strcmp(tree->f_cmd, "$?+$?")
			&& ft_strcmp(tree->f_cmd, "$? + $?"))
		{
			printf("minishell: command not found\n");
			g_global = 127;
			return (g_global);
		}
		else if (tree->cmd_type == tree_nocmd && (ft_strcmp(tree->f_cmd, "$?") == 0 || ft_strcmp(tree->f_cmd, "$? + $?") == 0) 
			&& ft_strcmp(tree->f_cmd, "$?+$?") != 0)
		{
			printf("minishell: %d: command not found\n", g_global);
			g_global = 127;
			return (g_global);
		}
		else if (tree->cmd_type == tree_nocmd
			&& ft_strcmp(tree->f_cmd, "$?+$?") == 0)
		{
			printf("minishell: %d+%d: command not found\n", g_global, g_global);
			g_global = 127;
			return (g_global);
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
		while (i < tree->size_red)
		{
			if ((!ft_strcmp(tree->red[i], "<") || !ft_strcmp(tree->red[i], "<<")
					|| !ft_strcmp(tree->red[i], ">")
					|| !ft_strcmp(tree->red[i], ">>")) && i + 1 < tree->size_red)
				i += 2;
			else
			{
				g_global = 258;
				return (printf("Syntax error near token \"%s\"\n", tree->red[i]));
			}
		}
		i = 1;
		while (i < tree->size_red)
		{
			if (tree->red[i][0] != '<' && tree->red[i][0] != '>')
					i += 2;
			else
			{
				g_global = 258;
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
		ret = signal_set(tree);
	if (tree->size_red && ret == 0)
		ret = error_redirections(tree);
	return (ret);
}

int	check_forbidden_char(char *line)
{
	int		i;
	char	c;

	i = 0;
	while (line[i])
	{
		if (ft_sch_forbidden_char(line[i]))
		{
			g_global = 1;
			ft_putstr_fd("Invalid character\n", STDOUT_FILENO);
			return (g_global);
		}
		if (line[i] != ' ')
			c = line[i];
		i++;
	}
	if (c == '|')
	{
		g_global = 258;
		ft_putstr_fd("Syntax error invalid pipe\n", STDOUT_FILENO);
		return (g_global);
	}
	return (0);
}
