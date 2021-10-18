/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 10:05:47 by misaev            #+#    #+#             */
/*   Updated: 2021/10/18 16:52:07 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void echo(char **arg)
{
	int i;
	int opt;

	opt = 0;
	i = 1;
	if (echo_option(arg[i]) == 1 && arg[i] != NULL)
	{
		opt = 1;
		i++;
	}
	while(arg[i] != '\0')
	{
		ft_putstr_fd(arg[i], 1);
		if (arg[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (opt != 1)
		write(1, "\n", 1);
}

void cd(char *path)
{
	if (access(path, F_OK) == 0)
		chdir(path);
	else
		perror(path);
}

void pwd(void)
{
	char *buf;
	buf = NULL;
	buf = getcwd(NULL, 0);
	if (buf == NULL)
		 perror(buf);
	else
	{
		ft_putstr_fd(buf, STDOUT_FILENO);
		write(STDOUT_FILENO, "\n", 1);
	}
}