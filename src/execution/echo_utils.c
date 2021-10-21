/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 14:18:21 by misaev            #+#    #+#             */
/*   Updated: 2021/10/21 18:02:06 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	echo_option(char *full_cmd, int i)
{
	int	x;

	x = i;
	if (full_cmd == NULL)
		return (0);
	if (ft_strstr(full_cmd, "-n") != 0)
	{
		while (full_cmd[x] == '-')
		{
			x++;
			if (full_cmd[x] != 'n' && full_cmd[x] != 'e')
				return (0);
			while (full_cmd[x] != ' ' && full_cmd[x])
			{
				if (full_cmd[x] != 'n' && full_cmd[x] != 'e')
					return (0);
				x++;
			}
			x++;
		}
		return (x - i);
	}
	return (0);
}

static int	echo_print_env(char *cmd, int i)
{
	ft_putstr_fd(get_env(cmd, i), STDOUT_FILENO);
	while (ft_isalpha(cmd[i]) || ft_isnum(cmd[i]) || cmd[i] == '_')
		i++;
	return (i - 1);
}

static int	print_quote(char *cmd, int i, char c)
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

void	trim_redirections(t_tree *tree)
{
	int	i;
	int	j;
	int	x;
	int y;

	x = 0;
	i = 4;
	j = 0;
	while (tree->f_cmd[i] && x < tree->size_red)
	{
		while (tree->f_cmd[i] == ' ')
			i++;
		y = 0;
		if (tree->f_cmd[i] == tree->red[x][y])
		{
			printf("1 - tree->f_cmd[%d] : %c\n", i, tree->f_cmd[i]);
			while (tree->f_cmd[i] == tree->red[x][y] && tree->f_cmd[i])
			{
				i++;
				y++;
			}
			x++;
			while (tree->f_cmd[i] == ' ')
				i++;
			y = 0;
			printf("2 - tree->f_cmd[%d] : %c\n", i, tree->f_cmd[i]);
			while (tree->f_cmd[i] == tree->red[x][y] && tree->f_cmd[i])
			{
				i++;
				y++;
			}
			x++;
		}
		while (tree->f_cmd[i] == ' ')
			i++;
		printf("[%d] : %c\n", i , tree->f_cmd[i]);
		if (x < tree->size_red)
		{
			while (tree->f_cmd[i] != ' ' && tree->f_cmd[i])
			{
				printf("3 - tree->f_cmd[%d] : %c\n", i, tree->f_cmd[i]);
				tree->f_cmd[j] = tree->f_cmd[i];
				i++;
				j++;
			}
		}
	}
	tree->f_cmd[j] = '\0';
}

void	exec_echo(t_tree *tree, int i)
{
	while (tree->f_cmd[i])
	{
		if (tree->f_cmd[i] != 34 && tree->f_cmd[i] != 39
			&& tree->f_cmd[i] != '$')
			ft_putchar_fd(tree->f_cmd[i], STDOUT_FILENO);
		if (tree->f_cmd[i] == 39 && tree->f_cmd[i + 1])
			i = print_quote(tree->f_cmd, i + 1, 39);
		if (tree->f_cmd[i] == 34 && tree->f_cmd[i + 1])
			i = print_quote(tree->f_cmd, i + 1, 34);
		if (tree->f_cmd[i] == '$' && (ft_isalpha(tree->f_cmd[i + 1])
				|| ft_isnum(tree->f_cmd[i + 1]) || tree->f_cmd[i + 1] == '_'))
			i = echo_print_env(tree->f_cmd, i + 1);
		i++;
	}

}
