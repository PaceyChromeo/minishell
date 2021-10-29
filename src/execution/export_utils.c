/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 11:27:45 by misaev            #+#    #+#             */
/*   Updated: 2021/10/29 16:56:53 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/* Cree une cellule pour l ajouter a la liste */
static	t_lenv	*creat_cell(char *str)
{
	t_lenv	*cell;

	cell = malloc(sizeof(t_lenv));
	if (!cell)
		return (NULL);
	cell->var_env = str;
	cell->next = NULL;
	return (cell);
}

/* initialiser une liste vide */
t_lenv	*empty_list(void)
{
	return (NULL);
}

/*Verifier si la liste est vide */
int	is_empty_list(t_lenv *lst)
{
	if (lst == NULL)
		return (1);
	else
		return (0);
}

/* Ajouter un element dans la liste a une position specifique */
t_lenv	*add_at(t_lenv *lst, char *str, int pos)
{
	t_lenv	*prec;
	t_lenv	*cur;
	t_lenv	*cell;
	int		i;
	char	*temp_str;

	temp_str = ft_strdup(str);
	prec = lst;
	cur = lst;
	i = 0;
	cell = creat_cell(temp_str);
	if (is_empty_list(lst))
	{
		return (cell);
	}
	if (pos == 0)
	{
		cell->next = lst;
		return (cell);
	}
	while (i < pos)
	{
		prec = cur;
		cur = cur->next;
		i++;
	}
	prec->next = cell;
	cell->next = cur;
	return (lst);
}

t_lenv	*add_and_push_to_env(t_lenv *lst, char *str, int pos)
{
	t_lenv	*prec;
	t_lenv	*cur;
	t_lenv	*cell;
	int		i;
	char	*quotes;

	quotes = ft_strdup(str);
	prec = lst;
	cur = lst;
	i = 0;
	cell = creat_cell(quotes);
	if (is_empty_list(lst))
	{
		return (cell);
	}
	if (pos == 0)
	{
		cell->next = lst;
		return (cell);
	}
	while (i < pos)
	{
		prec = cur;
		cur = cur->next;
		i++;
	}
	prec->next = cell;
	cell->next = cur;
	return (lst);
}
