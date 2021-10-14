/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacey <pacey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:20:04 by pjacob            #+#    #+#             */
/*   Updated: 2021/10/14 20:44:22 by pacey            ###   ########.fr       */
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
		tab[i] = ft_strjoin(tab[i], "/");
	i = -1;
	while (tab[++i])
		tab[i] = ft_strjoin(tab[i], cmd);
	i = -1;
	while (tab[++i])
	{
		if (access(tab[i], F_OK) == 0)
		{
			good_path = ft_strdup(tab[i]);
			free_tab(tab);
			return (good_path);
		}
	}
	free_tab(tab);
	return (NULL);
}
