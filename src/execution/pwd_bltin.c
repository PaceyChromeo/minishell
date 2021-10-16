/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_bltin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacey <pacey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:30:51 by pacey             #+#    #+#             */
/*   Updated: 2021/10/16 17:34:28 by pacey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pwd(t_tree *tree)
{
	char	*current_path;

	current_path = NULL;
	if (tree->size_args || tree->size_red)
	{
		ft_putstr_fd("Syntax error : no arguments needed\n", STDOUT_FILENO);
		return (-1);
	}
	current_path = getenv("PWD");
	ft_putchar_fd('\n', STDOUT_FILENO);
	ft_putstr_fd(current_path, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	return (1);
}