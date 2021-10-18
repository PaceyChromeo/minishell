/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 18:48:23 by hkrifa            #+#    #+#             */
/*   Updated: 2021/10/18 14:33:28 by pjacob           ###   ########.fr       */
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
	t_tree	**root;
	t_tree	*single_cmd;
	
	i = 0;
	single_cmd = NULL;
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
		if (!cmd_nbr)
		{
			single_cmd = create_trees(line);
			print_tree(single_cmd);
			error_handler(single_cmd);
		}
		else
		{
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
		}
	}
	return (0);
}
