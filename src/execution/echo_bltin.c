/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_bltin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacey <pacey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 14:56:26 by pacey             #+#    #+#             */
/*   Updated: 2021/10/16 16:42:44 by pacey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static	int	count_good_redir(char **redir)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (redir[i])
	{
		if (!ft_strcmp(redir[i], ">") || !ft_strcmp(redir[i], ">>"))
			count++;
		i += 2;
	}
	return (count);
}

static int	open_file(char *redirection, char *filename)
{
	int	fd;

	if (!access(filename, F_OK))
		return (create_and_open_file(filename));
	else if (!ft_strcmp(redirection, ">"))
	{
		fd = open(filename, O_WRONLY);
		if (!fd)
			return (-1);
		return (fd);
	}
	else if (!ft_strcmp(redirection, ">>"))
	{
		fd = open(filename, O_APPEND);
		if (!fd)
			return (-1);
		return (fd);
	}
	else
		return (0);
}

static int	*create_tab_fd(t_tree *tree)
{
	int	*fd;
	int	i;
	int	x;

	x = 0;
	i = 0;
	fd = ft_calloc(count_good_redir(tree->red), sizeof(int));
	if (!fd)
		return (NULL);
	while (tree->red[i] && tree->red[i + 1] && x < count_good_redir(tree->red))
	{
		if (!ft_strcmp(tree->red[i], ">") || !ft_strcmp(tree->red[i], ">>"))
		{
			fd[x] = open_file(tree->red[i], tree->red[i + 1]);
			x++;
		}
		i += 2;
	}
	return (fd);
}

static	void	print_args_with_fd_tab(t_tree *tree, int *fd_tab, int option)
{
	int	i;
	int	j;

	i = 0;
	if (option)
		i = 1;
	j = 0;
	while (tree->args[i])
	{
		while (fd_tab[j] > 0)
		{
			ft_putstr_fd(tree->args[i], fd_tab[j]);
			if (tree->args[i + 1])
				ft_putchar_fd(' ', fd_tab[j]);
			if (!tree->args[i + 1] && !option)
				ft_putchar_fd('\n', fd_tab[j]);
			j++;
		}
		i++;
	}
}

static void	print_args_with_stdout(t_tree *tree, int option)
{
	int	fd;
	int	i;

	i = 0;
	if (option)
		i = 1;
	fd = STDOUT_FILENO;
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

void	exec_echo(t_tree *tree)
{
	int	option;
	int	*fd_tab;

	fd_tab = NULL;
	option = 0;
	if (!(ft_strcmp(tree->args[i], "-n")))
		option = 1;
	if (count_good_redir(tree->red) > 0)
	{
		fd_tab = create_tab_fd(tree);
		print_args_with_fd_tab(tree, fd_tab, option);
	}
	else
		print_args_with_stdout(tree, option);
}
