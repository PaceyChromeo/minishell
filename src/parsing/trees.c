/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 15:58:43 by pjacob            #+#    #+#             */
/*   Updated: 2021/10/11 10:14:33 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*init_tree(int type)
{
	t_tree	*new_tree;

	new_tree = ft_calloc(1, sizeof(t_tree));
	if (!new_tree)
		return (NULL);
	new_tree->redir_type = type;
	new_tree->cmd = NULL;
	new_tree->args = NULL;
	new_tree->size_args = 0;
	return (new_tree);
}
