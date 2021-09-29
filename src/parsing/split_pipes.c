/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 14:51:05 by pjacob            #+#    #+#             */
/*   Updated: 2021/09/29 15:43:16 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipe(char *line, t_command *cmd)
{
	int	i;
	int	pipe;

	i = -1;
	pipe = count_pipe(line, cmd);
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
		{
			cmd->pp_index[pipe] = i;
			pipe++;
		}
	}
	return (pipe);
}

void	split_pipe(char *s, t_cmd_lst *list, t_command *cmd)
{
	char	**split;
	int		i;
	int		count;

	count = count_pipe(s, cmd) + 1;
	i = 0;
	split = ft_split(s, '|');
	while (split[i])
	{
		list->first->command = split[i];
		i++;
	}
}