/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaev <misaev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 11:55:08 by misaev            #+#    #+#             */
/*   Updated: 2021/10/25 17:33:00 by misaev           ###   ########.fr       */
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
