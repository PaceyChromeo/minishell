/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:50:45 by pjacob            #+#    #+#             */
/*   Updated: 2021/10/18 13:36:02 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmp_binaries(char *cmd_value)
{
	char const	*cmd_path;

	cmd_path = get_path(cmd_value);
	if (cmd_path)
	{
		if (!access(cmd_path, X_OK))
		{
			free((void *)cmd_path);
			return (1);
		}
	}
	return (0);
}
