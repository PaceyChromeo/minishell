/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkrifa <hkrifa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 14:25:27 by pjacob            #+#    #+#             */
/*   Updated: 2021/10/29 13:57:50 by hkrifa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	exec_export(t_tree *tree, t_var *var)
{
	int i;
	int e;
	
	e = 0;
	i = 0;
	if (tree->cmd_type == tree_export)
	{
		i = 1;
		e = 1;
	}
	if (tree->size_args > 1 && tree->cmd_type == tree_export)
	{
		while(tree->args[i])
		{
			if (check_export_args_str(tree->args[i]) == 1)
			{
				printf("export: `%s': not a valid identifier\n", tree->args[i]);
				if (tree->size_args - i == 1)
				{
					g_global = 1;
					exit(g_global);
				}
			}
			else
			{
				if (count_equals(tree->args[i]) || !(count_equals(tree->args[i])
					&& !(check_if_arg_in_env(tree->args[i], var->env))))
					add_var_last(&var->env, tree->args[i], e);
			}
			i++;
		}
	}		
	else if (tree->cmd_type == tree_export && tree->size_args == 1)
	{
		printf("zeubi\n");
		lst_env *lst;
		lst = ft_lstdup(var->env);
		sort_env_var(&lst);
		print_list(lst, 1);
		free_list(lst);
	}
	g_global = 0;
	return (g_global);	
}

int	exec_env(t_tree *tree, t_var *var)
{
	if (tree->size_args == 1)
	{
		print_list(var->env, 0);
		g_global = 0;
		return (g_global);
	}
	else
	{
		g_global = 127;
		return (g_global);
	}
}

int exec_unset(t_tree *tree, t_var *var)
{
	int i;
	int j;
	lst_env *temp_lst;

	i = 1;
	if (tree->size_args > 1)
	{
		while(tree->args[i])
		{
			j = 0;
			temp_lst = var->env;
			while(temp_lst)
			{
				if (ft_strstr_int(temp_lst->var_env, tree->args[i]) == 1)
				{
					var->env = free_at(&var->env, j);
					break ;		
				}
				j++;
				temp_lst = temp_lst->next;
			}
			i++;			
		}
	}
	return (0);
}

