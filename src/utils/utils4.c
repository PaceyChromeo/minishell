/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 14:26:41 by pjacob            #+#    #+#             */
/*   Updated: 2021/10/25 16:41:51 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_sch_forbidden_char(char c)
{
	if (c == 92 || c == ';')
		return (1);
	return (0);
}

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

void	ft_putnbr_fd(int n, int fd)
{
	size_t	nb;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		nb = (size_t)n * -1;
	}
	else
		nb = n;
	if (nb > 9)
		ft_putnbr_fd(nb / 10, fd);
	ft_putchar_fd((char)(nb % 10 + 48), fd);
}
