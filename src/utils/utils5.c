/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 14:13:52 by pjacob            #+#    #+#             */
/*   Updated: 2021/10/27 15:14:21 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_is_exportargs(char *str)
{
	int	i;
	int	equal;

	equal = 0;
	i = 0;
	if (ft_isalpha(str[i]) || str[i] == '_')
	{
		i++;
		while ((ft_isalpha(str[i]) || ft_isnum(str[i]) || str[i] == '_')
			&& str[i])
			i++;
		if (str[i] == '=')
		{
			equal++;
			return (1);
		}
	}
	return (0);
}