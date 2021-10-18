/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkrifa <hkrifa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 14:18:21 by misaev            #+#    #+#             */
/*   Updated: 2021/10/18 18:04:15 by hkrifa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int echo_option(char *option)
{
	int i;

	i = 0;
	if (option == NULL)
		return 0;
	if (ft_strstr(option, "-n") != 0)
	{
		if(option[i] == '-')
		{
			i++;
			if (option[i] != 'n' && option[i] != 'e')
				return 0;
		}
		while (option[i] != '\0')
		{
			if (option[i] != 'n' && option[i] != 'e')
				return 0;
			i++;
		}
		return 1;
	}
	return 0;
}

char *ft_strstr(char *str, char *to_find)
{
	int i;
	int j;

	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (to_find[j] == str[i + j])
		{
			if (to_find[j + 1] == '\0')
			{
				return (str + i);
			}
			j++;
		}
		i++;
	}
	return (0);
}