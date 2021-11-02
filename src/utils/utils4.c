/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 14:26:41 by pjacob            #+#    #+#             */
/*   Updated: 2021/11/02 11:41:35 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	ft_isspace(char str)
{
	if (str == '\t' || str == '\n' || str == '\r'
		|| str == '\v' || str == '\f' || str == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	size_t	nbr;
	size_t	n;

	n = 0;
	i = 0;
	nbr = 0;
	while (ft_isspace(str[i]) == 1)
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i + 1] == '-' || str[i + 1] == '+')
			return (0);
		else if (str[i] == '-')
			n++;
		i++;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		nbr = (nbr * 10) + str[i] - '0';
		i++;
	}
	if (n % 2 == 0)
		return (nbr * 1);
	return (nbr * -1);
}
