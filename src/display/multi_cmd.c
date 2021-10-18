/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:47:27 by pjacob            #+#    #+#             */
/*   Updated: 2021/10/18 15:56:48 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

int	treat_multi_cmd(char *line, int cmd_nbr, char **envp)
{
	char	**split;
	t_tree	**root;
	int		i;

	i = 0;
	split = ft_split_pipe(line, '|');
	root = ft_calloc(cmd_nbr, sizeof(t_tree));
	if (!root)
		exit (0);
	while (split[i])
	{
		root[i] = create_trees(split[i]);
		error_handler(root[i]);
		i++;
	}
	root[i] = NULL;
	print_trees(root);
	free(split);
	exec_pipes(root, envp);
	if (!ft_strcmp(line, "exit"))
	{
		ft_putstr_fd("exit\n", 1);
		free(split);
		exit(0);
	}
	return (0);
}