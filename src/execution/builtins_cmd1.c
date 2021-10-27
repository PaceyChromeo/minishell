/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 14:25:27 by pjacob            #+#    #+#             */
/*   Updated: 2021/10/27 17:00:24 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	exec_export(t_tree *tree, t_var *var)
{
	int i;
	int e;
	lst_env *lst;
	
	e = 0;
	i = 0;
	if (tree->cmd_type == tree_export)
	{
		i = 1;
		e = 1;
	}
	lst = var->env;
	//printf("---------LST BEFORE--------\n");
	//print_list(lst);
	if (tree->size_args > 1 && tree->cmd_type == tree_export)
	{
		while(tree->args[i])
		{
			if (check_export_args_str(tree->args[i]) == 1)
			{
				if (tree->size_args - i == 1)
				{
					printf("export: `%s': not a valid identifier\n", tree->args[i]);
					g_global = 1;
					exit(g_global);
				}
			}
			else
			{
				if (count_equals(tree->args[i]) || !(count_equals(tree->args[i])
					&& !(check_if_arg_in_env(tree->args[i], lst))))
					add_var_last(&lst, tree->args[i], e);
			}
			i++;
		}
	}		
	else if (tree->cmd_type == tree_export && tree->size_args == 1)
	{
		sort_env_var(&lst);
		print_list(lst, 1);
	}
	//printf("---------LST AFTER--------\n");
	//print_list(lst);
	//var->env = lst;
	//free_list(lst);
	g_global = 0;
	return (g_global);	
}

int	exec_env(t_tree *tree, t_var *var)
{
	lst_env	*lst;

	if (tree->size_args == 1)
	{
		lst = push_env_to_list(var->envp, 0);
		print_list(lst, 0);
		free_list(lst);
		g_global = 0;
		return (g_global);
	}
	else
	{
		g_global = 127;
		return (g_global);
	}
}
