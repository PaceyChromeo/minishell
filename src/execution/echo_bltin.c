/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_bltin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 14:56:26 by pacey             #+#    #+#             */
/*   Updated: 2021/10/18 11:21:43 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	exec_echo(t_tree *tree, int fd)
{
	int	i;
	int option;

	option = 0;
	i = 0;
	if (!(ft_strcmp(tree->args[0], "-n")))
	{
		i++;
		option++;
	}
	while (tree->args[i])
	{
		ft_putstr_fd(tree->args[i], fd);
		if (tree->args[i + 1])
			ft_putchar_fd(' ', fd);
		if (!tree->args[i + 1] && !option)
			ft_putchar_fd('\n', fd);
		i++;
	}
}
