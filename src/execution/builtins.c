/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 10:04:00 by pjacob            #+#    #+#             */
/*   Updated: 2021/10/21 10:58:26 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static char	**init_builtin_lst(void)
{
	char	**blti_lst;

	blti_lst = ft_calloc(8, sizeof(char *));
	if (!blti_lst)
		return (NULL);
	blti_lst[0] = "echo";
	blti_lst[1] = "cd";
	blti_lst[2] = "pwd";
	blti_lst[3] = "export";
	blti_lst[4] = "unset";
	blti_lst[5] = "env";
	blti_lst[6] = "exit";
	blti_lst[7] = NULL;
	return (blti_lst);
}

int	cmp_builtins(char *value)
{
	int		i;
	char	**bltin_lst;

	if (!value)
		return (7);
	bltin_lst = init_builtin_lst();
	i = 0;
	while (bltin_lst[i])
	{
		if (ft_strcmp(bltin_lst[i], value) == 0)
		{
			free (bltin_lst);
			return (i);
		}
		i++;
	}
	free (bltin_lst);
	return (7);
}
