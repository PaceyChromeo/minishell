/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacey <pacey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:50:45 by pjacob            #+#    #+#             */
/*   Updated: 2021/10/16 16:43:02 by pacey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmp_binaries(char *cmd_value)
{
	char	*cmd_path;

	cmd_path = get_path(cmd_value);
	if (!access(cmd_path, X_OK))
	{
		free(cmd_path);
		return (1);
	}
	free(cmd_path);
	return (0);
}
