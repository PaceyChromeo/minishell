/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 11:27:45 by misaev            #+#    #+#             */
/*   Updated: 2021/10/27 16:58:14 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/* Cree une cellule pour l ajouter a la liste */
static	lst_env	*creat_cell(char *str);

static	lst_env	*creat_cell(char *str)
{
	lst_env	*cell;

	cell = malloc(sizeof(lst_env));
	if (!cell)
		return (NULL);
	cell->var_env = str;
	cell->next = NULL;
	return (cell);
}

/* initialiser une liste vide */

lst_env	*empty_list(void)
{
	return (NULL);
}

/*Verifier si la liste est vide */

int	is_empty_list(lst_env *lst)
{
	if (lst == NULL)
		return (1);
	else
		return (0);
}

/* Ajouter un element dans la liste a une position specifique */

lst_env	*add_at(lst_env *lst, char *str, int pos)
{
	lst_env	*prec;
	lst_env	*cur;
	lst_env	*cell;
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

lst_env	*add_and_push_to_env(lst_env *lst, char *str, int pos, int d)
{
	lst_env	*prec;
	lst_env	*cur;
	lst_env	*cell;
	int		i;
	char *quotes;

	if (d)
		quotes = add_quote(str);
	else
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
