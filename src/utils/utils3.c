/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacey <pacey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:02:13 by pacey             #+#    #+#             */
/*   Updated: 2021/10/12 15:53:03 by pacey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *s)
{
	char	*copy;
	int		i;

	i = -1;
	copy = (char *)malloc(sizeof(*s) * ft_strlen(s) + 1);
	if (!copy)
		return (NULL);
	while (++i < ft_strlen(s))
		*(copy + i) = *(s + i);
	copy[i] = '\0';
	return (copy);
}

int	ft_is_ascii(char c)
{
	if (c > 0 && c < 127)
		return (1);
	return (0);
}