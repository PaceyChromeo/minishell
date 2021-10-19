/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacey <pacey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 11:37:56 by misaev            #+#    #+#             */
/*   Updated: 2021/10/19 20:49:53 by pacey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void print_list(lst_env *lst)
{
	while (lst)
	{
		ft_putstr_fd(lst->var_env, 1);
		write(1, "\n", 2);
		lst = lst->next;
	}
}

char *add_quote(char *arg)
{
	int i;
	int j;
	char *str;
	int equals;

	equals = 0;
	str = malloc(sizeof(char) * ft_strlen(arg) + 3);
	if (str == NULL)
		return NULL;
	i = 0;
	j = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '=' && equals == 0)
		{
			equals++;
			str[j++] = arg[i++];
			str[j++] = '"';
		}
		str[j++] = arg[i++];	
	}
	str[j++] = '"';
	str[j] = '\0';

	return str;
}

lst_env *push_env_to_list(char **env)
{
	int i;
	lst_env *lst = empty_list();
	i = 0;
	while (env[i + 2])
		i++;
	while (env[i])
	{
		lst = add_at(lst, add_quote(env[i]), 0);
		i--;
	}
	return lst;
}

void add_var_last(lst_env **lst, char *str)
{
	if (count_equals(str) > 0)
		str = add_quote(str);
	add_at(*lst,str,len_list(*lst));
}

int	check_if_done(lst_env *lst)
{
	lst_env	*prec;

	while (lst)
	{
		prec = lst;
		lst = lst->next;
		if (lst == NULL)
			return (0);
		if (prec->var_env[0] > lst->var_env[0])
			return (1);
	}
	return (0);
}