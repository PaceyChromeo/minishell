/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaev <misaev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 11:55:08 by misaev            #+#    #+#             */
/*   Updated: 2021/10/28 14:19:01 by misaev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	strlen_var_arg(char *str)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[i] != '=')
		i++;
	if (str[i] == '\0')
		return (0);
	i++;
	while (str[i] != '\0')
	{
		i++;
		j++;
	}
	return (j - 2);
}

void	set_at(lst_env *lst, char *str, int pos)
{
	int	i;

	i = 0;
	if (is_empty_list(lst))
		return ;
	while (i < pos)
	{
		i++;
		lst = lst->next;
	}
	lst->var_env = ft_strdup(str);
	free(str);
}

lst_env	*ft_lstdup(lst_env *lst)
{
	lst_env	*tmp;
	char *quotes;
	int i;
	
	i = 0; 
	quotes = NULL;
	tmp = empty_list();
	while(lst)
	{
		if (count_equals(lst->var_env) == 0)
			quotes = ft_strdup(lst->var_env);
		else
			quotes = add_quote(lst->var_env);	
		tmp = add_at(tmp, quotes, i);
		lst = lst->next; 
		free(quotes);
		i++;
	}
	return (tmp);
}
/* Free une cellule de la liste */

lst_env	*free_at(lst_env *lst, int pos)
{
	lst_env	*prec;
	lst_env	*cur;
	int		i;

	cur = lst;
	prec = lst;
	i = 0;
	if (is_empty_list(lst))
		return (NULL);
	if (pos == 0)
	{
		lst = lst->next;
		free(cur->var_env);
		free(cur);
		return (lst);
	}
	while (i < pos)
	{
		prec = cur;
		cur = cur->next;
		i++;
	}
	prec->next = cur->next;
	free(cur->var_env);
	free(cur);
	return (lst);
}