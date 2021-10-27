/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 18:48:23 by hkrifa            #+#    #+#             */
/*   Updated: 2021/10/27 11:17:17 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_global;

static void	start_minishell(t_tree **root, char *line, int cmd_nbr, t_var *var)
{
	if (line)
	{
		if (cmd_nbr == 0 && (root[0]->cmd_type == tree_cd) && root)
			builtins_cmd(root[0], var);
		else
		{
			if (root[0]->cmd_value 
				&& ft_strcmp(root[0]->cmd_value, "sort") == 0)
				g_global = 255;
			else if (root[0]->cmd_value 
				&& ft_strcmp(root[0]->cmd_value, "cat") == 0)
				g_global = 130;
			exec_pipes(root, var);
		}
	}
}

static t_tree	**get_root(char **split, char *line, int cmd_nbr)
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
			if (!root[i] || error_handler(root[i]))
			{
				free_all(root, split, line);
				return (NULL);
			}
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
	t_var 	var;

	var.env = envp;	
	while (argc && argv)
	{
		//printf("1 - g_global : %d\n", g_global);
		signal(SIGINT, handler_signals);
		signal(SIGQUIT, handler_signals);
		line = display_prompt();
		if (!line)
			return(g_global);
		if (!check_forbidden_char(line))
		{
			cmd_nbr = count_pipes(line, '|');
			split = ft_split_pipe(line, '|');
			if (!split)
				split = NULL;
			root = get_root(split, line, cmd_nbr);
			if (root)
			{
				if (root[0]->size_args && !ft_strcmp(root[0]->cmd_value, "exit"))
				{
					builtins_cmd(root[0], &var);
					ft_putstr_fd("exit\n", 1);
					return(g_global);
				}
				start_minishell(root, line, cmd_nbr, &var);
				free_all(root, split, line);
			}
		}
	}
	return (0);
}
