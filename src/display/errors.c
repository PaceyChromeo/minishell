/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:26:55 by pjacob            #+#    #+#             */
/*   Updated: 2021/10/18 14:30:44 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

int	error_handler(t_tree *tree)
{
	int	i;

	i = 0;
	if (tree->size_red)
	{
		while (tree->args[i])
		{
			if (!ft_strcmp(tree->args[i], "<") || !ft_strcmp(tree->args[i], "<<")
				|| !ft_strcmp(tree->args[i], ">") || !ft_strcmp(tree->args[i], ">>"))
				return (printf("Syntax error\n"));
			i += 2;
		}
	}
	return (0);
}

int check_forbidden_char(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_sch_forbidden_char(line[i]))
			return (1);
		i++;
	}
	return (0);
}