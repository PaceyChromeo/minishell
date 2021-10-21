/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkrifa <hkrifa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 18:48:23 by hkrifa            #+#    #+#             */
/*   Updated: 2021/10/21 14:56:39 by hkrifa           ###   ########.fr       */
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
	char	**split;
	t_tree	**root;
	
    while (1)
	{
		//system("leaks minishell");
		line = display_prompt();   
		if (check_forbidden_char(line))
			return (printf("Forbidden character : ';' or '\\'\n"));
		cmd_nbr = count_pipes(line, '|');
		split = ft_split_pipe(line, '|');
		if (!split)
			split = NULL;
		root = ft_calloc(cmd_nbr + 2, sizeof(t_tree));
		if (!root)
			root = NULL;
		if (root && split)
		{
			i = 0;
			while (split[i])
			{
				root[i] = create_trees(split[i]);
				if (!root[i])
				{
					free_all(root, split, line);
					return (0);
				}
				error_handler(root[i]);
				i++;
			}
			root[i] = NULL;
		}
		//print_trees(root);
		if (!ft_strcmp(line, "exit"))
		{
			ft_putstr_fd("exit\n", 1);
			exit(0);
		}
		else if (cmd_nbr == 0 && root[0]->cmd_type == tree_cd && root)
			bultins_cmd(root[0]);
		else
			exec_pipes(root, envp);
		free_all(root, split, line);
	}
	return (0);
}

