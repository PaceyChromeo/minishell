/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaev <misaev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:01:54 by misaev            #+#    #+#             */
/*   Updated: 2021/10/18 15:09:10 by misaev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int count_quotes(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	
	while (str[i] != '\0')
	{
		if(str[i] == '"')
			j++;
		i++;
	}
	return j;
}

int count_equals(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	
	while (str[i] != '\0')
	{
		if(str[i] == '=')
			j++;
		i++;
	}
	return j;
}

int check_export_args_str(char *str, int arg_pos)
{
	int i;
	
	i = 0;
	if (arg_pos == 0 && ft_strstr(str, "export") != 0)
		return 0;
	while(str[i] != '=' || str[i] != '\0')
	{
		if (str[i] == '=' || str[i] == '\0')
			break;
		if (ft_isalpha(str[i]) == 1 || str[i] == '_' || (ft_isnum(str[i]) == 1 && i > 0))
			i++;
		else
			return 1;
	}
	return 0;
}