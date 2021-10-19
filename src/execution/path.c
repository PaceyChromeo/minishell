/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:20:04 by pjacob            #+#    #+#             */
/*   Updated: 2021/10/19 11:09:17 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(char *cmd)
{
	char	*path;
	char	*good_path;
	char	**tab;
	int		i;

	i = -1;
	path = getenv("PATH");
	tab = ft_split(path, ':');
	while (tab[++i])
		tab[i] = ft_realloc(tab[i], "/");
	i = -1;
	while (tab[++i])
		tab[i] = ft_realloc(tab[i], cmd);
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
	return (NULL);
}
