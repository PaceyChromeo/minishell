/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_bltin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacey <pacey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:00:08 by pacey             #+#    #+#             */
/*   Updated: 2021/10/16 17:38:19 by pacey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	exec_cd(t_tree *tree)
{
	char *current_path;
	char *path_to_reach;

	if (tree->size_red > 0)
	{
		ft_putstr_fd("Syntax error : cd [path]\n", STDOUT_FILENO);
		return (-1);
	}
	if (!tree->size_args)
		return (0);
	if (tree->size_args > 1)
	{
		ft_putstr_fd("Too many arguments\n", STDOUT_FILENO);
		return (1);
	}
	current_path = getenv("PWD");
	path_to_reach = ft_strjoin(current_path, "/");
	path_to_reach = ft_strjoin(current_path, tree->args[0]);
	/* checker si le path est correct. 
	Si oui, y aller. Si non, aucun fichier ou dossier de ce type */
	printf("path to reach : %s\n", path_to_reach);
	return (2);
}