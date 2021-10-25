/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaev <misaev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 11:43:38 by misaev            #+#    #+#             */
/*   Updated: 2021/10/25 17:32:45 by misaev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	sort_env_var(lst_env **lst)
{
	lst_env	*prec;
	lst_env	*cur;
	char	*temp_str;
	int		i;

	temp_str = NULL;
	cur = *lst;
	prec = *lst;
	cur = cur->next;
	while (check_if_done(*lst) == 1)
	{
		i = 0;
		if (prec->var_env[i] == cur->var_env[i])
		{
			while (prec->var_env[i] == cur->var_env[i])
				i++;
		}
		if (prec->var_env[i] > cur->var_env[i])
		{
			temp_str = cur->var_env;
			cur->var_env = prec->var_env;
			prec->var_env = temp_str;
			prec = *lst;
			cur = (*lst)->next;
			if (cur == NULL)
				break ;
		}
		else
		{
			prec = cur;
			cur = cur->next;
			if (cur == NULL)
				break ;
		}
	}
}

lst_env	*push_env_to_list_declare_x(lst_env *d_env)
{
	int		i;
	char	*declare;
	char	*x;
	lst_env	*lst;

	lst = empty_list();
	i = 0;
	x = "declare -x ";
	while (d_env)
	{
		declare = ft_strjoin(x, d_env->var_env);
		lst = add_at(lst, declare, i);
		i++;
		d_env = d_env->next;
	}
	free_list (d_env);
	return (lst);
}

void	add_new(lst_env **lst, char *new_content, char *var_dest)
{
	int		i;
	lst_env	*temp;

	i = 0;
	temp = *lst;
	while (temp != NULL)
	{
		if (ft_strstr_int(temp->var_env, var_dest) != 0)
		{
			temp->var_env = add_content_to_var(temp->var_env, new_content);
			break ;
		}
		temp = temp->next;
	}
}

char	*add_content_to_var(char *dest, char *content_to_add)
{
	int		i;
	int		j;
	char	*new_dest_content;

	j = 0;
	i = 0;
	while (dest[i] != '=')
		i++;
	i++;
	new_dest_content = ft_calloc(sizeof(char), (ft_strlen(content_to_add) + i + 3));
	i = 0;
	while (dest[i] != '=')
	{
		new_dest_content[i] = dest[i];
		i++;
	}
	new_dest_content[i] = dest[i];
	i++;
	while (content_to_add[j] != '\0')
		new_dest_content[i++] = content_to_add[j++];
	new_dest_content[i] = '\0';
	free (dest);
	return (new_dest_content);
}
