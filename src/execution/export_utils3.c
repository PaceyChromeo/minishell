/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 11:43:38 by misaev            #+#    #+#             */
/*   Updated: 2021/10/29 16:55:03 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	sort_env_var(t_lenv **lst)
{
	t_lenv	*prec;
	t_lenv	*cur;
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

void	add_new(t_lenv **lst, char *new_content, char *var_dest)
{
	int		i;
	t_lenv	*temp;

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
	if (temp == NULL)
	{
		*lst = add_at(*lst, var_dest, 0);
		add_new(lst, getcwd(NULL, 0), var_dest);
	}
}

char	*add_content_to_var(char *dest, char *content_to_add)
{
	int		i;
	int		j;
	char	*new_dest_content;

	j = 0;
	i = 0;
	while (dest[i] != '=' && dest[i])
		i++;
	if (dest[i])
	{
		i++;
		new_dest_content = ft_calloc(sizeof(char),
				(ft_strlen(content_to_add) + i + 1));
	}
	else
		new_dest_content = ft_calloc(sizeof(char),
				(ft_strlen(content_to_add) + i + 2));
	i = 0;
	while (dest[i] != '=' && dest[i])
	{
		new_dest_content[i] = dest[i];
		i++;
	}
	if (dest[i])
		new_dest_content[i] = dest[i];
	else
		new_dest_content[i] = '=';
	i++;
	if (content_to_add == NULL)
		new_dest_content[i] = '\0';
	else
	{
		while (content_to_add[j] != '\0')
			new_dest_content[i++] = content_to_add[j++];
		new_dest_content[i] = '\0';
	}
	free (dest);
	return (new_dest_content);
}
