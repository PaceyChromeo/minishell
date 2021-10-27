/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 11:37:56 by misaev            #+#    #+#             */
/*   Updated: 2021/10/27 16:59:26 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*add_quote(char *arg)
{
	int		i;
	int		j;
	char	*str;
	int		equals;

	equals = 0;
	str = ft_calloc(sizeof(char), ft_strlen(arg) + 3);
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '=' && equals == 0 && arg[i + 1] == 0)
		{
			str[j++] = arg[i];
			str[j++] = '"';
			break ;
		}
		else if (arg[i] == '=' && equals == 0)
		{
			equals++;
			str[j++] = arg[i++];
			str[j++] = '"';
		}
		str[j++] = arg[i++];
	}
	str[j++] = '"';
	str[j++] = '\0';
	return (str);
}

lst_env	*push_env_to_list(char **env, int d)
{
	int		i;
	lst_env	*lst;

	lst = empty_list();
	i = 0;
	while (env[i + 2] != '\0')
		i++;
	while (env[i])
	{
		lst = add_and_push_to_env(lst, env[i], 0, d);
		i--;
	}
	return (lst);
}

void	add_var_last(lst_env **lst, char *str, int export)
{
	int		i;
	char	*rstr;
	char	**var;

	i = 0;
	rstr = add_quote(str);
	var = ft_split(rstr, '=');
	if (check_if_arg_in_env(var[0], *lst) == 0 && export == 0)
	{
		free(rstr);
		free_tab(var);
		return ;
	}
	if (check_if_arg_in_env(rstr, *lst) != 0)
		add_new(lst, var[1], var[0]);
	else
		add_at(*lst, rstr, len_list(*lst));
	free(rstr);
	free_tab(var);
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
