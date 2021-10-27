/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:01:54 by misaev            #+#    #+#             */
/*   Updated: 2021/10/27 16:28:03 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	count_quotes(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"')
			j++;
		i++;
	}
	return (j);
}

int	count_equals(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			j++;
		i++;
	}
	return (j);
}

int	check_export_args_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' || str[i] != '\0')
	{
		if (str[i] == '+' && str[i + 1] == '=')
		{
			return (2);
		}
		if (str[i] == '=' || str[i] == '\0')
			break ;
		if (ft_isalpha(str[i]) == 1 || str[i] == '_'
			|| (ft_isnum(str[i]) == 1 && i > 0))
			i++;
		else
			return (1);
	}
	return (0);
}

int	check_if_arg_in_env(char *var_name, lst_env *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		if (ft_strstr_int(lst->var_env, var_name) != 0)
			return (i);
		lst = lst->next;
		i++;
	}
	return (0);
}
