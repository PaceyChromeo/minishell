/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 14:25:27 by pjacob            #+#    #+#             */
/*   Updated: 2021/10/27 10:55:10 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	export(char **args,char **env)
{
	lst_env *lst = empty_list();
	int i;
	int e;
	
	e = 0;
	i = 0;
	if (ft_strcmp(args[i], "export") == 0)
	{
		i++;
		e = 1;
	}
	else
		i = 0;
	lst = push_env_to_list(env);
	if (count_tab_nbr(args) > 1)
	{
		while(args[i])
		{
			if (check_export_args_str(args[i]) == 1)
			{
				if (count_tab_nbr(args) - i == 1)
				{
					printf("export: `%s': not a valid identifier\n", args[i]);
					exit(0);
				}
			}
			else
				if(count_equals(args[i]) != 0 || (count_equals(args[i]) == 0 && check_if_arg_in_env(args[i], lst) == 0))
					add_var_last(&lst, args[i], e);	
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
