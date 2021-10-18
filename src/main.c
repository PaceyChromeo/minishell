/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkrifa <hkrifa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 18:48:23 by hkrifa            #+#    #+#             */
/*   Updated: 2021/10/18 18:49:13 by hkrifa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char	*line;
	int		cmd_nbr;
	int		i;
	char		**split;
	static t_tree	**root;
	
	root = NULL;
    while (1)
	{
		line = display_prompt();   
		if (check_forbidden_char(line))
			return (printf("Forbidden character ';' or '\\'\n"));
		cmd_nbr = count_pipes(line, '|');
		split = ft_split_pipe(line, '|');
		root = ft_calloc(cmd_nbr, sizeof(t_tree));
		if (!root)
			exit (0);
		i = 0;
		while (split[i])
		{
			root[i] = create_trees(split[i]);
			error_handler(root[i]);
			i++;
		}
		root[i] = NULL;
		free(split);
		if (!ft_strcmp(line, "exit"))
		{
			ft_putstr_fd("exit\n", 1);
			exit(0);
		}
		else if (cmd_nbr == 0 && root[0]->cmd_type != tree_execve)
			bultins_cmd(root[0]);
		else
			exec_pipes(root, envp);
			
	}
	return (0);
}

