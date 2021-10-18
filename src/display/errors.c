/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkrifa <hkrifa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:26:55 by pjacob            #+#    #+#             */
/*   Updated: 2021/10/18 15:37:07 by hkrifa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

int	error_handler(t_tree *tree)
{
	int	i;

	i = 0;
	if (tree->size_red)
	{
		while (tree->red[i])
		{
			
			if ((!ft_strcmp(tree->red[i], "<") || !ft_strcmp(tree->red[i], "<<")
				|| !ft_strcmp(tree->red[i], ">") || !ft_strcmp(tree->red[i], ">>")) && tree->red[i + 1])
				i += 2;
			else
				return (printf("Syntax error\n"));
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