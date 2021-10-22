/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 14:25:27 by pjacob            #+#    #+#             */
/*   Updated: 2021/10/22 16:27:35 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	exec_export(t_tree *tree, char **env)
{
	int		i;
	int		x;
	char	***exp_split;

	(void)env;
	i = 1;
	x = 0;
	if (tree->size_args > 1)
	{
		exp_split = ft_calloc(tree->size_args, sizeof(char **));
		while (i < tree->size_args)
		{
			exp_split[x] = ft_split(tree->args[i], '=');
			i++;
			x++;
		}
		exp_split[x] = NULL;
	}
}
