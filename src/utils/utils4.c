/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaev <misaev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 14:26:41 by pjacob            #+#    #+#             */
/*   Updated: 2021/10/18 15:08:14 by misaev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_sch_forbidden_char(char c)
{
	if (c == 92 || c == ';')
		return (1);
	return (0);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t destsize)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = 0;
	if (!dest)
		return (0);
	while (src[src_len])
		src_len++;
	if (!destsize)
		return (src_len);
	while (src[i] && i < destsize - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (src_len);
}
