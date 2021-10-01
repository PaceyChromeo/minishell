/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 14:25:51 by pjacob            #+#    #+#             */
/*   Updated: 2021/09/29 15:42:14 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*create_command(char *command)
{
	t_command	*new;
	
	new = malloc(sizeof(*new) * 1);
	if (!new)
		return (NULL);
	new->command = command;
	new->next = NULL;
	return (new);
}

int		count_lst(t_cmd_lst *list)
{
	t_command	*cmd;
	int	i;

	cmd = list->first;
	i = 1;
	if (!cmd)
		return (0);
	while (cmd->next)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

t_command	*last_cmd(t_cmd_lst	*list)
{
	t_command	*last;

	last = list->first;
	if (!last)
		return (NULL);
	while (last->next)
		last = last->next;
	return (last);
}

void	add_back(t_cmd_lst *list, t_command	*new)
{
	t_command	*last;
	
	last = malloc(sizeof(*new) * 1);
	if (!new)
		return ;
	last = last_cmd(list);
	last->next = new;
	new->last = last;
	new->next = NULL;
}