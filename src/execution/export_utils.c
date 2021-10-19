/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkrifa <hkrifa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 11:27:45 by misaev            #+#    #+#             */
/*   Updated: 2021/10/19 11:42:20 by hkrifa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t destsize)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = 0;
	if (!dest)
		return (0);
	while (src[src_len])
		src_len++;
	if (!destsize)
		return (src_len);
	while (src[i] && i < destsize - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (src_len);
}

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

	prec = lst;
	cur = lst;
	i = 0;
	cell = creat_cell(str);
	if (is_empty_list(lst))
		return (cell);
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
