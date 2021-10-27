/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 14:25:27 by pjacob            #+#    #+#             */
/*   Updated: 2021/10/27 11:36:27 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	export(t_tree *tree,char **env)
{
	lst_env *lst = empty_list();
	int i;
	int e;
	
	e = 0;
	i = 0;
	if (!ft_strcmp(tree->args[i], "export"))
	{
		i++;
		e = 1;
	}
	else
		i = 0;
	lst = push_env_to_list(env);
	if (tree->size_args > 1)
	{
		while(tree->args[i])
		{
			if (check_export_args_str(tree->args[i]) == 1)
			{
				if (tree->size_args - i == 1)
				{
					printf("export: `%s': not a valid identifier\n", tree->args[i]);
					exit(0);
				}
			}
			else
				if(count_equals(tree->args[i]) != 0
					|| (count_equals(tree->args[i]) == 0
					&& check_if_arg_in_env(tree->args[i], lst) == 0))
					add_var_last(&lst, tree->args[i], e);	
			i++;
		}
	}		
	else
	{
		sort_env_var(&lst);
		print_list(lst);
	}
	free_list(lst);
	g_global = 0;
	return (g_global);	
}
