/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkrifa <hkrifa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 18:48:23 by hkrifa            #+#    #+#             */
/*   Updated: 2021/10/26 13:46:17 by hkrifa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int global;

void	start_minishell(t_tree **root, char *line, int cmd_nbr, char **envp)
{
	if (line)
	{
		if (cmd_nbr == 0 && root[0]->cmd_type == tree_cd && root)
			builtins_cmd(root[0]);
		else	
		{
			if (root[0]->cmd_value 
				&& ft_strcmp(root[0]->cmd_value, "sort") == 0)
				global = 255;
			else if (root[0]->cmd_value 
				&& ft_strcmp(root[0]->cmd_value, "cat") == 0)
				global = 130;
			exec_pipes(root, envp);
		}
	}
}

t_tree	**get_root(char **split, char *line, int cmd_nbr)
{
	int i;
	t_tree **root;
	
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
				return(NULL);
			}
			error_handler(root[i]);
			i++;
		}
		root[i] = NULL;
	}
	return(root);
}

int main(int argc, char **argv, char **envp)
{
	char	*line;
	int		cmd_nbr;
	char	**split;
	t_tree	**root;
	
    while (argc && argv)
	{
		signal(SIGINT, handler_signals);
		signal(SIGQUIT, handler_signals);
		//system("leaks minishell");
		line = display_prompt();
		if (!line)
			return(global);
		if (check_forbidden_char(line))
			return (printf("Forbidden character : ';' or '\\'\n"));
		cmd_nbr = count_pipes(line, '|');
		split = ft_split_pipe(line, '|');
		if (!split)
			split = NULL;
		root = get_root(split, line, cmd_nbr);
		if (root)
		{
			start_minishell(root, line, cmd_nbr, envp);
			if (!ft_strcmp(root[0]->cmd_value, "exit"))
			{
				builtins_cmd(root[0]);
				ft_putstr_fd("exit\n", 1);
				return(global);
			}
		}
		free_all(root, split, line);
	}
	return (0);
}
