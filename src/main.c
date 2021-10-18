/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkrifa <hkrifa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 18:48:23 by hkrifa            #+#    #+#             */
/*   Updated: 2021/10/18 15:42:21 by hkrifa           ###   ########.fr       */
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
	int		cmd_nbr;
	int		i;
	static t_tree	**root;
	//t_tree	*single_cmd;
	
	//i = 0;
	//single_cmd = NULL;
	root = NULL;
    while (1)
	{
		prompt = prompt_color();   
		line = readline(prompt);
		if (ft_strlen(line) > 0)
			add_history(line);
		if (check_forbidden_char(line))
			return (printf("Forbidden character ';' or '\\'\n"));
		cmd_nbr = count_pipes(line, '|');
		// if (!cmd_nbr)
		// {
		// 	single_cmd = create_trees(line);
		// 	print_tree(single_cmd);
		// 	error_handler(single_cmd);
		// }
		//{
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
			else
				exec_pipes(root, envp);
		//}
	}
	return (0);
}
