/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 14:18:21 by misaev            #+#    #+#             */
/*   Updated: 2021/10/22 12:08:57 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	echo_option(char **args, int i)
{
	int	x;

	if (args == NULL)
		return (1);
	while (ft_strstr(args[i], "-n"))
	{
		x = 0;
		if (args[i][x] == '-')
		{
			x++;
			while (args[i][x] == 'n' && args[i][x])
				x++;
			if (args[i][x] != 'n' && args[i][x])
				return (i);
		}
		else
			return (i);
		i++;
	}
	return (i);
}
