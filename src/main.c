/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkrifa <hkrifa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 18:48:23 by hkrifa            #+#    #+#             */
/*   Updated: 2021/10/15 16:50:19 by hkrifa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	int	ok = 1;
	const char *line;
	char **split;
	(void)argc;
	(void)argv;
    (void)envp;
    while (ok)
	{
		//prompt_color();   
		line = readline("minishell ");
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
				// for (int i = 0; split[i]; i++)
				// 	printf("split[%d] = %s\n", i, split[i]);
				int y = 0;
				t_tree **root;
				int	cmd_nbr = count_pipes(line, '|') + 2;
				root = ft_calloc(cmd_nbr, sizeof(t_tree));
				if (!root)
					exit (0);
				while (split[y])
				{
					root[y] = create_trees(split[y]);
					y++;
				}
				root[y] = NULL;
				exec_pipes(root, envp);
			}
		}
	}
	return (0);
}
