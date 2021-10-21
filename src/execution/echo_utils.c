/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 14:18:21 by misaev            #+#    #+#             */
/*   Updated: 2021/10/21 11:03:40 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	echo_option(char *full_cmd, int i)
{
	if (full_cmd == NULL)
		return (0);
	if (ft_strstr(full_cmd, "-n") != 0)
	{
		while (full_cmd[i] == '-')
		{
			i++;
			if (full_cmd[i] != 'n' && full_cmd[i] != 'e')
				return (0);
			while (full_cmd[i] != ' ' && full_cmd[i])
			{
				if (full_cmd[i] != 'n' && full_cmd[i] != 'e')
					return (0);
				i++;
			}
			i++;
		}
		return (i);
	}
	return (0);
}

int	print_quote(char *cmd, int i, char c)
{
	if (c == 39)
	{
		while (cmd[i] != 39 && cmd[i])
		{
			ft_putchar_fd(cmd[i], STDOUT_FILENO);
			i++;
		}
	}
	if (c == 34)
	{
		while (cmd[i] != 34 && cmd[i])
		{
			if (cmd[i] == '$' && (ft_isalpha(cmd[i + 1])
					|| ft_isnum(cmd[i + 1]) || cmd[i + 1] == '_'))
				i = echo_print_env(cmd, i + 1) + 1;
			if (cmd[i] != 34)
				ft_putchar_fd(cmd[i], STDOUT_FILENO);
			else
				break ;
			i++;
		}
	}
	return (i);
}

int	echo_print_env(char *cmd, int i)
{
	char	*env;

	env = get_env(cmd, i);
	ft_putstr_fd(env, STDOUT_FILENO);
	while (ft_isalpha(cmd[i]) || ft_isnum(cmd[i]) || cmd[i] == '_')
		i++;
	return (i - 1);
}
