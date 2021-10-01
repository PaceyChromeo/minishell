/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 14:51:05 by pjacob            #+#    #+#             */
/*   Updated: 2021/09/30 12:13:29 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipe(char *line)
{
	int	i;
	int	pipe;

	i = -1;
	pipe = 0;
	while(line[++i])
	{
		if (line[i] == 34 && line[i + 1] != 34)
		{
			i++;
			while (line[i] != 34 && line[i])
				i++;
		}
		if (line[i] == 39 && line[i + 1] != 39)
		{
			i++;
			while (line[i] != 39 && line[i])
				i++;
		}
		if (line[i] == '|')
			pipe++;
	}
	return (pipe);
}
