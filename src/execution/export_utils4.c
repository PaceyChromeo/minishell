/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 10:01:07 by misaev            #+#    #+#             */
/*   Updated: 2021/10/21 11:18:54 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/* dois retourner un le nombre de d argument incorrect */
int	check_export_args_tab(char **arg)
{
	int	i;
	int	f;

	f = 0;
	i = 0;
	while (arg[i])
	{
		printf("\n==[%s]==\n", arg[i]);
		if (check_export_args_str(arg[i], i) == 1)
		{
			printf("export: `%s': not a valid identifier\n", arg[i]);
			f++;
		}
		i++;
	}
	return (f);
}

int	count_tab_nbr(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}