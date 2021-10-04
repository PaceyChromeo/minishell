/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 11:58:49 by pjacob            #+#    #+#             */
/*   Updated: 2021/10/04 12:20:54 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_command(char *str)
{
	char	**builtin;
	int		i;

	i = 0;
	builtin = init_builtin_lst();
	if (!builtin)
		return (-1);
	while (i < 8)
	{
		if (strcmp(str, builtin[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}