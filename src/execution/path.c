/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkrifa <hkrifa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:20:04 by pjacob            #+#    #+#             */
/*   Updated: 2021/11/02 17:12:29 by hkrifa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_tab_path(char **tab, char *cmd)
{
	int	i;

	i = -1;
	while (tab[++i])
		tab[i] = ft_realloc(tab[i], "/");
	i = -1;
	while (tab[++i])
		tab[i] = ft_realloc(tab[i], cmd);
	return (tab);
}

static char	*ft_str_chr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
			return ((char *)str + i + 1);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)str + i);
	return (NULL);
}

char	*ft_getenv(char *env, t_var *var)
{
	t_lenv	*tmp_lst;

	tmp_lst = var->env;
	while (tmp_lst)
	{
		if (ft_strstr_int(tmp_lst->var_env, env))
			return (ft_str_chr(tmp_lst->var_env, '='));
		tmp_lst = tmp_lst->next;
	}
	return (NULL);
}

char	*get_path(char *cmd, t_var *var)
{
	char	*path;
	char	*good_path;
	char	**tab;
	int		i;

	path = ft_getenv("PATH", var);
	if (path)
	{
		tab = ft_split(path, ':');
		tab = get_tab_path(tab, cmd);
		i = -1;
		while (tab[++i])
		{
			good_path = ft_strdup(tab[i]);
			if (access(tab[i], F_OK) == 0)
			{
				free_tab(tab);
				return (good_path);
			}
			free(good_path);
		}
		free_tab(tab);
	}
	return (NULL);
}
