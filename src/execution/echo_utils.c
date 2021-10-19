/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacey <pacey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 14:18:21 by misaev            #+#    #+#             */
/*   Updated: 2021/10/19 22:26:57 by pacey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int echo_option(char *option)
{
	int i;

	i = 0;
	if (option == NULL)
		return (0);
	if (ft_strstr(option, "-n") != 0)
	{
		if(option[i] == '-')
		{
			i++;
			if (option[i] != 'n' && option[i] != 'e')
				return (0);
		}
		while (option[i] != '\0')
		{
			if (option[i] != 'n' && option[i] != 'e')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);	
}

int	echo_print_env(char *cmd, int i)
{
	char	*env;

	env = get_env(cmd, i);
	ft_putstr_fd(env, STDOUT_FILENO);
	i += ft_strlen(env);
	free(env);
	return (i);
}