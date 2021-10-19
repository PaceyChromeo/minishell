/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacey <pacey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 11:43:38 by misaev            #+#    #+#             */
/*   Updated: 2021/10/19 20:50:15 by pacey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

lst_env *sort_env_var(lst_env **lst)
{
	lst_env *prec = *lst;
	lst_env *cur = *lst;
	char *temp_str = NULL;
	cur = cur->next;
	int i;
	while(check_if_done(*lst) == 1)
	{
		i = 0;
		if (prec->var_env[i] == cur->var_env[i])
		{
			while(prec->var_env[i] == cur->var_env[i])
				i++;
		}
		if (prec->var_env[i] > cur->var_env[i])
		{
			temp_str = ft_strdup(cur->var_env);
			cur->var_env = ft_strdup(prec->var_env);
			prec->var_env = ft_strdup(temp_str);
			prec = *lst;
			cur = (*lst)->next;
			if (cur == NULL)
				break;
		}
		else
		{
			prec = cur;
			cur = cur->next;
			if (cur == NULL)
				break;
		}
	}
	return *lst;
}

lst_env *push_env_to_list_declare_x(lst_env *d_env)
{
	int i;
	lst_env *lst = empty_list();
	i = 0;
	while (d_env)
	{
		lst = add_at(lst, ft_strjoin("declare -x ",d_env->var_env), i);
		i++;
		d_env = d_env->next;
	}
	return lst;
}

char *add_new(char *update, char *dest)
{
	int i;
	int j;

	i = 0;
	j = 0;
	char *dest2 = malloc(sizeof(char *) * (ft_strlen(dest) + ft_strlen(update) + 1));
	ft_strlcpy(dest2, dest, ft_strlen(dest));
	while (dest2[i + 1] != '\0')
		i++;
	i++;
	while(update[j])
	{
		dest2[i] = update[j];
		i++;
		j++;
	}
	dest2[i] = '"';
	i++;
	dest2[i] = '\0';
	return dest2;
}

lst_env *update_var(lst_env **lst, char *var_name, char *update)
{
	lst_env *temp = *lst;
	(void)update;
	
	while (temp->next != NULL)
	{
		temp = temp->next;
		if (ft_strstr_equalizer(temp->var_env,var_name) != 0)
		{
			temp->var_env = add_new(update, temp->var_env);
			break;
		}
	}
	return temp;
}
