/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkrifa <hkrifa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 18:48:23 by hkrifa            #+#    #+#             */
/*   Updated: 2021/10/18 11:13:46 by hkrifa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char	*prompt;
	char	*line;
	char	**split;
	int	cmd_nbr;
	int y;
	t_tree **root;
	
	y = 0;
    while (1)
	{
		prompt = prompt_color();   
		line = readline(prompt);
		if (ft_strlen(line) > 0)
			add_history(line);
		split = ft_split_pipe(line, '|');
		if (!ft_strcmp(line, "exit"))
		{
			ft_putstr_fd("exit\n", 1);
			exit(0);
		}
		else if (split != NULL)
		{
			if (split)
			{
				cmd_nbr = count_pipes(line, '|') + 2;
				root = ft_calloc(cmd_nbr, sizeof(t_tree));
				if (!root)
					exit (0);
				while (split[y])
				{
					root[y] = create_trees(split[y]);
					y++;
				}
				root[y] = NULL;
				print_tree(root);
				exec_pipes(root, envp);
			}
		}
	}
	return (0);
}
