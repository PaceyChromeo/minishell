/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 09:59:51 by pjacob            #+#    #+#             */
/*   Updated: 2021/09/29 10:45:55 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	count_quote(char *s, t_command *cmd)
{
	int	i;

	i = 0;
	cmd->nb_dq = 0;
	cmd->nb_sq = 0;
	while (s[i])
	{
		if (s[i] == 34)
			cmd->nb_dq++;
		if (s[i] == 39)
			cmd->nb_sq++;
		i++;
	}
}

static int	quote_mutex(char *s, int mutex, int i)
{
	while (s[++i])
	{
		if (s[i] == 34 && !mutex)
		{
			mutex = 1;
			while (s[i] && mutex)
			{
				i++;
				if (s[i] == 34)
					mutex = 0;
			}
		}
		if (s[i] == 39 && !mutex)
		{
			mutex = 1;
			while (s[i] && mutex)
			{
				i++;
				if (s[i] == 39)
					mutex = 0;
			}
		}
	}
	return (mutex);
}

static int	check_error_quote(t_command *cmd, char *s)
{
	int	i;

	i = -1;
	if ((cmd->nb_dq % 2 && !cmd->nb_sq) || (cmd->nb_sq % 2 && !cmd->nb_dq))
		return (1);
	else
	{
		return (quote_mutex(s, 0, -1));
	}
	return (0);
}

static t_command	*init_indexes(t_command *cmd, char *s)
{
	cmd = malloc(sizeof(t_command) * 1);
	if (!cmd)
		return (NULL);
	count_quote(s, cmd);
	if (cmd->nb_sq > 0)
	{
		cmd->single_q = malloc(sizeof(int) * cmd->nb_sq);
		if (!cmd->single_q)
			cmd->single_q = NULL;
	}
	else
		cmd->single_q = NULL;
	if (cmd->nb_dq > 0)
	{
		cmd->double_q = malloc(sizeof(int) * cmd->nb_dq);
		if (!cmd->double_q)
			cmd->double_q = NULL;
	}
	else
		cmd->double_q = NULL;
	if (!cmd->single_q && !cmd->double_q)
		return (NULL);
	return (cmd);
}

t_command	*find_indexes(char *s)
{
	t_command	*cmd;
	int			i;
	int			x;
	int			y;

	cmd = NULL;
	i = -1;
	x = 0;
	y = 0;
	cmd = init_indexes(cmd, s);
	if (!cmd)
		return (NULL);
	while (s[++i])
	{
		if (s[i] == 34)
			cmd->double_q[x++] = i;
		if (s[i] == 39)
			cmd->single_q[y++] = i;
	}
	if (check_error_quote(cmd, s))
		return (NULL);
	return (cmd);
}
